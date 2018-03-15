Public Class frmDeviceSettings

        Public ImagingControl As TIS.Imaging.ICImagingControl
    Private DeviceState As String
    Const NOT_AVAILABLE = "n/a"
    
    ' ------------------------------------------------------------------------------
    ' Form events
    ' ------------------------------------------------------------------------------

    '
    ' Form_Load
    '
    ' Fill the Video Sources combo box with names of all available
    ' video capture devices and select the first one. This will trigger
    ' a click event on the Video Sources combo box and open the device.
    '
        Private Sub frmDeviceSettings_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Load
        If ImagingControl.DeviceValid Then
            If ImagingControl.LiveVideoRunning Then
                lblErrorMessage.Text = "The device settings dialog is not available while the live video is running.\n\nStop the live video first."
                lblErrorMessage.AutoSize = False
                lblErrorMessage.Padding = New Padding(8)
                lblErrorMessage.SetBounds(0, 0, 100, cmdOK.Top)
                lblErrorMessage.Dock = DockStyle.Top
                lblErrorMessage.Visible = True
                Exit Sub
            Else
                lblErrorMessage.Visible = False
            End If
        End If

        SaveDeviceSettings()

        UpdateDevices()
    End Sub
    
    ' ------------------------------------------------------------------------------
    ' Buttons
    ' ------------------------------------------------------------------------------

    '
    ' cmdCancel_Click
    '
    ' Close form and set canceled to true.
    '
        Private Sub cmdCancel_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles cmdCancel.Click
        RestoreDeviceSettings()

        Me.Close()
    End Sub
    
    '
    ' cmdOK_Click
    '
    ' Close form.
    '
        Private Sub cmdOK_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles cmdOK.Click
        Me.Close()
    End Sub
    
    ' ------------------------------------------------------------------------------
    ' Combo boxes
    ' ------------------------------------------------------------------------------

    '
    ' cboDevice_SelectedIndexChanged
    '
    ' Get available inputs and video formats for the selected
    ' device and enter the information in the respective combo
    ' boxes.
    '
        Private Sub cboDevice_SelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles cboDevice.SelectedIndexChanged
        Dim Serial As String = ""

        Try
            'Open the device
            If cboDevice.Enabled Then

                Dim Item As Object
                Dim index As Integer
                index = 0

                ImagingControl.Device = cboDevice.Text
                txtSerial.Text = NOT_AVAILABLE

                For Each Item In ImagingControl.Devices
                    If Item.Name = cboDevice.Text Then
                        If ImagingControl.Devices(index).GetSerialNumber(Serial) Then
                            txtSerial.Text = Serial
                            Exit For
                        End If
                    End If
                    index = index + 1
                Next

                ' Get supported video norms, formats and inputs
                UpdateVideoNorms()
                UpdateInputChannels()
                UpdateFlip()
            End If

        Catch ex As System.Exception
            MessageBox.Show(ex.Message)
        End Try
    End Sub
    
    '
    ' cboVideoNorm_SelectedIndexChanged
    '
    ' Select a video norm.
    '
        Private Sub cboVideoNorm_SelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles cboVideoNorm.SelectedIndexChanged
        Try
            If cboVideoNorm.Enabled Then
                ImagingControl.VideoNorm = cboVideoNorm.Text
            End If

            UpdateVideoFormats()

        Catch ex As System.Exception
            MessageBox.Show(ex.Message)
        End Try
    End Sub
    
    '
    ' cboInputChannel_SelectedIndexChanged
    '
    ' Select an input channel.
    '
        Private Sub cboInputChannel_SelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles cboInputChannel.SelectedIndexChanged
        Try
            If cboInputChannel.Enabled Then
                ImagingControl.InputChannel = cboInputChannel.Text
            End If

        Catch ex As System.Exception
            MessageBox.Show(ex.Message)
        End Try
    End Sub
    
    '
    ' cboVideoFormat_SelectedIndexChanged
    '
    ' Select a video format.
    '
        Private Sub cboVideoFormat_SelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles cboVideoFormat.SelectedIndexChanged
        Try
            If cboVideoFormat.Enabled Then
                ImagingControl.VideoFormat = cboVideoFormat.Text
            End If

            UpdateFrameRates()

        Catch ex As System.Exception
            MessageBox.Show(ex.Message)
        End Try
    End Sub
    
    '
    ' cboFrameRate_SelectedIndexChanged
    '
    ' Select a frame rate
    '
        Private Sub cboFrameRate_SelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles cboFrameRate.SelectedIndexChanged
        Try

            If cboFrameRate.Enabled Then
                ImagingControl.DeviceFrameRate = CDbl(cboFrameRate.Text)
            End If

        Catch ex As System.Exception
            MessageBox.Show(ex.Message)
        End Try
    End Sub
    '

    '
    ' chkFlipV
    '
    ' Switch flip vertical on/off
    '
        Private Sub chkFlipV_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles chkFlipV.Click
        If ImagingControl.DeviceFlipVerticalAvailable Then
            ImagingControl.DeviceFlipVertical = (chkFlipV.Checked = True)
        End If
    End Sub
    
    '
    ' chkFlipH
    '
    ' Switch flip horizontal on/off
    '
    Private Sub chkFlipH_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles chkFlipH.Click
        If ImagingControl.DeviceFlipHorizontalAvailable Then
            ImagingControl.DeviceFlipHorizontal = (chkFlipH.Checked = True)
        End If
    End Sub


    ' ------------------------------------------------------------------------------
    ' UI Update
    ' ------------------------------------------------------------------------------

    '
    ' UpdateDevices
    '
    ' Fills cboDevice
    '
        Private Sub UpdateDevices()
        cboDevice.Items.Clear()
        If ImagingControl.Devices.Length > 0 Then
            Dim Item As Object

            For Each Item In ImagingControl.Devices
                cboDevice.Items.Add(Item.ToString())
            Next

            If ImagingControl.DeviceValid Then
                cboDevice.SelectedItem = ImagingControl.Device
            Else
                cboDevice.SelectedIndex = 0
            End If
            cboDevice.Enabled = True
        Else
            cboDevice.Items.Add(NOT_AVAILABLE)
            cboDevice.Enabled = False
            cboDevice.SelectedIndex = 0
        End If
    End Sub
    
    '
    ' UpdateVideoNorms
    '
    ' Fills cboVideoNorm
    '
        Private Sub UpdateVideoNorms()
        cboVideoNorm.Items.Clear()
        If ImagingControl.VideoNormAvailable Then
            Dim Item As Object

            For Each Item In ImagingControl.VideoNorms
                cboVideoNorm.Items.Add(Item.ToString())
            Next

            cboVideoNorm.SelectedItem = ImagingControl.VideoNorm
            cboVideoNorm.Enabled = True
        Else
            cboVideoNorm.Items.Add(NOT_AVAILABLE)
            cboVideoNorm.Enabled = False
            cboVideoNorm.SelectedIndex = 0
        End If
    End Sub
    
    '
    ' UpdateVideoFormats
    '
    ' Fills cboVideoFormat
    '
        Private Sub UpdateVideoFormats()
        cboVideoFormat.Items.Clear()
        If ImagingControl.DeviceValid Then
            Dim Item As Object

            For Each Item In ImagingControl.VideoFormats
                cboVideoFormat.Items.Add(Item.ToString())
            Next

            cboVideoFormat.SelectedItem = ImagingControl.VideoFormat
            cboVideoFormat.Enabled = True
        Else
            cboVideoFormat.Items.Add(NOT_AVAILABLE)
            cboVideoFormat.Enabled = False
            cboVideoFormat.SelectedIndex = 0
        End If
    End Sub
    
    '
    ' UpdateInputChannels
    '
    ' Fills cboInputChannel
    '
        Private Sub UpdateInputChannels()
        cboInputChannel.Items.Clear()
        If ImagingControl.InputChannelAvailable Then
            Dim Item As Object

            For Each Item In ImagingControl.InputChannels
                cboInputChannel.Items.Add(Item.ToString())
            Next

            cboInputChannel.SelectedItem = ImagingControl.InputChannel
            cboInputChannel.Enabled = True
        Else
            cboInputChannel.Items.Add(NOT_AVAILABLE)
            cboInputChannel.Enabled = False
            cboInputChannel.SelectedIndex = 0
        End If
    End Sub
    
    '
    ' UpdateFrameRates
    '
    ' Fills cboFrameRates
    '
        Private Sub UpdateFrameRates()
        cboFrameRate.Items.Clear()
        If ImagingControl.DeviceFrameRateAvailable Then
            Dim Item As Object

            For Each Item In ImagingControl.DeviceFrameRates
                cboFrameRate.Items.Add(Str(Item))
            Next

            cboFrameRate.SelectedItem = Str(ImagingControl.DeviceFrameRate)
            cboFrameRate.Enabled = True
        Else
            cboFrameRate.Items.Add(NOT_AVAILABLE)
            cboFrameRate.Enabled = False
            cboFrameRate.SelectedIndex = 0
        End If
    End Sub
    
    '
    ' UpdateFlip
    '
    ' updates the flip checkboxes
    '
        Private Sub UpdateFlip()
        If ImagingControl.DeviceFlipHorizontalAvailable Then
            chkFlipH.Enabled = True
            If ImagingControl.DeviceFlipHorizontal Then
                chkFlipH.Checked = True
            Else
                chkFlipH.Checked = False
            End If
        Else
            chkFlipH.Enabled = False
            chkFlipH.Checked = False
        End If

        If ImagingControl.DeviceFlipVerticalAvailable Then
            chkFlipV.Enabled = True
            If ImagingControl.DeviceFlipVertical Then
                chkFlipV.Checked = True
            Else
                chkFlipV.Checked = False
            End If
        Else
            chkFlipV.Enabled = False
            chkFlipV.Checked = False
        End If
    End Sub
    
    Private Sub SaveDeviceSettings()
        DeviceState = ImagingControl.DeviceState
    End Sub

    Private Sub RestoreDeviceSettings()

        Try
            ImagingControl.DeviceState = DeviceState
        Catch ex As System.Exception
        End Try
    End Sub

End Class