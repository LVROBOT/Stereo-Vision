Public Class Form1

    ''' <summary>
    ''' Form_Load
    '''
    ''' Check whether the video capture device supports external
    ''' transport. If external transport is available, the buttons
    ''' for external transports will be enabled.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
	    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        cmdETPlay.Enabled = False
        cmdETStop.Enabled = False
        cmdETFastForward.Enabled = False
        cmdETRewind.Enabled = False
        cmdStart.Enabled = False
        cmdStop.Enabled = False

        If Not IcImagingControl1.DeviceValid Then
            IcImagingControl1.ShowDeviceSettingsDialog()

            If Not IcImagingControl1.DeviceValid Then
                MessageBox.Show("No device was selected.")
                Me.Close()
                Exit Sub
            End If
        End If

        cmdStart.Enabled = True
        cmdStop.Enabled = True

        ' Check whether external transport is available.
        If IcImagingControl1.ExternalTransportAvailable = True Then
            cmdETPlay.Enabled = True
            cmdETStop.Enabled = True
            cmdETFastForward.Enabled = True
            cmdETRewind.Enabled = True
        End If
    End Sub
	
    ''' <summary>
    ''' cmdStart_Click
    '''
    ''' Starts the live video and, if external transport is available,
    ''' starts the drive of the DV Device.
    ''' If the external transport is not set to ET_MODE_PLAY after
    ''' LiveStart has been called, no live image can be seen.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdStart_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStart.Click
        IcImagingControl1.LiveStart()
        If IcImagingControl1.ExternalTransportAvailable = True Then
            cmdETPlay_Click(sender, e)
        End If
    End Sub
    
    ''' <summary>
    ''' cmdStop_Click
    '''
    ''' Stop the live video display.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStop.Click
        IcImagingControl1.LiveStop()
    End Sub
    
    ''' <summary>
    ''' cmdETPlay_Click
    '''
    ''' Advises the DV device to start playing.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdETPlay_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdETPlay.Click
        IcImagingControl1.ExternalTransportMode = TIS.Imaging.ExternalTransportModes.ET_MODE_PLAY
    End Sub
    
    ''' <summary>
    ''' cmdETStop_Click
    '''
    ''' Advises the DV device to stop playing.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdETStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdETStop.Click
        IcImagingControl1.ExternalTransportMode = TIS.Imaging.ExternalTransportModes.ET_MODE_STOP
    End Sub
    
    ''' <summary>
    ''' cmdETFastForward_Click
    '''
    ''' Advises the DV device to fast forward.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdETFastForward_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdETFastForward.Click
        IcImagingControl1.ExternalTransportMode = TIS.Imaging.ExternalTransportModes.ET_MODE_FASTFORWARD
    End Sub
    
    ''' <summary>
    ''' cmdEtRewind_Click
    '''
    ''' Advises the DV device to rewind.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdETRewind_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdETRewind.Click
        IcImagingControl1.ExternalTransportMode = TIS.Imaging.ExternalTransportModes.ET_MODE_REWIND
    End Sub
    
End Class
