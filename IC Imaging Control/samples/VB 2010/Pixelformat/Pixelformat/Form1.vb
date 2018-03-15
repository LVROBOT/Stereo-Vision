Public Class Form1

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        If Not IcImagingControl1.DeviceValid Then

            IcImagingControl1.ShowDeviceSettingsDialog()

            If Not IcImagingControl1.DeviceValid Then
                Close()
                Return
            End If
        End If

        cmdYGB0.Enabled = IcImagingControl1.VideoFormat.StartsWith("YGB0")
		cmdYGB1.Enabled = IcImagingControl1.VideoFormat.StartsWith("YGB1")
		cmdY16.Enabled = IcImagingControl1.VideoFormat.StartsWith("Y16")

        IcImagingControl1.OverlayBitmapPosition = TIS.Imaging.PathPositions.None
        IcImagingControl1.LiveCaptureLastImage = False
        IcImagingControl1.LiveStart()
    End Sub

    Private ReadOnly Property CurrentVideoFormat() As TIS.Imaging.VideoFormat
        Get
            For Each fmt As TIS.Imaging.VideoFormat In IcImagingControl1.VideoFormats
                If fmt.Name = IcImagingControl1.VideoFormat Then
                    Return fmt
                End If
            Next

            Throw New System.Exception("Invalid video format selected")
        End Get
    End Property

    Private Function GrabImage(ByVal colorFormat As Guid) As TIS.Imaging.ImageBuffer

        Dim wasLive As Boolean = IcImagingControl1.LiveVideoRunning
        IcImagingControl1.LiveStop()

        Dim oldSink As TIS.Imaging.BaseSink = IcImagingControl1.Sink

        Dim fhs As New TIS.Imaging.FrameHandlerSink
        fhs.FrameTypes.Add(New TIS.Imaging.FrameType(colorFormat))

        IcImagingControl1.Sink = fhs

        Try
            IcImagingControl1.LiveStart()
        Catch ex As System.Exception
            MessageBox.Show(ex.Message)
            Return Nothing
        End Try

        Dim rval As TIS.Imaging.ImageBuffer

        Try
            fhs.SnapImage(1000)
            rval = fhs.LastAcquiredBuffer
        Catch ex As System.Exception
            MessageBox.Show(ex.Message)
        End Try

        IcImagingControl1.LiveStop()

        IcImagingControl1.Sink = oldSink

        If wasLive Then IcImagingControl1.LiveStart()

        Return rval
    End Function

    Private Sub cmdY800_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdY800.Click
        Dim buf As TIS.Imaging.ImageBuffer = GrabImage(TIS.Imaging.MediaSubtypes.Y800)
        If buf Is Nothing Then Return

                ' Y800 is top-down, the first line has index 0
        Dim y As Integer = 0

        txtOutput.Text = "Image buffer pixel format is Y800" & vbCrLf
        txtOutput.Text &= "Pixel 1: " & buf(0, y) & vbCrLf
        txtOutput.Text &= "Pixel 2: " & buf(1, y)
        
                ' Set the first pixel to 0 (black)
        buf(0, y) = 0
        ' Set the second pixel to 128 (gray)
        buf(1, y) = 128
        ' Set the third pixel to 255 (white)
        buf(2, y) = 255

        buf.SaveAsBitmap("Y800.bmp")
            End Sub

    Private Sub cmdRGB8_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdRGB8.Click
        Dim buf As TIS.Imaging.ImageBuffer = GrabImage(TIS.Imaging.MediaSubtypes.RGB8)
        If buf Is Nothing Then Return

                ' RGB8 is top-down, the first line has index lines-1
        Dim y As Integer = buf.Lines - 1

        txtOutput.Text = "Image buffer pixel format is RGB8" & vbCrLf
        txtOutput.Text &= "Pixel 1: " & buf(0, y) & vbCrLf
        txtOutput.Text &= "Pixel 2: " & buf(1, y)
        
                ' Set the first pixel to 0 (black)
        buf(0, y) = 0
        ' Set the second pixel to 128 (gray)
        buf(1, y) = 128
        ' Set the third pixel to 255 (white)
        buf(2, y) = 255

        buf.SaveAsBitmap("RGB8.bmp")
            End Sub

    Private Sub cmdRGB24_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdRGB24.Click
        Dim buf As TIS.Imaging.ImageBuffer = GrabImage(TIS.Imaging.MediaSubtypes.RGB24)
        If buf Is Nothing Then Return

                ' RGB24 is bottom-up, the first line has index lines-1
        Dim y As Integer = buf.Lines - 1

        txtOutput.Text = "Image buffer pixel format is RGB24" & vbCrLf
        txtOutput.Text &= "Pixel 1: "
        txtOutput.Text &= "R=" & buf(0 * 3 + 2, y) & ", "
        txtOutput.Text &= "G=" & buf(0 * 3 + 1, y) & ", "
        txtOutput.Text &= "B=" & buf(0 * 3 + 0, y) & vbCrLf
        txtOutput.Text &= "Pixel 2: "
        txtOutput.Text &= "R=" & buf(1 * 3 + 2, y) & ", "
        txtOutput.Text &= "G=" & buf(1 * 3 + 1, y) & ", "
        txtOutput.Text &= "B=" & buf(1 * 3 + 0, y)
        
                ' Set the first pixel to red (255 0 0)
        buf(0 * 3 + 2, y) = 255
        buf(0 * 3 + 1, y) = 0
        buf(0 * 3 + 0, y) = 0
        ' Set the second pixel to 128 (gray)
        buf(1 * 3 + 2, y) = 0
        buf(1 * 3 + 1, y) = 255
        buf(1 * 3 + 0, y) = 0
        ' Set the third pixel to 255 (white)
        buf(2 * 3 + 2, y) = 0
        buf(2 * 3 + 1, y) = 0
        buf(2 * 3 + 0, y) = 255

        buf.SaveAsBitmap("RGB24.bmp")
            End Sub

    Private Sub cmdRGB32_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdRGB32.Click
        Dim buf As TIS.Imaging.ImageBuffer = GrabImage(TIS.Imaging.MediaSubtypes.RGB32)
        If buf Is Nothing Then Return

                ' RGB32 is bottom-up, the first line has index lines-1
        Dim y As Integer = buf.Lines - 1

        txtOutput.Text = "Image buffer pixel format is RGB32" & vbCrLf
        txtOutput.Text &= "Pixel 1: "
        txtOutput.Text &= "R=" & buf(0 * 4 + 2, y) & ", "
        txtOutput.Text &= "G=" & buf(0 * 4 + 1, y) & ", "
        txtOutput.Text &= "B=" & buf(0 * 4 + 0, y) & vbCrLf
        txtOutput.Text &= "Pixel 2: "
        txtOutput.Text &= "R=" & buf(1 * 4 + 2, y) & ", "
        txtOutput.Text &= "G=" & buf(1 * 4 + 1, y) & ", "
        txtOutput.Text &= "B=" & buf(1 * 4 + 0, y)
        
                ' Set the first pixel to red (255 0 0)
        buf(0 * 4 + 2, y) = 255
        buf(0 * 4 + 1, y) = 0
        buf(0 * 3 + 0, y) = 0
        ' Set the second pixel to 128 (gray)
        buf(1 * 4 + 2, y) = 0
        buf(1 * 4 + 1, y) = 255
        buf(1 * 4 + 0, y) = 0
        ' Set the third pixel to 255 (white)
        buf(2 * 4 + 2, y) = 0
        buf(2 * 4 + 1, y) = 0
        buf(2 * 4 + 0, y) = 255

        buf.SaveAsBitmap("RGB32.bmp")
            End Sub

        Private Function IntValueFromYGB1Bytes(ByVal b1 As Byte, ByVal b2 As Byte) As Integer
        Return (CInt(b1) << 8) Or CInt(b2)
    End Function

    Private Function YGB1BytesFromIntValue(ByVal val As Integer, ByRef b1 As Byte, ByRef b2 As Byte)
        b1 = CByte(val >> 8)
        b2 = CByte(val And 255)
    End Function
    
    Private Sub cmdYGB1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdYGB1.Click
        Dim buf As TIS.Imaging.ImageBuffer = GrabImage(TIS.Imaging.MediaSubtypes.YGB1)
        If buf Is Nothing Then Return

                ' YGB1 is top-down, the first line has index 0
        Dim y As Integer = 0

        Dim val0 As Integer = IntValueFromYGB1Bytes(buf(0, y), buf(1, y))
        Dim val1 As Integer = IntValueFromYGB1Bytes(buf(2, y), buf(3, y))

        txtOutput.Text = "Image buffer pixel format is YGB1" & vbCrLf
        txtOutput.Text &= "Pixel 1: " & val0 & vbCrLf
        txtOutput.Text &= "Pixel 2: " & val1
        
                Dim b1, b2 As Byte
        YGB1BytesFromIntValue(0, b1, b2)
        buf(0, y) = b1
        buf(1, y) = b2
        YGB1BytesFromIntValue(512, b1, b2)
        buf(2, y) = b1
        buf(3, y) = b2
        YGB1BytesFromIntValue(1023, b1, b2)
        buf(4, y) = b1
        buf(5, y) = b2

        buf.SaveAsBitmap("ygb1.bmp", TIS.Imaging.ICImagingControlColorformats.ICY800)
            End Sub

        Private Function IntValueFromYGB0Bytes(ByVal b1 As Byte, ByVal b2 As Byte) As Integer
        Return (((CInt(b1) << 8) Or CInt(b2)) >> 6)
    End Function

    Private Function YGB0BytesFromIntValue(ByVal val As Integer, ByRef b1 As Byte, ByRef b2 As Byte)
        val <<= 6
        b1 = CByte(val >> 8)
        b2 = CByte(val & 255)
    End Function
    
    Private Sub cmdYGB0_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdYGB0.Click
        Dim buf As TIS.Imaging.ImageBuffer = GrabImage(TIS.Imaging.MediaSubtypes.YGB0)
        If buf Is Nothing Then Return

                ' YGB0 is top-down, the first line has index 0
        Dim y As Integer = 0

        Dim val0 As Integer = IntValueFromYGB0Bytes(buf(0, y), buf(1, y))
        Dim val1 As Integer = IntValueFromYGB0Bytes(buf(2, y), buf(3, y))

        txtOutput.Text = "Image buffer pixel format is YGB0" & vbCrLf
        txtOutput.Text &= "Pixel 1: " & val0 & vbCrLf
        txtOutput.Text &= "Pixel 2: " & val1
        
                Dim b1, b2 As Byte
        YGB0BytesFromIntValue(0, b1, b2)
        buf(0, y) = b1
        buf(1, y) = b2
        YGB0BytesFromIntValue(512, b1, b2)
        buf(2, y) = b1
        buf(3, y) = b2
        YGB0BytesFromIntValue(1023, b1, b2)
        buf(4, y) = b1
        buf(5, y) = b2

        buf.SaveAsBitmap("ygb0.bmp", TIS.Imaging.ICImagingControlColorformats.ICY800)
            End Sub


		Private Function IntValueFromY16Bytes(ByVal b1 As Byte, ByVal b2 As Byte) As Integer
		Return (((CInt(b1) << 8) Or CInt(b2)) >> 6)
	End Function

	Private Function Y16BytesFromIntValue(ByVal val As Integer, ByRef b1 As Byte, ByRef b2 As Byte)
		val <<= 6
		b1 = CByte(val >> 8)
		b2 = CByte(val & 255)
	End Function
	
		Private Function ToUInt16(ByVal s As Int16) As UInt16
		If (s And &H8000) = 0 Then
			Return CType(s, UInt16)
		Else
			Return CType(UInt16.MaxValue + 1 + CType(s, Int32), UInt16)
		End If
	End Function

	Private Function ReadY16(ByVal buf As TIS.Imaging.ImageBuffer, ByVal row As Integer, ByVal col As Integer) As UInt16
		' Y16 is top-down, the first line has index 0
		Dim offset As Integer = row * buf.BytesPerLine + col * 2

		Dim val As Int16 = System.Runtime.InteropServices.Marshal.ReadInt16(buf.GetIntPtr(), offset)

		Return ToUInt16(val)
	End Function
	
		Private Function ToInt16(ByVal us As UInt16) As Int16
		If (us And &H8000) = 0 Then
			Return CType(us, Int16)
		Else
			Return CType(CType(us, Int32) - UInt16.MaxValue - 1, Int16)
		End If
	End Function

	Private Sub WriteY16(ByVal buf As TIS.Imaging.ImageBuffer, ByVal row As Integer, ByVal col As Integer, ByVal value As UInt16)

		Dim offset As Integer = row * buf.BytesPerLine + col * 2

		System.Runtime.InteropServices.Marshal.WriteInt16(buf.GetIntPtr(), offset, ToInt16(value))
	End Sub
	
	Private Sub cmdY16_Click(sender As Object, e As EventArgs) Handles cmdY16.Click
		Dim buf As TIS.Imaging.ImageBuffer = GrabImage(TIS.Imaging.MediaSubtypes.Y16)
		If buf Is Nothing Then Return

				Dim val0 As UInt16 = ReadY16(buf, 0, 0)
		Dim val1 As UInt16 = ReadY16(buf, 0, 1)

		txtOutput.Text = "Image buffer pixel format is Y16" & vbCrLf
		txtOutput.Text &= "Pixel 1: " & val0 & vbCrLf
		txtOutput.Text &= "Pixel 2: " & val1
		
				WriteY16(buf, 0, 0, &H0) ' Black
		WriteY16(buf, 0, 1, &H8000)	' Gray
		WriteY16(buf, 0, 2, &HFFFF)	' White

		buf.SaveAsTiff("y16.tiff")
			End Sub
End Class
