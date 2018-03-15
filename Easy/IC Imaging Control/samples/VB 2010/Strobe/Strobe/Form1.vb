Imports TIS.Imaging
Imports TIS.Imaging.VCDHelpers

Public Class Form1

        Private VCDProp As VCDSimpleProperty
    
        Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' If no device is selected yet, show the selection dialog
        If Not IcImagingControl1.DeviceValid Then
            IcImagingControl1.ShowDeviceSettingsDialog()

            If Not IcImagingControl1.DeviceValid Then
                MsgBox("No device was selected.", MsgBoxStyle.Information, "Strobe")

                Me.Close()
                Exit Sub
            End If
        End If

        ' Initialize the VCDProp class to access the properties of our ICImagingControl
        ' object
        VCDProp = VCDSimpleModule.GetSimplePropertyContainer(IcImagingControl1.VCDPropertyItems)

        ' Initialize the strobe checkbox.
        If Not VCDProp.SwitchAvailable(VCDIDs.VCDID_Strobe) Then
            chkStrobe.Enabled = False
        Else
            chkStrobe.Enabled = True
            ' Read the current state of the camera's strobe and set the check box
            ' to this value. To query the current state of the strobe, the 
            ' "switch" property of the VCDProp helper class is read out.
            If VCDProp.Switch(VCDIDs.VCDID_Strobe) = True Then
                chkStrobe.CheckState = CheckState.Checked
            Else
                chkStrobe.CheckState = CheckState.Unchecked
            End If
        End If

        ' start live mode
        IcImagingControl1.LiveStart()
    End Sub
    
    ''' <summary>
    ''' chkStrobe_CheckedChanged
    '''
    ''' If the user changes the contents of the strobe check box, the strobe of
    ''' the camera is to be enabled or disabled.
    ''' To handle the strobe, the "switch" property is set.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub chkStrobe_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chkStrobe.CheckedChanged
        If chkStrobe.Checked = True Then
            VCDProp.Switch(VCDIDs.VCDID_Strobe) = 1
        Else
            VCDProp.Switch(VCDIDs.VCDID_Strobe) = 0
        End If
    End Sub
End Class
