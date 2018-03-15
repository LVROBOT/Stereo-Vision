Public Class Form1

    ''' <summary>
    ''' Form_Load
    '''
    ''' Initializes the buttons and sets the size of the control
    ''' to the size of the currently selected video format.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' Check if a valid video capture device has been selected, otherwise
        ' show the device selection dialog of Imaging Control.
        If Not IcImagingControl1.DeviceValid Then
            IcImagingControl1.ShowDeviceSettingsDialog()

            If Not IcImagingControl1.DeviceValid Then
                MessageBox.Show("No device was selected.", "Display Buffer Sample")
                Me.Close()
                Exit Sub
            End If
        End If

        cmdStop.Enabled = False
        IcImagingControl1.Width = IcImagingControl1.ImageWidth
        IcImagingControl1.Height = IcImagingControl1.ImageHeight
    End Sub
    
    ''' <summary>
    ''' cmdStart
    '''
    ''' Starts the Display.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdStart_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStart.Click
        IcImagingControl1.LiveStart()
        cmdStart.Enabled = False
        cmdStop.Enabled = True
    End Sub
    
    ''' <summary>
    ''' cmdStop
    '''
    ''' Stops the Display.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdStop.Click
        cmdStart.Enabled = True
        cmdStop.Enabled = False
        IcImagingControl1.LiveStop()
    End Sub
    
    ''' <summary>
    ''' ICImagingControl1_ImageAvailable
    '''
    ''' Retrieves the buffer specified by BufferIndex
    ''' from the collection and displays it in the control window.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub IcImagingControl1_ImageAvailable(ByVal sender As System.Object, ByVal e As TIS.Imaging.ICImagingControl.ImageAvailableEventArgs) Handles IcImagingControl1.ImageAvailable
        Try
            Dim CurrentBuffer As TIS.Imaging.ImageBuffer

            CurrentBuffer = IcImagingControl1.ImageBuffers(e.bufferIndex)
            IcImagingControl1.DisplayImageBuffer(CurrentBuffer)

        Catch ex As System.Exception
            System.Diagnostics.Trace.WriteLine(ex.Message)
        End Try
    End Sub
    
End Class
