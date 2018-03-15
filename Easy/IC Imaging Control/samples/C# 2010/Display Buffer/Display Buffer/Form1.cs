using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Display_Buffer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Form_Load
        ///
        /// Initializes the buttons and sets the size of the control
        /// to the size of the currently selected video format.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void Form1_Load(object sender, EventArgs e)
        {
            // Check if a valid video capture device has been selected, otherwise
            // show the device selection dialog of Imaging Control.
            if (!icImagingControl1.DeviceValid)
            {
                icImagingControl1.ShowDeviceSettingsDialog();

                if (!icImagingControl1.DeviceValid)
                {
                    MessageBox.Show("No device was selected.", "Display Buffer",
                                    MessageBoxButtons.OK, MessageBoxIcon.Information);
                    this.Close();
                    return;
                }
            }

            cmdStop.Enabled = false;
            icImagingControl1.LiveDisplayDefault = false;
            icImagingControl1.LiveDisplayHeight = icImagingControl1.Height;
            icImagingControl1.LiveDisplayWidth = icImagingControl1.Width;

            icImagingControl1.LiveCaptureContinuous = true;
            icImagingControl1.LiveDisplay = false;
        }
		
        /// <summary>
        /// cmdStart
        ///
        /// Starts the Display.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdStart_Click(object sender, EventArgs e)
        {
            icImagingControl1.LiveStart();
            cmdStart.Enabled = false;
            cmdStop.Enabled = true;
        }
		
        /// <summary>
        /// cmdStop
        ///
        /// Stops the Display.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdStop_Click(object sender, EventArgs e)
        {
            cmdStart.Enabled = true;
            cmdStop.Enabled = false;
            icImagingControl1.LiveStop();
        }
		
        /// <summary>
        /// ICImagingControl1_ImageAvailable
        ///
        /// Retrieves the buffer specified by BufferIndex
        /// from the collection and displays it in the control window.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void icImagingControl1_ImageAvailable(object sender, TIS.Imaging.ICImagingControl.ImageAvailableEventArgs e)
        {
            try
            {
                TIS.Imaging.ImageBuffer CurrentBuffer = null;

                CurrentBuffer = icImagingControl1.ImageBuffers[e.bufferIndex];
                icImagingControl1.DisplayImageBuffer(CurrentBuffer);
            }
            catch (Exception ex)
            {
                System.Diagnostics.Trace.WriteLine(ex.Message);
            }
        }
		
        private void Form1_SizeChanged(object sender, EventArgs e)
        {
            if (icImagingControl1.DeviceValid)
            {
                icImagingControl1.LiveDisplayHeight = icImagingControl1.Height;
                icImagingControl1.LiveDisplayWidth = icImagingControl1.Width;
            }
        }


    }
}