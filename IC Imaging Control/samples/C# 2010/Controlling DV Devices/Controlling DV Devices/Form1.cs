using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Controlling_DV_Devices
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
        /// Check whether the video capture device supports external
        /// transport. If external transport is available, the buttons
        /// for external transports will be enabled.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void Form1_Load(object sender, EventArgs e)
        {
            cmdETPlay.Enabled = false;
            cmdETStop.Enabled = false;
            cmdETFastForward.Enabled = false;
            cmdETRewind.Enabled = false;
            cmdStart.Enabled = false;
            cmdStop.Enabled = false;

            if (!icImagingControl1.DeviceValid)
            {
                icImagingControl1.ShowDeviceSettingsDialog();

                if (!icImagingControl1.DeviceValid)
                {
                    MessageBox.Show("No device was selected.");
                    this.Close();
                    return;
                }
            }

            cmdStart.Enabled = true;
            cmdStop.Enabled = true;

            // Check whether external transport is available.
            if (icImagingControl1.ExternalTransportAvailable)
            {
                cmdETPlay.Enabled = true;
                cmdETStop.Enabled = true;
                cmdETFastForward.Enabled = true;
                cmdETRewind.Enabled = true;
            }
        }
		
		        private void cmdStart_Click(object sender, EventArgs e)
        {
            icImagingControl1.LiveStart();
            if (icImagingControl1.ExternalTransportAvailable)
            {
                cmdETPlay_Click(sender, e);
            }
        }
		
        /// <summary>
        /// cmdStop_Click
        ///
        /// Stop the live video display.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdStop_Click(object sender, EventArgs e)
        {
            icImagingControl1.LiveStop();
        }
		
        /// <summary>
        /// cmdETPlay_Click
        ///
        /// Advises the DV device to start playing.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdETPlay_Click(object sender, EventArgs e)
        {
            icImagingControl1.ExternalTransportMode = TIS.Imaging.ExternalTransportModes.ET_MODE_PLAY;
        }
		
        /// <summary>
        /// cmdETStop_Click
        ///
        /// Advises the DV device to stop playing.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdETStop_Click(object sender, EventArgs e)
        {
            icImagingControl1.ExternalTransportMode = TIS.Imaging.ExternalTransportModes.ET_MODE_STOP;
        }
		
        /// <summary>
        /// cmdEtRewind_Click
        ///
        /// Advises the DV device to rewind.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdETRewind_Click(object sender, EventArgs e)
        {
            icImagingControl1.ExternalTransportMode = TIS.Imaging.ExternalTransportModes.ET_MODE_REWIND;
        }
		
        /// <summary>
        /// cmdETFastForward_Click
        ///
        /// Advises the DV device to fast forward.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdETFastForward_Click(object sender, EventArgs e)
        {
            icImagingControl1.ExternalTransportMode = TIS.Imaging.ExternalTransportModes.ET_MODE_FASTFORWARD;
        }
		
    }
}