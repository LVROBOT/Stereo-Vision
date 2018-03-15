Public Class Form1

    ''' <summary>
    ''' Form1_Load
    '''
    ''' If no video capture device was selected in the properties window of IC
    ''' Imaging Control, the device settings dialog of IC Imaging Control is shown.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        If Not IcImagingControl1.DeviceValid() Then
            IcImagingControl1.ShowDeviceSettingsDialog()

            If Not IcImagingControl1.DeviceValid Then
                MsgBox("No device was selected.", MsgBoxStyle.Information, "Grabbing an Image")

                Me.Close()
            End If
        End If
    End Sub

    ''' <summary>
    ''' cmdStartLive_Click
    '''
    ''' Start the live video.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdStartLive_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStartLive.Click
        IcImagingControl1.LiveStart()
    End Sub
    
    ''' <summary>
    ''' cmdStopLive_Click
    '''
    ''' Stop the live video.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdStopLive_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStopLive.Click
        IcImagingControl1.LiveStop()
    End Sub
    
    ''' <summary>
    ''' cmdSaveBitmap_Click
    '''
    ''' Snap an image from the live video stream and show a sav file selection
    ''' dialog. After the file name has been selected, the image is saved to a
    ''' bitmap file.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdSaveBitmap_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdSaveBitmap.Click
        IcImagingControl1.MemorySnapImage()
        ' Call the save file dialog to enter the file name of the image
        Dim saveFileDialog1 As New SaveFileDialog
        saveFileDialog1.Filter = "bmp files (*.bmp)|*.bmp|All files (*.*)|*.*"
        saveFileDialog1.FilterIndex = 1
        saveFileDialog1.RestoreDirectory = True

        If saveFileDialog1.ShowDialog() = DialogResult.OK Then
            ' Save the image.
            IcImagingControl1.MemorySaveImage(saveFileDialog1.FileName)
        End If
    End Sub
    End Class
