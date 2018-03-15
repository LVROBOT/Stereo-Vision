using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Binarization
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private TIS.Imaging.FrameFilter m_FrameFilter;

        private void Form1_Load(object sender, EventArgs e)
        {
            if (!icImagingControl1.DeviceValid)
            {
                icImagingControl1.ShowDeviceSettingsDialog();

                if (!icImagingControl1.DeviceValid)
                {
                    Close();
                    return;
                }
            }

			            // Disable overlay bitmap
            icImagingControl1.OverlayBitmapPosition = TIS.Imaging.PathPositions.None;

            // Create an instance of the frame filter implementation
            BinarizationFilter binFilterImpl = new BinarizationFilter();

            // Create a FrameFilter object wrapping the implementation
            m_FrameFilter = icImagingControl1.FrameFilterCreate(binFilterImpl);

            // Set the FrameFilter as display frame filter.
            icImagingControl1.DisplayFrameFilters.Add(m_FrameFilter);

            // Start live mode
            icImagingControl1.LiveStart();
			
            m_FrameFilter.BeginParameterTransfer();

            chkEnable.Checked = m_FrameFilter.GetBoolParameter("enable");

            sldThreshold.Minimum = 0;
            sldThreshold.Maximum = 255;
            sldThreshold.Value = m_FrameFilter.GetIntParameter("threshold");
            lblThreshold.Text = sldThreshold.Value.ToString();
            sldThreshold.Enabled = chkEnable.Checked;
            lblThreshold.Enabled = chkEnable.Checked;

            m_FrameFilter.EndParameterTransfer();
        }

        /// <summary>
        /// The user clicked the "Enable" check box.
		///
		///	Toggle binarization at the binarization filter,
        ///	and adjust the enabled state of the threshold slider.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void chkEnable_CheckedChanged(object sender, EventArgs e)
        {
            m_FrameFilter.BeginParameterTransfer();

            m_FrameFilter.SetBoolParameter("enable", chkEnable.Checked);
            sldThreshold.Enabled = m_FrameFilter.GetBoolParameter("enable");
            lblThreshold.Enabled = m_FrameFilter.GetBoolParameter("enable");

            m_FrameFilter.EndParameterTransfer();
        }
		
        /// <summary>
        /// The user changed the position of the threshold slider.
		///
		///	Read the new value, and set it at the binarization filter.
        ///	Display the value in the threshold static control.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void sldThreshold_Scroll(object sender, EventArgs e)
        {
            m_FrameFilter.BeginParameterTransfer();

            m_FrameFilter.SetIntParameter("threshold", sldThreshold.Value);
            lblThreshold.Text = m_FrameFilter.GetIntParameter("threshold").ToString();

            m_FrameFilter.EndParameterTransfer();
        }
		
        /// <summary>
        /// The user clicked the "Device..."-button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDevice_Click(object sender, EventArgs e)
        {
            icImagingControl1.LiveStop();
            icImagingControl1.ShowDeviceSettingsDialog();
            icImagingControl1.LiveStart();
        }

        /// <summary>
        /// The user clicked the "Properties..."-button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnProperties_Click(object sender, EventArgs e)
        {
            icImagingControl1.ShowPropertyDialog();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            icImagingControl1.LiveStop();
        }

    }
}