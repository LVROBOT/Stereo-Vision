Imports TIS.Imaging
Imports TIS.Imaging.VCDHelpers

Public Class Form1

        Private VCDProp As VCDSimpleProperty
    
        Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        ' If no device is selected yet, show the selection dialog
        If Not IcImagingControl1.DeviceValid Then
            IcImagingControl1.ShowDeviceSettingsDialog()

            If Not IcImagingControl1.DeviceValid Then
                MsgBox("No device was selected.", MsgBoxStyle.Information, "DigitalIO")

                Me.Close()
                Exit Sub
            End If
        End If

        ' Initialize the VCDProp class to access the properties of our ICImagingControl
        ' object
        VCDProp = VCDSimpleModule.GetSimplePropertyContainer(IcImagingControl1.VCDPropertyItems)

        ' Initialize the DigitalIO controls of the form.
        If VCDProp.Available(VCDIDs.VCDID_GPIO) Then
            cmdReadDigitalInput.Enabled = True
            ' Read the current state of the digital input.
            ReadDigitalInput()

            cmdWriteDigitalOutput.Enabled = True
            chkDigitalOutputState.Enabled = True

            ' Set the chkDigitalOutputState check box to the current state of
            ' the video capture device's digital output state.
            If VCDProp.RangeValue(VCDIDs.VCDElement_GPIOOut) = 1 Then
                chkDigitalOutputState.CheckState = CheckState.Checked
            Else
                chkDigitalOutputState.CheckState = CheckState.Unchecked
            End If
        Else
            cmdReadDigitalInput.Enabled = False
            cmdWriteDigitalOutput.Enabled = False
            chkDigitalOutputState.Enabled = False
        End If

        ' start live mode
        IcImagingControl1.LiveStart()

    End Sub
    
    Private Sub cmdReadDigitalInput_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdReadDigitalInput.Click
        ReadDigitalInput()
    End Sub

    ''' <summary>
    ''' cmdReadDigitalInput_Click
    '''
    ''' Read the current state of the digital input and set the checkbox
    ''' chkDigitalInputState to this state.
    ''' </summary>
    ''' <remarks></remarks>
    Private Sub ReadDigitalInput()
        ' Read the digital input states of the video capture device.
        VCDProp.OnePush(VCDIDs.VCDElement_GPIORead)

        ' Now set the chkDigitalInputState state to the read value.
        If VCDProp.RangeValue(VCDIDs.VCDElement_GPIOIn) = 1 Then
            chkDigitalInputState.CheckState = CheckState.Checked
        Else
            chkDigitalInputState.CheckState = CheckState.Unchecked
        End If

    End Sub

    ''' <summary>
    ''' cmdWriteDigitalOutput_Click
    '''
    ''' Set the digital outputs of the video capture device to the state of the
    ''' chkDigitalOutputState check box and write this state to the video capture
    ''' device.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub cmdWriteDigitalOutput_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdWriteDigitalOutput.Click
        ' Set the state, that will be send to the video capture device.
        If chkDigitalOutputState.CheckState = CheckState.Checked Then
            VCDProp.RangeValue(VCDIDs.VCDElement_GPIOOut) = 1
        Else
            VCDProp.RangeValue(VCDIDs.VCDElement_GPIOOut) = 0
        End If

        ' Send / write the digital output state to the video capture device.
        VCDProp.OnePush(VCDIDs.VCDElement_GPIOWrite)
    End Sub
End Class
