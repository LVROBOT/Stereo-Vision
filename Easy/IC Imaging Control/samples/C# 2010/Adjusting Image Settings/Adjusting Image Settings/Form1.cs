using System;
using System.Windows.Forms;
using TIS.Imaging;
using TIS.Imaging.VCDHelpers;
namespace Adjusting_Image_Settings
{
    public partial class Form1 : Form
    {
				private VCDSimpleProperty VCDProp;
		
        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// All preparations are performed here.
        /// - selecting a device
        /// - starting the live video
        /// - fetching the properties and initializing the controls
        /// </summary>
		        private void Form1_Load(object sender, EventArgs e)
        {
            if (icImagingControl1.ShowDeviceSettingsDialog() == DialogResult.OK)
            {
                icImagingControl1.LiveStart();

                VCDProp = VCDSimpleModule.GetSimplePropertyContainer(icImagingControl1.VCDPropertyItems);

                //  Setup the range of the brightness slider.
                trackBar1.Minimum = VCDProp.RangeMin(VCDIDs.VCDID_Brightness);
                trackBar1.Maximum = VCDProp.RangeMax(VCDIDs.VCDID_Brightness);

                //  Set the slider to the current brightness value.
                trackBar1.Value = VCDProp.RangeValue[VCDIDs.VCDID_Brightness];
            }
            else
            {
                MessageBox.Show("No device was selected.", this.Text,
                                                     MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.Close();
            }
        }
				        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            VCDProp.RangeValue[VCDIDs.VCDID_Brightness] = trackBar1.Value;
        }
		    }
}