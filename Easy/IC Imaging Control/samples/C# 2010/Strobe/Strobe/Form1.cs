using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using TIS.Imaging;
using TIS.Imaging.VCDHelpers;

namespace Strobe
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

		        // Declare an object of the VCDSimpleProperty class. This class provides
        // simple access to the properties of a video capture device.
        VCDSimpleProperty VCDProp;
		
		        private void Form1_Load(object sender, EventArgs e)
        {
            // If no device is selected yet, show the selection dialog
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

            // Initialize the VCDProp class to access the properties of our ICImagingControl
            // object
            VCDProp = VCDSimpleModule.GetSimplePropertyContainer(icImagingControl1.VCDPropertyItems);

            // Initialize the sliders
            if (!VCDProp.SwitchAvailable(VCDIDs.VCDID_Strobe))
            {
                chkStrobe.Enabled = false;
            }
            else
            {
                chkStrobe.Enabled = true;
                // Set the strobe checkbox to the current state to the strobe in
                // the video capture device.
                if (VCDProp.Switch[VCDIDs.VCDID_Strobe] == true)
                {
                    chkStrobe.CheckState = CheckState.Checked;
                }
                else
                {
                    chkStrobe.CheckState = CheckState.Unchecked;
                }
            }

            // start live mode
            icImagingControl1.LiveStart();
        }
		
        /// <summary>
        /// chkStrobe_CheckedChanged
        ///
        /// If the user clicks the strobe checkbox, the strobe of the video capture
        /// device is enabled or disabled regarding to the current state of the
        /// the check box. The strobe uses the "Switch" interface.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void chkStrobe_CheckedChanged(object sender, EventArgs e)
        {
            if (chkStrobe.CheckState == CheckState.Checked)
            {
                VCDProp.Switch[VCDIDs.VCDID_Strobe] = true;
            }
            else
            {
                VCDProp.Switch[VCDIDs.VCDID_Strobe] = false;
            }
        }



    }
}