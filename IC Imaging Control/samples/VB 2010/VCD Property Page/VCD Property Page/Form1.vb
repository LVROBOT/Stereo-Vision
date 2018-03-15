Public Class Form1

    Dim vcdPropDlg As VCDPropertiesDlg

    Private Sub cmdSelectDevice_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdSelectDevice.Click
        ' The device settings dialog needs the live mode to be stopped
        If IcImagingControl1.LiveVideoRunning Then
            IcImagingControl1.LiveStop()
        End If

        IcImagingControl1.ShowDeviceSettingsDialog()

        IcImagingControl1.LiveStart()
    End Sub

    Private Sub cmdShowMyDialog_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdShowMyDialog.Click
        ' Show our VCD Property dialog
        If vcdPropDlg Is Nothing Then
            vcdPropDlg = New VCDPropertiesDlg
            vcdPropDlg.SetIC(IcImagingControl1)
            vcdPropDlg.ShowDialog()
            vcdPropDlg.Dispose()
            vcdPropDlg = Nothing
        End If
    End Sub

    Private Sub cmdShowOriginalDialog_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdShowOriginalDialog.Click
        ' Show the builtin property dialog
        IcImagingControl1.ShowPropertyDialog()
    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' If no device was selected in the property browser, try to open the first device
        If Not IcImagingControl1.DeviceValid Then
            IcImagingControl1.ShowDeviceSettingsDialog()

            If Not IcImagingControl1.DeviceValid Then
                MessageBox.Show("No device was selected.")
                Me.Close()
                Exit Sub
            End If
        End If
        IcImagingControl1.LiveStart()
    End Sub
End Class
