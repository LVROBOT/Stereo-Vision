Imports System.Windows.Forms
Imports TIS.Imaging
Imports TIS.Imaging.VCDHelpers

Public Class Form1

        private VCDProp as VCDSimpleProperty
    
    ''' <summary>
    ''' All preparations are performed here.
    ''' - selecting a device
    ''' - starting the live video
    ''' - fetching the properties and initializing the controls
    ''' </summary>
        Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        If IcImagingControl1.ShowDeviceSettingsDialog = DialogResult.OK Then
            IcImagingControl1.LiveStart()

            VCDProp = VCDSimpleModule.GetSimplePropertyContainer(IcImagingControl1.VCDPropertyItems)

            '  Setup the range of the brightness slider.
            trackBar1.Minimum = VCDProp.RangeMin(VCDIDs.VCDID_Brightness)
            trackBar1.Maximum = VCDProp.RangeMax(VCDIDs.VCDID_Brightness)

            '  Set the slider to the current brightness value.
            trackBar1.Value = VCDProp.RangeValue(VCDIDs.VCDID_Brightness)
        Else
            System.Windows.Forms.MessageBox.Show("No device was selected.", Me.Text, System.Windows.Forms.MessageBoxButtons.OK, MessageBoxIcon.Information)
            Me.Close()
        End If

    End Sub
    
        Private Sub trackBar1_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles trackBar1.Scroll
        VCDProp.RangeValue(VCDIDs.VCDID_Brightness) = trackBar1.Value
    End Sub
    
End Class
