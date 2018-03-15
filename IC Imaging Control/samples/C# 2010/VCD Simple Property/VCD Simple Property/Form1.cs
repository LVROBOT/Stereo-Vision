using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using TIS.Imaging;

namespace VCD_Simple_Property
{
    public partial class Form1 : Form
    {
		        private TIS.Imaging.VCDHelpers.VCDSimpleProperty VCDProp;
		        public Form1()
        {
            InitializeComponent();
        }

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
            VCDProp = TIS.Imaging.VCDHelpers.VCDSimpleModule.GetSimplePropertyContainer(icImagingControl1.VCDPropertyItems);

            // Initialize the auto checkboxes
            if (!VCDProp.AutoAvailable(VCDIDs.VCDID_Brightness))
                BrightnessAutoCheckBox.Enabled = false;
            else
                VCDProp.Automation[VCDIDs.VCDID_Brightness] = false;

            if (!VCDProp.AutoAvailable(VCDIDs.VCDID_WhiteBalance))
            {
                WhitebalanceCheckBox.Enabled = false;
                WhitebalanceOnePushButton.Enabled = false;
            }
            else
                VCDProp.Automation[VCDIDs.VCDID_WhiteBalance] = false;


            // Initialize the sliders
            if (!VCDProp.Available(VCDIDs.VCDID_Brightness))
            {
                BrightnessTrackBar.Enabled = false;
            }
            else
            {
                BrightnessTrackBar.Enabled = true;
                BrightnessTrackBar.Minimum = VCDProp.RangeMin(VCDIDs.VCDID_Brightness);
                BrightnessTrackBar.Maximum = VCDProp.RangeMax(VCDIDs.VCDID_Brightness);
                BrightnessTrackBar.Value = VCDProp.RangeValue[VCDIDs.VCDID_Brightness];
                BrightnessTrackBar.TickFrequency = (BrightnessTrackBar.Maximum - BrightnessTrackBar.Minimum) / 10;
                BrightnessValueLabel.Text = BrightnessTrackBar.Value.ToString();
            }

            if (!VCDProp.Available(VCDIDs.VCDElement_WhiteBalanceBlue))
                WhiteBalBlueTrackBar.Enabled = false;
            else
            {
                WhiteBalBlueTrackBar.Enabled = true;
                WhiteBalBlueTrackBar.Minimum = VCDProp.RangeMin(VCDIDs.VCDElement_WhiteBalanceBlue);
                WhiteBalBlueTrackBar.Maximum = VCDProp.RangeMax(VCDIDs.VCDElement_WhiteBalanceBlue);
                WhiteBalBlueTrackBar.Value = VCDProp.RangeValue[VCDIDs.VCDElement_WhiteBalanceBlue];
                WhiteBalBlueTrackBar.TickFrequency = (WhiteBalBlueTrackBar.Maximum - WhiteBalBlueTrackBar.Minimum) / 10;
                WhiteBalBlueLabel.Text = WhiteBalBlueTrackBar.Value.ToString();
            }

            if (!VCDProp.Available(VCDIDs.VCDElement_WhiteBalanceRed))
                WhiteBalRedTrackBar.Enabled = false;
            else
            {
                WhiteBalRedTrackBar.Enabled = false;
                WhiteBalRedTrackBar.Enabled = true;
                WhiteBalRedTrackBar.Minimum = VCDProp.RangeMin(VCDIDs.VCDElement_WhiteBalanceRed);
                WhiteBalRedTrackBar.Maximum = VCDProp.RangeMax(VCDIDs.VCDElement_WhiteBalanceRed);
                WhiteBalRedTrackBar.Value = VCDProp.RangeValue[VCDIDs.VCDElement_WhiteBalanceRed];
                WhiteBalRedTrackBar.TickFrequency = (WhiteBalRedTrackBar.Maximum - WhiteBalRedTrackBar.Minimum) / 10;
                WhiteBalRedLabel.Text = WhiteBalRedTrackBar.Value.ToString();
            }

            // start live mode
            icImagingControl1.LiveStart();
        }
		
		        private void BrightnessAutoCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            VCDProp.Automation[VCDIDs.VCDID_Brightness] = BrightnessAutoCheckBox.Checked;
            BrightnessTrackBar.Enabled = !BrightnessAutoCheckBox.Checked;		
        }
		
		        private void WhitebalanceCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            VCDProp.Automation[VCDIDs.VCDID_WhiteBalance] = WhitebalanceCheckBox.Checked;
            WhiteBalBlueTrackBar.Enabled = !WhitebalanceCheckBox.Checked;
            WhiteBalRedTrackBar.Enabled = !WhitebalanceCheckBox.Checked;
        }
		
		        private void BrightnessTrackBar_Scroll(object sender, EventArgs e)
        {
            VCDProp.RangeValue[VCDIDs.VCDID_Brightness] = BrightnessTrackBar.Value;
            BrightnessValueLabel.Text = VCDProp.RangeValue[VCDIDs.VCDID_Brightness].ToString();
        }
		
        private void WhiteBalRedTrackBar_Scroll(object sender, EventArgs e)
        {
            VCDProp.RangeValue[VCDIDs.VCDElement_WhiteBalanceRed] = WhiteBalRedTrackBar.Value;
            WhiteBalRedLabel.Text = VCDProp.RangeValue[VCDIDs.VCDElement_WhiteBalanceRed].ToString();
        }

        private void WhiteBalBlueTrackBar_Scroll(object sender, EventArgs e)
        {
            VCDProp.RangeValue[VCDIDs.VCDElement_WhiteBalanceBlue] = WhiteBalBlueTrackBar.Value;
            WhiteBalBlueLabel.Text = VCDProp.RangeValue[VCDIDs.VCDElement_WhiteBalanceBlue].ToString();
        }

		        private void WhitebalanceOnePushButton_Click(object sender, EventArgs e)
        {
            VCDProp.OnePush(VCDIDs.VCDID_WhiteBalance);
        }
		        
    }
}