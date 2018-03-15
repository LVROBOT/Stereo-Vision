using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Saving_Codec_Properties
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        // Global AVICompressor object
		        private TIS.Imaging.AviCompressor Codec;
		        /// <summary>
        /// Form_Load
        ///
        /// Gets all available codecs from ICImagingControl and
        /// put their names in the cboVideoCodec combo box.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void Form1_Load(object sender, EventArgs e)
        {
            // Insert all installed codecs into the cboVideoCodec combobox.
            foreach (TIS.Imaging.AviCompressor _Codec in icImagingControl1.AviCompressors)
            {
                cboVideoCodec.Items.Add(_Codec);
            }
            // Show the first codec in the combobox.
            cboVideoCodec.SelectedIndex = 0;

            Codec = (TIS.Imaging.AviCompressor)cboVideoCodec.SelectedItem;

            // Enable or disable the buttons.
            cmdShowPropertyPage.Enabled = Codec.PropertyPageAvailable;
            cmdLoadData.Enabled = Codec.PropertyPageAvailable;
            cmdSaveData.Enabled = Codec.PropertyPageAvailable;
        }
		
        /// <summary>
        /// cboVideoCodec_SelectedValueChanged
        ///
        /// If the selected codec has a property dialog, the buttons
        /// will be enabled.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cboVideoCodec_SelectedIndexChanged(object sender, EventArgs e)
        {
            Codec = (TIS.Imaging.AviCompressor)cboVideoCodec.SelectedItem;
            // Enable or disable the buttons.
            cmdShowPropertyPage.Enabled = Codec.PropertyPageAvailable;
            cmdLoadData.Enabled = Codec.PropertyPageAvailable;
            cmdSaveData.Enabled = Codec.PropertyPageAvailable;
        }
		
        /// <summary>
        /// cmdShowPropertyPage_Click
        ///
        /// Shows the property dialog of a codec by calling its
        /// ShowPropertyPage Method.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdShowPropertyPage_Click(object sender, EventArgs e)
        {
            Codec.ShowPropertyPage();
        }
		
        /// <summary>
        /// cmdSaveData_Click
        ///
        /// Gets the binary data from the codec and saves it
        /// into the binary opened file "test.bin".
        /// To make sure that the saved file will match the used
        /// codec, the name of the codec will be saved in the file.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdSaveData_Click(object sender, EventArgs e)
        {
            try
            {
                System.IO.FileStream Filestream = new System.IO.FileStream("test.bin", System.IO.FileMode.Create, System.IO.FileAccess.Write);
                System.IO.BinaryWriter BinWriter = new System.IO.BinaryWriter(Filestream);
                BinWriter.Write(Codec.Name);
                BinWriter.Write(Codec.CompressorDataSize);
                BinWriter.Write(Codec.CompressorData);

                BinWriter.Close();
                Filestream.Close();
            }
            catch (Exception Ex)
            {
                MessageBox.Show(Ex.Message);
            }
        }
		
        /// <summary>
        /// cmdLoadData_Click
        ///
        /// Loads binary data from a file "test.bin" and assigns
        /// it to the codec
        /// To check, whether the file matches the used codec, the
        /// name of the codec was saved in the file. Now, it will be
        /// loaded first from the file and compared with Codec.Name.
        /// If they are identical, the binary data can be assigned
        /// to the codec. Please refer to cmdSaveData_Click().
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdLoadData_Click(object sender, EventArgs e)
        {
            try
            {
                System.IO.FileStream Filestream = new System.IO.FileStream("test.bin", System.IO.FileMode.Open, System.IO.FileAccess.Read);
                System.IO.BinaryReader BinReader = new System.IO.BinaryReader(Filestream);
                String CodecName;

                // Retrieve the name of the codec from the codec configuration file
                CodecName = BinReader.ReadString();

                //Compare the codec name in the file with the current codec's name.
                if (Codec.Name == CodecName)
                {
                    // Read the length of the binary data.
                    int codecDataLen = BinReader.ReadInt32();
                    // Assign the configuration data to the codec.
                    Codec.CompressorData = BinReader.ReadBytes(codecDataLen);
                }
                else
                {
                    MessageBox.Show("The saved data does not match to the used codec.\n" +
                            "saved: " + CodecName + "\n" +
                            "used: " + Codec.Name);
                }
                BinReader.Close();
                Filestream.Close();
            }
            catch (Exception Ex)
            {
                MessageBox.Show(Ex.Message);
            }
        }
		
    }
}