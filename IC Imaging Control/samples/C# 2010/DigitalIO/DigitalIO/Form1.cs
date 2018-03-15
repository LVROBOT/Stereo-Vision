using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using TIS.Imaging;
using TIS.Imaging.VCDHelpers;

namespace DigitalIO
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

		        /// <summary>
        ///Declare an object of the VCDSimpleProperty class. This class provides
        /// simple access to the properties of a video capture device.
        /// </summary>
        private VCDSimpleProperty VCDProp;
		
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

            // First of all, check, whether the digital IOs are supported by the
            // current video capture device.
            if (VCDProp.Available(VCDIDs.VCDID_GPIO))
            {
                // Get the digital input state.
                cmdReadDigitalInput.Enabled = true;
                ReadDigitalInput();

                // Get the digital output state.
                cmdWriteDigitalOutput.Enabled = true;
                chkDigitalOutputState.Enabled = true;
                if (VCDProp.RangeValue[VCDIDs.VCDElement_GPIOOut] == 1)
                {
                    chkDigitalOutputState.CheckState = CheckState.Checked;
                }
                else
                {
                    chkDigitalOutputState.CheckState = CheckState.Unchecked;
                }
            }
            else
            {
                cmdReadDigitalInput.Enabled = false;
                cmdWriteDigitalOutput.Enabled = false;
                chkDigitalOutputState.Enabled = false;
            }

            // Initialize the sliders
            // start live mode
            icImagingControl1.LiveStart();
        }
		
        /// <summary>
        /// ReadDigitalInput
        ///
        /// Send the push for read out to the video capture device. Then set the
        /// input state check box to the current state of the digital input.
        /// </summary>
        private void ReadDigitalInput()
        {
            // Read the digital input from the video capture device.
            VCDProp.OnePush(VCDIDs.VCDElement_GPIORead);

            // Set the state of the digital input to the chkDigitalInputState
            // check box.
            if (VCDProp.RangeValue[VCDIDs.VCDElement_GPIOIn] == 1)
            {
                chkDigitalInputState.CheckState = CheckState.Checked;
            }
            else
            {
                chkDigitalInputState.CheckState = CheckState.Unchecked;
            }
        }

        private void cmdReadDigitalInput_Click(object sender, EventArgs e)
        {
            ReadDigitalInput();
        }

        /// <summary>
        /// cmdWriteDigitalOutput_Click
        ///
        /// The state of the chkDigitalOutputState check box is set to the video 
        /// capture device' digital output property. 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmdWriteDigitalOutput_Click(object sender, EventArgs e)
        {
            // Set the state.
            if (chkDigitalOutputState.CheckState == CheckState.Checked)
            {
                VCDProp.RangeValue[VCDIDs.VCDElement_GPIOOut] = 1;
            }
            else
            {
                VCDProp.RangeValue[VCDIDs.VCDElement_GPIOOut] = 0;
            }

            // Now write it into the video capture device.
            VCDProp.OnePush(VCDIDs.VCDElement_GPIOWrite);
        }
    }
}