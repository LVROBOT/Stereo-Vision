using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace VCD_Simple
{
    public partial class Form1 : Form
    {
        // These variables will hold the interfaces to the brightness property
		        private TIS.Imaging.VCDRangeProperty BrightnessRange;
        private TIS.Imaging.VCDSwitchProperty BrightnessSwitch;
		
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Form1_Load
        ///
        /// Check whether a device has been specified in the properties of IC Imaging
        /// Control. If there is no device, show the device selection dialog.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            // Create a VCDPropertyItem for brightness.
            TIS.Imaging.VCDPropertyItem Brightness = null;

            sldBrightness.Enabled = false;
            chkBrightnessAuto.Enabled = false;

            if (icImagingControl1.DeviceValid == false)
            {
                icImagingControl1.ShowDeviceSettingsDialog();
            }

            if (icImagingControl1.DeviceValid)
            {
                if (GetBrightnessItem() == true)
                {
					                    // Initialize the slider with the current range and value of the
                    // BrightnessRange object.
                    sldBrightness.Enabled = true;
                    sldBrightness.Minimum = BrightnessRange.RangeMin;
                    sldBrightness.Maximum = BrightnessRange.RangeMax;
                    sldBrightness.Value = BrightnessRange.Value;

                    // Initialize the checkbox with the BrightnessSwitch object
                    if (BrightnessSwitch != null)
                    {
                        chkBrightnessAuto.Enabled = true;
                        sldBrightness.Enabled = !BrightnessSwitch.Switch;
                        chkBrightnessAuto.Checked = BrightnessSwitch.Switch;
                    }
                    icImagingControl1.LiveStart();
					                }
            }
        }

        /// <summary>
        /// GetBrightnessItem
        ///
        /// Retrieve the brightness VCDPropertyItem and assign BrightnessSwitch and BrightnessRange.
        /// The function returns true, if the property exists. If the property does not
        /// exists, the function returns false.
        /// </summary>
        /// <returns></returns>
        private bool GetBrightnessItem()
        {
            bool bPropertyFound = false;
            // Try Find brightness property in the VCDPropertyItems collection.
            // If brightness is not support by the current video capture device,
            // an excpetion is thrown.
			            TIS.Imaging.VCDPropertyItem Brightness = null;
            Brightness = icImagingControl1.VCDPropertyItems.FindItem(TIS.Imaging.VCDIDs.VCDID_Brightness);
						if (Brightness != null)
            {
                bPropertyFound = true;
				                // Acquire interfaces to the range and switch interface for value and auto
                BrightnessRange = (TIS.Imaging.VCDRangeProperty)Brightness.Elements.FindInterface(
                                                                    TIS.Imaging.VCDIDs.VCDElement_Value + ":" +
                                                                    TIS.Imaging.VCDIDs.VCDInterface_Range);
                BrightnessSwitch = (TIS.Imaging.VCDSwitchProperty)Brightness.Elements.FindInterface(
                                                                    TIS.Imaging.VCDIDs.VCDElement_Auto + ":" +
                                                                    TIS.Imaging.VCDIDs.VCDInterface_Switch);
                if (BrightnessSwitch == null)
                {
                    MessageBox.Show("Automation of brightness is not supported by the current device!");
                }
				            }

            // Show a message box, if brightness is not supported.
            if (Brightness == null)
            {
                MessageBox.Show("Brightness property is not supported by the current device!");
            }
            return bPropertyFound;
        }

        /// <summary>
        /// chkBrightnessAuto_CheckedChanged
        ///
        /// Enable or disable the autmatic of the brightness property when the checkbox
        /// has been clicked.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void chkBrightnessAuto_CheckedChanged(object sender, EventArgs e)
        {
            BrightnessSwitch.Switch = chkBrightnessAuto.Checked;
            sldBrightness.Enabled = !chkBrightnessAuto.Checked;
        }
		
        /// <summary>
        /// sldBrightness_Scroll
        ///
        /// Set the brightness to the current slider position.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void sldBrightness_Scroll(object sender, EventArgs e)
        {
            BrightnessRange.Value = sldBrightness.Value;
        }
		
    }
}