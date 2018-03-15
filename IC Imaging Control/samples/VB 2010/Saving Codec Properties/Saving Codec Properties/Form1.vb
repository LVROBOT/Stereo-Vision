Public Class Form1

    ' Global AVICompressor object
        Dim Codec As TIS.Imaging.AviCompressor
        ''' <summary>
    ''' Form_Load
    '''
    ''' Gets all available codecs from ICImagingControl and
    ''' put their names in the cboVideoCodec combo box.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        'Insert all installed codecs into the cboVideoCodec combobox.
        For Each Codec As TIS.Imaging.AviCompressor In IcImagingControl1.AviCompressors
            cboVideoCodec.Items.Add(Codec)
        Next
        ' Show the first codec in the combobox.
        cboVideoCodec.SelectedIndex = 0

        Codec = CType(cboVideoCodec.SelectedItem(), TIS.Imaging.AviCompressor)

        ' Enable or disable the buttons.
        cmdShowPropertyPage.Enabled = Codec.PropertyPageAvailable
        cmdLoadData.Enabled = Codec.PropertyPageAvailable
        cmdSaveData.Enabled = Codec.PropertyPageAvailable
    End Sub
    
    ''' <summary>
    ''' cboVideoCodec_SelectedValueChanged
    '''
    ''' If the selected codec has a property dialog, the buttons
    ''' will be enabled.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cboVideoCodec_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cboVideoCodec.SelectedIndexChanged
        Codec = CType(cboVideoCodec.SelectedItem(), TIS.Imaging.AviCompressor)

        ' Enable or disable the buttons.
        cmdShowPropertyPage.Enabled = Codec.PropertyPageAvailable
        cmdLoadData.Enabled = Codec.PropertyPageAvailable
        cmdSaveData.Enabled = Codec.PropertyPageAvailable
    End Sub
    
    ''' <summary>
    ''' cmdShowPropertyPage_Click
    '''
    ''' Shows the property dialog of a codec by calling its
    ''' ShowPropertyPage Method.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdShowPropertyPage_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdShowPropertyPage.Click
        Codec.ShowPropertyPage()
    End Sub
    
    ''' <summary>
    ''' cmdSaveData_Click
    '''
    ''' Gets the binary data from the codec and saves it
    ''' into the binary opened file "test.bin".
    ''' To make sure that the saved file will match the used
    ''' codec, the name of the codec will be saved in the file.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdSaveData_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdSaveData.Click
        Try
            Dim Filestream As New System.IO.FileStream("test.bin", System.IO.FileMode.Create, System.IO.FileAccess.Write)

            ' Create the writer for data.
            Dim BinWriter As New System.IO.BinaryWriter(Filestream)

            BinWriter.Write(Codec.ToString())
            BinWriter.Write(Codec.CompressorDataSize)
            BinWriter.Write(Codec.CompressorData)

            BinWriter.Close()
            Filestream.Close()

        Catch ex As System.Exception
            MsgBox(ex.Message, MsgBoxStyle.Critical, "Write error")
        End Try
    End Sub
    
    ''' <summary>
    ''' cmdLoadData_Click
    '''
    ''' Loads binary data from a file "test.bin" and assigns
    ''' it to the codec
    ''' To check, whether the file matches the used codec, the
    ''' name of the codec was saved in the file. Now, it will be
    ''' loaded first from the file and compared with Codec.Name.
    ''' If they are identical, the binary data can be assigned
    ''' to the codec. Please refer to cmdSaveData_Click().
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    ''' <remarks></remarks>
        Private Sub cmdLoadData_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdLoadData.Click
        Try
            ' Create the reader for data.
            Dim Filestrem As New System.IO.FileStream("test.bin", System.IO.FileMode.Open, System.IO.FileAccess.Read)
            Dim BinReader As New System.IO.BinaryReader(Filestrem)

            Dim CodecName As String

            ' Retrieve the name of the codec from the codec configuration file.
            CodecName = BinReader.ReadString()

            ' Compare the codec name in the file with the current codec's name.
            If Codec.Name = CodecName Then
                Dim codecDataLen As Integer = BinReader.ReadInt32()
                ' Assign the configuration data to the codec.
                Codec.CompressorData = BinReader.ReadBytes(codecDataLen)
            Else
                MsgBox("The saved data does not match to the used codec." + Chr(13) + _
                       "saved: " + CodecName + Chr(13) + _
                       "used: " + Codec.Name)
            End If
            BinReader.Close()
            Filestrem.Close()
        Catch ex As System.Exception
            MsgBox(ex.Message, MsgBoxStyle.Critical, "Read error")
        End Try
    End Sub
    
End Class
