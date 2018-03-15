using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Capturing_a_Video_File
{
    public partial class SaveVideoForm : Form
    {
        public SaveVideoForm(TIS.Imaging.ICImagingControl ic )
        {
            InitializeComponent();
            m_ImagingControl = ic;
        }

        private TIS.Imaging.ICImagingControl m_ImagingControl;
        private TIS.Imaging.BaseSink m_OldSink;
        private bool m_OldLiveMode;
        private TIS.Imaging.MediaStreamSink m_Sink;

		        private void SaveVideoForm_Load(object sender, EventArgs e)
        {
            cboMediaStreamContainer.DataSource = m_ImagingControl.MediaStreamContainers;

            cboVideoCodec.DataSource = m_ImagingControl.AviCompressors;

            txtFileName.Text = System.IO.Path.ChangeExtension("video.avi", CurrentMediaStreamContainer.PreferredFileExtension);

            btnStopCapture.Enabled = false;
        }
		
        private void btnProperties_Click(object sender, EventArgs e)
        {
            CurrentVideoCodec.ShowPropertyPage();
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.AddExtension = true;

            string ext = CurrentMediaStreamContainer.PreferredFileExtension;
            dlg.DefaultExt = ext;
            dlg.Filter = CurrentMediaStreamContainer.Name
                        + " Video Files (*." + ext + ")|*." + ext + "||";

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                txtFileName.Text = dlg.FileName;
            }
        }

        private TIS.Imaging.MediaStreamContainer CurrentMediaStreamContainer
        {
            get
            {
                return (TIS.Imaging.MediaStreamContainer)cboMediaStreamContainer.SelectedItem;
            }
        }

        private TIS.Imaging.AviCompressor CurrentVideoCodec
        {
            get
            {
                if (CurrentMediaStreamContainer != null && CurrentMediaStreamContainer.IsCustomCodecSupported)
                {
                    return (TIS.Imaging.AviCompressor)cboVideoCodec.SelectedItem;
                }
                else
                {
                    return null;
                }
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void btnStopCapture_Click(object sender, EventArgs e)
        {
            m_ImagingControl.LiveStop();

            chkPause.Checked = false;
            btnStartCapture.Enabled = true;
            btnStopCapture.Enabled = false;
            btnClose.Enabled = true;

            m_ImagingControl.Sink = m_OldSink;

            if (m_OldLiveMode)
                m_ImagingControl.LiveStart();
        }

		        private void btnStartCapture_Click(object sender, EventArgs e)
        {
            m_Sink = new TIS.Imaging.MediaStreamSink();
            m_Sink.StreamContainer = CurrentMediaStreamContainer;
            m_Sink.Codec = CurrentVideoCodec;
            m_Sink.Filename = txtFileName.Text;
            m_Sink.SinkModeRunning = !chkPause.Checked;

            m_OldLiveMode = m_ImagingControl.LiveVideoRunning;
            m_OldSink = m_ImagingControl.Sink;

            m_ImagingControl.LiveStop();

            m_ImagingControl.Sink = m_Sink;

            m_ImagingControl.LiveStart();

            btnStartCapture.Enabled = false;
            btnStopCapture.Enabled = true;
            btnClose.Enabled = false;
        }
		
		        private void chkPause_CheckedChanged(object sender, EventArgs e)
        {
            if (m_Sink != null)
            {
                m_Sink.SinkModeRunning = !chkPause.Checked;
            }
        }
		
        private void cboMediaStreamContainer_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (CurrentMediaStreamContainer.IsCustomCodecSupported)
            {
                cboVideoCodec.Enabled = true;
                if ( CurrentVideoCodec != null )
                    btnProperties.Enabled = CurrentVideoCodec.PropertyPageAvailable;
            }
            else
            {
                cboVideoCodec.Enabled = false;
                btnProperties.Enabled = false;
            }

            txtFileName.Text = System.IO.Path.ChangeExtension(txtFileName.Text, CurrentMediaStreamContainer.PreferredFileExtension);
        }

        private void cboVideoCodec_SelectedIndexChanged(object sender, EventArgs e)
        {
            btnProperties.Enabled = CurrentVideoCodec.PropertyPageAvailable;
        }


    }
}