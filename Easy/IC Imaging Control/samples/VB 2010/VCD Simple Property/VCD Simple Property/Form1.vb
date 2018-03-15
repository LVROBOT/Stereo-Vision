Imports TIS.Imaging

Public Class Form1

        Private VCDProp As TIS.Imaging.VCDHelpers.VCDSimpleProperty
    
        Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' If no device is selected yet, show the selection dialog
        If Not IcImagingControl1.DeviceValid Then
            IcImagingControl1.ShowDeviceSettingsDialog()

            If Not IcImagingControl1.DeviceValid Then
                MsgBox("No device was selected.", MsgBoxStyle.Information, "VCD Simple Property")

                Me.Close()
                Exit Sub
            End If
        End If

        ' Initialize the VCDProp class to access the properties of our ICImagingControl
        ' object
        VCDProp = TIS.Imaging.VCDHelpers.VCDSimpleModule.GetSimplePropertyContainer(IcImagingControl1.VCDPropertyItems)

        ' Initialize the auto checkboxes
        If Not VCDProp.AutoAvailable(VCDIDs.VCDID_Brightness) Then
            BrightnessAutoCheckBox.Enabled = False
        Else
            VCDProp.Automation(VCDIDs.VCDID_Brightness) = False
        End If

        If Not VCDProp.AutoAvailable(VCDIDs.VCDID_WhiteBalance) Then
            WhitebalanceCheckBox.Enabled = False
            WhitebalanceOnePushButton.Enabled = False
        Else
            VCDProp.Automation(VCDIDs.VCDID_WhiteBalance) = False
        End If


        ' Initialize the track bars
        If Not VCDProp.Available(VCDIDs.VCDID_Brightness) Then
            BrightnessTrackBar.Enabled = False
        Else
            BrightnessTrackBar.Enabled = True
            BrightnessTrackBar.Minimum = VCDProp.RangeMin(VCDIDs.VCDID_Brightness)
            BrightnessTrackBar.Maximum = VCDProp.RangeMax(VCDIDs.VCDID_Brightness)
            BrightnessTrackBar.Value = VCDProp.RangeValue(VCDIDs.VCDID_Brightness)
            BrightnessTrackBar.TickFrequency = (BrightnessTrackBar.Maximum - BrightnessTrackBar.Minimum) / 10
            BrightnessValueLabel.Text = BrightnessTrackBar.Value
        End If

        If Not VCDProp.Available(VCDIDs.VCDElement_WhiteBalanceBlue) Then
            WhiteBalBlueTrackBar.Enabled = False
        Else
            WhiteBalBlueTrackBar.Enabled = True
            WhiteBalBlueTrackBar.Minimum = VCDProp.RangeMin(VCDIDs.VCDElement_WhiteBalanceBlue)
            WhiteBalBlueTrackBar.Maximum = VCDProp.RangeMax(VCDIDs.VCDElement_WhiteBalanceBlue)
            WhiteBalBlueTrackBar.Value = VCDProp.RangeValue(VCDIDs.VCDElement_WhiteBalanceBlue)
            WhiteBalBlueTrackBar.TickFrequency = (WhiteBalBlueTrackBar.Maximum - WhiteBalBlueTrackBar.Minimum) / 10
            WhiteBalBlueLabel.Text = WhiteBalBlueTrackBar.Value
        End If

        If Not VCDProp.Available(VCDIDs.VCDElement_WhiteBalanceRed) Then
            WhiteBalRedTrackBar.Enabled = False
        Else
            WhiteBalRedTrackBar.Enabled = False
            WhiteBalRedTrackBar.Enabled = True
            WhiteBalRedTrackBar.Minimum = VCDProp.RangeMin(VCDIDs.VCDElement_WhiteBalanceRed)
            WhiteBalRedTrackBar.Maximum = VCDProp.RangeMax(VCDIDs.VCDElement_WhiteBalanceRed)
            WhiteBalRedTrackBar.Value = VCDProp.RangeValue(VCDIDs.VCDElement_WhiteBalanceRed)
            WhiteBalRedTrackBar.TickFrequency = (WhiteBalRedTrackBar.Maximum - WhiteBalRedTrackBar.Minimum) / 10
            WhiteBalRedLabel.Text = WhiteBalRedTrackBar.Value
        End If

        ' start live mode
        IcImagingControl1.LiveStart()
    End Sub
    
        Private Sub BrightnessTrackBar_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BrightnessTrackBar.Scroll
        VCDProp.RangeValue(VCDIDs.VCDID_Brightness) = BrightnessTrackBar.Value
        BrightnessValueLabel.Text = VCDProp.RangeValue(VCDIDs.VCDID_Brightness)
    End Sub
    
        Private Sub BrightnessAutoCheckBox_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BrightnessAutoCheckBox.CheckedChanged
        VCDProp.Automation(VCDIDs.VCDID_Brightness) = BrightnessAutoCheckBox.Checked
        BrightnessTrackBar.Enabled = Not BrightnessAutoCheckBox.Checked
    End Sub
    
        Private Sub WhitebalanceCheckBox_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles WhitebalanceCheckBox.CheckedChanged
        VCDProp.Automation(VCDIDs.VCDID_WhiteBalance) = WhitebalanceCheckBox.Checked
        WhiteBalBlueTrackBar.Enabled = Not WhitebalanceCheckBox.Checked
        WhiteBalRedTrackBar.Enabled = Not WhitebalanceCheckBox.Checked
    End Sub
    
        Private Sub WhitebalanceOnePushButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles WhitebalanceOnePushButton.Click
        VCDProp.OnePush(VCDIDs.VCDID_WhiteBalance)
    End Sub
    
    Private Sub WhiteBalRedTrackBar_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles WhiteBalRedTrackBar.Scroll
        VCDProp.RangeValue(VCDIDs.VCDElement_WhiteBalanceRed) = WhiteBalRedTrackBar.Value
        WhiteBalRedLabel.Text = VCDProp.RangeValue(VCDIDs.VCDElement_WhiteBalanceRed)
    End Sub

    Private Sub WhiteBalBlueTrackBar_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles WhiteBalBlueTrackBar.Scroll
        VCDProp.RangeValue(VCDIDs.VCDElement_WhiteBalanceBlue) = WhiteBalBlueTrackBar.Value
        WhiteBalBlueLabel.Text = VCDProp.RangeValue(VCDIDs.VCDElement_WhiteBalanceBlue)
    End Sub
End Class
