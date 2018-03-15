Imports System
Imports System.Windows
Imports System.Windows.Forms

Public Class Form1

        Private Structure RECT
        Dim Left As Integer
        Dim Top As Integer
        Dim Right As Integer
        Dim Bottom As Integer
    End Structure
            Private DisplayBuffer As TIS.Imaging.ImageBuffer
    Private UserROI As RECT
    Private UserROICommited As Boolean
    Private Threshold As Integer
    
    ''' <summary>
    ''' cmdDevice_Click
    '''
    ''' Shows the device selection dialog and initializes some properties.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdDevice_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdDevice.Click
        With IcImagingControl1
            If .LiveVideoRunning Then
                .LiveStop()
            End If

            .ShowDeviceSettingsDialog()

            If .DeviceValid Then
                cmdStart.Enabled = True
                cmdSettings.Enabled = True
                MakeDeviceSettings()
            End If
        End With
    End Sub
    
    ''' <summary>
    ''' MakeDeviceSettings
    '''
    ''' Setup the ring buffer, color format and capture mode.
    ''' </summary>
    ''' <remarks></remarks>
        Private Sub MakeDeviceSettings()

        ' Set the color format to monochrome
        IcImagingControl1.MemoryCurrentGrabberColorformat = TIS.Imaging.ICImagingControlColorformats.ICY8

        ' Set the ring buffer size to 5. This ensures that the last 5
        ' acquired images are in memory.
        IcImagingControl1.ImageRingBufferSize = 5

        ' LiveCaptureContinuous = True means that every frame is
        ' copied to the ring buffer.
        IcImagingControl1.LiveCaptureContinuous = True

        ' Do not save the last image, if liveStop is called
        IcImagingControl1.LiveCaptureLastImage = False

        ' Disable the live display. This allows to display images
        ' from the ring buffer in ICImagingControl's control window.
        IcImagingControl1.LiveDisplay = False

        ' Set the size of ICImagingControl to the width and height
        ' of the currently selected video format.
        IcImagingControl1.Width = IcImagingControl1.ImageWidth
        IcImagingControl1.Height = IcImagingControl1.ImageHeight

        UserROI.Top = 0
        UserROI.Left = 0
        UserROI.Bottom = IcImagingControl1.ImageHeight
        UserROI.Right = IcImagingControl1.ImageWidth
    End Sub
    
    ''' <summary>
    ''' cmdROICommit_Click
    '''
    ''' Handles the commit or resets the ROI.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdROICommit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdROICommit.Click
        If Not UserROICommited Then
            UserROICommited = True
            cmdROICommit.Text = "Reset ROI"
        Else
            UserROICommited = False
            cmdROICommit.Text = "Set current ROI"
        End If
    End Sub
    
    ''' <summary>
    ''' cmdSettings_Click
    '''
    ''' Shows the device settings dialog.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdSettings_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdSettings.Click
        IcImagingControl1.ShowPropertyDialog()
    End Sub
    
    ''' <summary>
    ''' cmdStart_Click
    '''
    ''' Starts the display.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub cmdStart_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStart.Click
                Try
            IcImagingControl1.LiveStart()
            cmdStart.Enabled = False
            cmdStop.Enabled = True
            cmdROICommit.Enabled = True

        Catch ex As System.Exception
            MsgBox(ex.Message)
        End Try
            End Sub

    ''' <summary>
    ''' cmdStop_Click
    '''
    ''' Stops the display.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub cmdStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStop.Click
                Try
            cmdStart.Enabled = True
            cmdStop.Enabled = False
            If UserROICommited Then
                cmdROICommit_Click(sender, e)
            End If

            cmdROICommit.Enabled = False

            DisplayBuffer.ForceUnlock()

            IcImagingControl1.LiveStop()

        Catch ex As System.Exception
            MsgBox(ex.Message)
        End Try
            End Sub


    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Try
            cmdStart.Enabled = False
            cmdStop.Enabled = False
            cmdSettings.Enabled = False
            cmdROICommit.Enabled = False

            If IcImagingControl1.DeviceValid Then
                cmdStart.Enabled = True
                cmdSettings.Enabled = True

                ' Setup image buffers and the color format
                MakeDeviceSettings()

                DisplayBuffer = IcImagingControl1.ImageBuffers(1)

                UserROI.Top = 0
                UserROI.Left = 0
                UserROI.Bottom = IcImagingControl1.ImageHeight
                UserROI.Right = IcImagingControl1.ImageWidth
            End If

        Catch ex As System.Exception
            MsgBox(ex.Message)
        End Try

    End Sub

    ''' <summary>
    ''' ICImagingControl1_ImageAvailable
    '''
    ''' Event is called for each frame. If an ROI is committed,
    ''' it is drawn. In addition, the current buffer is displayed
    ''' if a change is the ROI is recognized.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub IcImagingControl1_ImageAvailable(ByVal sender As System.Object, ByVal e As TIS.Imaging.ICImagingControl.ImageAvailableEventArgs) Handles IcImagingControl1.ImageAvailable
        Try
                        Dim Region As RECT
            Region = NormalizeRect(UserROI)

            If Not UserROICommited Then
                ContinousMode(e.bufferIndex, Region)
            Else
                CompareMode(e.bufferIndex, Region)
            End If
                    Catch ex As System.Exception
            System.Diagnostics.Trace.WriteLine(ex.Message)
        End Try
    End Sub

    ''' <summary>
    ''' ContinousMode
    '''
    ''' This function is called if the user has not yet commited an ROI.
    ''' The Region contains the ROI specified by the current mouse position.
    ''' The rectangle specified by Region is drawn in the current buffer.
    ''' </summary>
    ''' <param name="BufferIndex"></param>
    ''' <param name="Region"></param>
    ''' <remarks></remarks>
        Private Sub ContinousMode(ByVal BufferIndex As Integer, ByVal Region As RECT)
        DisplayBuffer = IcImagingControl1.ImageBuffers(BufferIndex)
        DisplayBuffer.Lock()
        DrawRectangleY8(DisplayBuffer, Region)
        IcImagingControl1.DisplayImageBuffer(DisplayBuffer)
        DisplayBuffer.Unlock()
    End Sub
    
    ''' <summary>
    ''' CompareMode
    '''
    ''' This function is called when the user commits an ROI.
    ''' Compares the current DisplayBuffer with the recently copied buffer.
    ''' If they differ, sets the copied buffer as DisplayBuffer.
    ''' </summary>
    ''' <param name="BufferIndex"></param>
    ''' <param name="Region"></param>
    ''' <remarks></remarks>
        Private Sub CompareMode(ByVal BufferIndex As Integer, ByVal Region As RECT)
        Dim IBOld, IBNew As TIS.Imaging.ImageBuffer
        IBOld = DisplayBuffer
        IBNew = IcImagingControl1.ImageBuffers(BufferIndex)

        If CompareRegion(IBOld, IBNew, Region, Threshold) Then
            DisplayBuffer.Unlock()
            DisplayBuffer = IBNew
            DisplayBuffer.Lock()

            DrawRectangleY8(IBNew, Region)

            IcImagingControl1.DisplayImageBuffer(DisplayBuffer)
        End If
    End Sub
    
    ''' <summary>
    ''' NormalizeRect
    '''
    ''' Returns a normalized rectangle based on Val.
    ''' Normalized means:
    ''' (left <= right, top <= bottom, right < MaxX, bottom < MaxY)
    ''' </summary>
    ''' <param name="val"></param>
    ''' <returns></returns>
    ''' <remarks></remarks>
        Private Function NormalizeRect(ByRef val As RECT) As RECT
        Dim Tmp As Integer
        Dim r As RECT
        r = val
        If r.Top > r.Bottom Then
            Tmp = r.Top
            r.Top = r.Bottom
            r.Bottom = Tmp
        End If
        If r.Left > r.Right Then
            Tmp = r.Left
            r.Left = r.Right
            r.Right = Tmp
        End If
        If r.Top < 0 Then
            r.Top = 0
        End If
        If r.Left < 0 Then
            r.Left = 0
        End If
        If r.Bottom >= IcImagingControl1.ImageHeight Then
            r.Bottom = IcImagingControl1.ImageHeight - 1
        End If
        If r.Right >= IcImagingControl1.ImageWidth Then
            r.Right = IcImagingControl1.ImageWidth - 1
        End If
        NormalizeRect = r
    End Function
    
    ''' <summary>
    ''' CompareRegion
    '''
    ''' Compares the contents of Arr with Arr2 in the rectangle
    ''' defined by Region. If both arrays differ by more then the
    ''' Threshold value,  the function returns true, otherwise false.
    ''' </summary>
    ''' <param name="Buf"></param>
    ''' <param name="Buf2"></param>
    ''' <param name="Region"></param>
    ''' <param name="Threshold"></param>
    ''' <returns></returns>
    ''' <remarks></remarks>
        Private Function CompareRegion(ByVal Buf As TIS.Imaging.ImageBuffer, ByVal Buf2 As TIS.Imaging.ImageBuffer, ByVal Region As RECT, ByVal Threshold As Integer) As Boolean
        Dim x, y As Integer
        Dim GreyscaleDifference As Integer
        Dim PixelCount As Integer

        PixelCount = (Region.Bottom - Region.Top) * (Region.Right - Region.Left)
        If PixelCount > 0 Then
            GreyscaleDifference = 0
            For y = Region.Top To Region.Bottom
                For x = Region.Left To Region.Right
                    GreyscaleDifference = GreyscaleDifference + Math.Abs(CInt(Buf(x, y)) - CInt(Buf2(x, y)))
                Next x
            Next y
            GreyscaleDifference = GreyscaleDifference / PixelCount
            If GreyscaleDifference > Threshold Then
                CompareRegion = True
            Else
                CompareRegion = False
            End If
        Else
            CompareRegion = False
        End If
    End Function
    
    ''' <summary>
    ''' DrawRectangle
    '''
    ''' Draws a rectangle in the array Arr. The rectangle is
    ''' defined by Region. The rectangle has to be normalized
    ''' (top < bottom, left < right, left < maxX, bottom < maxY)
    ''' </summary>
    ''' <param name="Buf"></param>
    ''' <param name="Region"></param>
    ''' <remarks></remarks>
    Private Sub DrawRectangleY8(ByVal Buf As TIS.Imaging.ImageBuffer, ByVal Region As RECT)
        Const RECT_COLOR As Integer = 255

        Dim x, y As Integer

        For x = Region.Left To Region.Right
            Buf(x, Region.Top) = RECT_COLOR
        Next x
        For x = Region.Left To Region.Right
            Buf(x, Region.Bottom) = RECT_COLOR
        Next x
        For y = Region.Top To Region.Bottom
            Buf(Region.Left, y) = RECT_COLOR
        Next y
        For y = Region.Top To Region.Bottom
            Buf(Region.Right, y) = RECT_COLOR
        Next y

    End Sub

    ''' <summary>
    ''' IcImagingControl1_MouseDown
    '''
    ''' MouseDown event. Resets the user ROI,
    ''' if the left mouse button is pressed.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub IcImagingControl1_MouseDown(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles IcImagingControl1.MouseDown
                If Not UserROICommited And (e.Button = Forms.MouseButtons.Left) Then
            UserROI.Left = e.X
            UserROI.Top = IcImagingControl1.Height - e.Y
        End If
            End Sub

    ''' <summary>
    ''' IcImagingControl1_MouseMove
    '''
    ''' MouseMove event. Sets the user ROI to the current mouse cursor
    ''' position, if the left mouse button is pressed.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub IcImagingControl1_MouseMove(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles IcImagingControl1.MouseMove
                If Not UserROICommited And (e.Button = Forms.MouseButtons.Left) Then
            UserROI.Right = e.X
            UserROI.Bottom = IcImagingControl1.Height - e.Y
        End If
            End Sub

    ''' <summary>
    ''' IcImagingControl1_MouseUp
    '''
    ''' MouseUp event. Sets the user ROI, if the left
    ''' mouse button is released.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub IcImagingControl1_MouseUp(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles IcImagingControl1.MouseUp
                If Not UserROICommited And Not (e.Button = Forms.MouseButtons.Left) Then
            UserROI.Right = e.X
            UserROI.Bottom = IcImagingControl1.Height - e.Y
        End If
            End Sub

    Private Sub sldThresholdSlider_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles sldThresholdSlider.Scroll
        Threshold = sldThresholdSlider.Value
    End Sub
End Class
