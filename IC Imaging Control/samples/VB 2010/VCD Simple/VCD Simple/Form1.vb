Public Class Form1

    ' These variables will hold the interfaces to the brightness property
        Dim BrightnessRange As TIS.Imaging.VCDRangeProperty
    Dim BrightnessSwitch As TIS.Imaging.VCDSwitchProperty
        ''' <summary>
    ''' Form1_Load
    '''
    ''' Check whether a device has been specified in the properties of IC Imaging
    ''' Control. If there is no device, show the device selection dialog.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' Create a VCDPropertyItem for brightness.
        Dim Brightness As TIS.Imaging.VCDPropertyItem

        sldBrightness.Enabled = False
        chkBrightnessAuto.Enabled = False

        If IcImagingControl1.DeviceValid = False Then
            IcImagingControl1.ShowDeviceSettingsDialog()
        End If

        If IcImagingControl1.DeviceValid Then
            If GetBrightnessItem() = True Then
                                ' Initialize the slider with the current range and value of the
                ' BrightnessRange object.
                sldBrightness.Enabled = True
                sldBrightness.Minimum = BrightnessRange.RangeMin
                sldBrightness.Maximum = BrightnessRange.RangeMax
                sldBrightness.Value = BrightnessRange.Value

                ' Initialize the checkbox with the BrightnessSwitch object
                If Not BrightnessSwitch Is Nothing Then
                    chkBrightnessAuto.Enabled = True
                    sldBrightness.Enabled = Not BrightnessSwitch.Switch
                    chkBrightnessAuto.Checked = BrightnessSwitch.Switch
                End If
                                IcImagingControl1.LiveStart()
            End If
        Else
            MsgBox("No device was selected.", MsgBoxStyle.Information, "VCD Simple Property")
            Me.Close()
        End If
    End Sub

    ''' <summary>
    ''' GetBrightnessItem
    '''
    ''' Retrieve the brightness VCDPropertyItem and assign BrightnessSwitch and BrightnessRange.
    ''' The function returns true, if the property exists. If the property does not
    ''' exists, the function returns false.
    ''' </summary>
    ''' <returns></returns>
    ''' <remarks></remarks>
    Private Function GetBrightnessItem()
        ' Try Find brightness property in the VCDPropertyItems collection.
        ' If brightness is not supported by the current video capture device,
        ' the value Brightness is Nothing.
                Dim Brightness As TIS.Imaging.VCDPropertyItem
        Brightness = IcImagingControl1.VCDPropertyItems.FindItem(TIS.Imaging.VCDIDs.VCDID_Brightness)
                GetBrightnessItem = True
                If Not Brightness Is Nothing Then
            ' Acquire interfaces to the range and switch interface for value and auto
            BrightnessRange = Brightness.Elements.FindInterface(TIS.Imaging.VCDIDs.VCDElement_Value + _
                                                                ":" + _
                                                                TIS.Imaging.VCDIDs.VCDInterface_Range)
            Try
                BrightnessSwitch = Brightness.Elements.FindInterface(TIS.Imaging.VCDIDs.VCDElement_Auto + _
                                                                    ":" + _
                                                                    TIS.Imaging.VCDIDs.VCDInterface_Switch)
            Catch ex As System.Exception
                MsgBox("Automation of brightness is not supported by the current device!")
            End Try
        End If
                ' Show a message box if brightness is not supported.
        If Brightness Is Nothing Then
            MsgBox("Brightness property is not supported by the current device!")
            GetBrightnessItem = False
        End If
    End Function

    ''' <summary>
    ''' chkBrightnessAuto_CheckedChanged
    '''
    ''' Enable or disable the autmatic of the brightness property when the checkbox
    ''' has been clicked.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub chkBrightnessAuto_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles chkBrightnessAuto.CheckedChanged
        BrightnessSwitch.Switch = chkBrightnessAuto.Checked
        sldBrightness.Enabled = Not chkBrightnessAuto.Checked
    End Sub
    
    ''' <summary>
    ''' sldBrightness_Scroll
    '''
    ''' Set the brightness to the current slider position.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub sldBrightness_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles sldBrightness.Scroll
        BrightnessRange.Value = sldBrightness.Value
    End Sub
    
End Class
