using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Grabbing_an_Image
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Form1_Load
        ///
        /// If no device has been selected in the properties window of IC Imaging
        /// Control, the device settings dialog of IC Imaging Control is show at
        /// start of this sample. 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            if (!icImagingControl1.DeviceValid)
            {
                icImagingControl1.ShowDeviceSettingsDialog();

                if (!icImagingControl1.DeviceValid)
                {
                    MessageBox.Show("No device was selected.", "Grabbing an Image",
                                     MessageBoxButtons.OK, MessageBoxIcon.Information);
                    this.Close();
                }
            }
        }

        /// <summary>
        /// cmdStartLive_Click
        ///
        /// Start the live video. A valid video capture device should have been
        /// selected previsously in the properties window of IC Imaging Control.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdStartLive_Click(object sender, EventArgs e)
        {
            icImagingControl1.LiveStart();
        }
		        /// <summary>
        /// cmdStopLive_Click
        ///
        /// Stop the live video.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdStopLive_Click(object sender, EventArgs e)
        {
            if (icImagingControl1.LiveVideoRunning == true)
                icImagingControl1.LiveStop();
        }
		
        /// <summary>
        /// cmdSaveBitmap_Click
        ///
        /// Snap an image from the live video stream and show the file save
        /// dialog. After a file name has been selected, the image is saved.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdSaveBitmap_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1;
            icImagingControl1.MemorySnapImage();
            saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "bmp files (*.bmp)|*.bmp|All files (*.*)|*.*";
            saveFileDialog1.FilterIndex = 1;
            saveFileDialog1.RestoreDirectory = true;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                icImagingControl1.MemorySaveImage(saveFileDialog1.FileName);
            }
        }
		    }
}