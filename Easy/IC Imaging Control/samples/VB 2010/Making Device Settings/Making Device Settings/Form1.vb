Public Class Form1

    ' ------------------------------------------------------------------------------
    ' Form events
    ' ------------------------------------------------------------------------------

    '
    ' Form_Load
    '
    ' Start the live display, if a video capture device has been selected.
    '
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        cmdStopLive.Enabled = False

        If IcImagingControl1.DeviceValid = True Then
            cmdStartLive.Enabled = True
        Else
            cmdStartLive.Enabled = False
        End If
    End Sub

    ' ----------------------------------------------------------------------------
    ' Menus and buttons
    ' ----------------------------------------------------------------------------

    '
    ' cmdDevice_Click
    '
    ' Open a Device Settings dialog box.
    '
    
    Private Sub cmdDevice_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdDevice.Click
                Dim DeviceDialog As New frmDeviceSettings

        DeviceDialog.ImagingControl = IcImagingControl1
        DeviceDialog.ShowDialog()

        DeviceDialog.Dispose()
                If Not IcImagingControl1.LiveVideoRunning Then
            If IcImagingControl1.DeviceValid = True Then
                cmdStartLive.Enabled = True
            Else
                cmdStartLive.Enabled = False
            End If
        End If
    End Sub

    Private Sub cmdStartLive_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStartLive.Click
        On Error GoTo err_cmdStartLive_Click

        IcImagingControl1.LiveStart()
        cmdStartLive.Enabled = False
        cmdStopLive.Enabled = True
        Exit Sub

err_cmdStartLive_Click:
        MessageBox.Show(Err.Description)
    End Sub

    Private Sub cmdStopLive_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStopLive.Click
        On Error GoTo err_cmdStopLive_Click

        IcImagingControl1.LiveStop()
        cmdStartLive.Enabled = True
        cmdStopLive.Enabled = False
        Exit Sub

err_cmdStopLive_Click:
        MessageBox.Show(Err.Description)
    End Sub
End Class
