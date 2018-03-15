Public Class Form1

    Dim VideoHasStarted As Boolean
    Dim VideoHasStopped As Boolean

        Private Sub cmdStartLive_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStartLive.Click
        IcImagingControl1.LiveStart()

        ' Store in VideoHasStarted whether a video stream
        ' has been started once. If VideoHasStarted is True,
        ' you can be sure that there is an image that can be processed.
        VideoHasStarted = True

        ' VideoHasStopped is set to False, because the live
        ' video has just been started.
        VideoHasStopped = False
    End Sub
    
    ''' <summary>
    ''' Form_load
    '''
    '''  Shows the device settings dialog and checks for a  valid video
    '''  capture device to prevent error messages.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' No video stream has been started now. Processing an image 
        ' will fail in this case.
        VideoHasStarted = False
        VideoHasStopped = False

        ' Check whether a valid video capture device has been selected,
        ' otherwise show the device settings dialog.
        If Not IcImagingControl1.DeviceValid Then
            IcImagingControl1.ShowDeviceSettingsDialog()

            If Not IcImagingControl1.DeviceValid Then
                MsgBox("No device was selected.", MsgBoxStyle.Information, "Image Processing Sample")

                Me.Close()
                Exit Sub
            End If
        End If

        cmdStartLive.Enabled = True
        cmdStopLive.Enabled = True
        cmdProcess.Enabled = True

        ' This sample works works for color images, so set the sink type
        ' to RGB24
        IcImagingControl1.MemoryCurrentGrabberColorformat = TIS.Imaging.ICImagingControlColorformats.ICRGB24
    End Sub

        Private Sub cmdStopLive_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStopLive.Click
        IcImagingControl1.LiveStop()

        If VideoHasStarted = True Then
            VideoHasStopped = True
        End If
    End Sub
    
    ''' <summary>
    ''' cmdProcess_Click
    '''
    ''' Snaps a single image, inverts the image data and shows the buffer.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdProcess_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdProcess.Click
        Dim ImgBuffer As TIS.Imaging.ImageBuffer
        Dim x As Integer, y As Integer
        Dim BytesPerLine As Integer
        Cursor = Cursors.WaitCursor
        Try
            ' Check whether the video stream has been started once.
            ' If it has been started once, there are two possible situations:
            ' 1) The live video is running. In this case we stop the live video
            '       in order to get the last frame and display the processed image.
            ' 2) The live video has been stopped. In this case the last frame of the
            '       live video was grabbed automatically and can be processed and
            '       displayed.

            If VideoHasStarted Then
                If VideoHasStopped = False Then
                    IcImagingControl1.LiveStop()
                End If

                ImgBuffer = IcImagingControl1.ImageActiveBuffer
                ' Calculate the count of bytes ber line using the color format and the
                ' pixels per line of the image buffer.
                BytesPerLine = ImgBuffer.BitsPerPixel / 8 * ImgBuffer.PixelPerLine - 1
                For y = 0 To ImgBuffer.Lines - 1
                    For x = 0 To BytesPerLine
                        ImgBuffer(x, y) = 255 - ImgBuffer(x, y)
                    Next x
                Next y

                IcImagingControl1.Display()
            Else
                MessageBox.Show("Please click the Start Live button first!", _
                                "Image Processing", _
                                MessageBoxButtons.OK, _
                                MessageBoxIcon.None)
            End If

        Catch ex As System.Exception
            MessageBox.Show(ex.Message)
        End Try
        Cursor = Cursors.Default
    End Sub
    
End Class
