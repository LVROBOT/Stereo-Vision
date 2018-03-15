using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Image_Processing
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        bool VideoHasStarted;
        bool VideoHasStopped;

        /// <summary>
        /// Form_load
        ///
        /// Shows the device settings dialog and checks for a  valid video
        /// capture device to prevent error messages.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            // No video stream has been started now. Processing an image 
			// will fail in this case.
			VideoHasStarted = false;
			VideoHasStopped = false;

			// Check whether a valid video capture device has been selected,
			// otherwise show the device settings dialog
			if( !icImagingControl1.DeviceValid )
			{
				icImagingControl1.ShowDeviceSettingsDialog();

				if( !icImagingControl1.DeviceValid )
				{
					MessageBox.Show( "No device was selected." );
					this.Close();
					return;
				}
			}
			
			cmdStartLive.Enabled = true;
			cmdStopLive.Enabled = true;
			cmdProcess.Enabled = true;

			// This sample works works for color images, so set the sink type
			// to RGB24
			icImagingControl1.MemoryCurrentGrabberColorformat = TIS.Imaging.ICImagingControlColorformats.ICRGB24;
        }

        /// <summary>
        /// cmdProcess_Click
        ///
        /// Snaps a single image, inverts the image data and shows the buffer.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdProcess_Click(object sender, EventArgs e)
        {
            TIS.Imaging.ImageBuffer ImgBuffer;
            int x, y;
            int BytesPerLine;

            Cursor = Cursors.WaitCursor;
            try
            {
                // Check whether the video stream has been started once.
                // If it has been started once, there are two possible situations:
                // 1) The live video is running. In this case we stop the live video
                //       in order to get the last frame and display the processed image.
                // 2) The live video has been stopped. In this case the last frame of the
                //       live video was grabbed automatically and can be processed and
                //       displayed.
                if (VideoHasStarted)
                {
                    if (VideoHasStopped == false)
                    {
                        icImagingControl1.LiveStop();
                    }

                    ImgBuffer = icImagingControl1.ImageActiveBuffer;
                    // Calculate the count of bytes per line. 
                    BytesPerLine = ImgBuffer.BitsPerPixel / 8 * ImgBuffer.PixelPerLine;
                    unsafe
                    {
                        byte* pDatabyte = ImgBuffer.GetImageData();
                        for (y = 0; y < ImgBuffer.Lines; y++)
                        {
                            for (x = 0; x < BytesPerLine; x++)
                            {
                                *pDatabyte = (byte)(255 - *pDatabyte);
                                pDatabyte++;
                            }
                        }
                    }

                    icImagingControl1.DisplayImageBuffer(ImgBuffer);
                }
                else
                {
                    MessageBox.Show("Please click the Start Live button first!",
                        "Image Processing",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.None);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            Cursor = Cursors.Default;
        }
		
		        private void cmdStopLive_Click(object sender, EventArgs e)
        {
            icImagingControl1.LiveStop();

            if (VideoHasStarted == true)
            {
                VideoHasStopped = true;
            }
        }
		
		        private void cmdStartLive_Click_1(object sender, EventArgs e)
        {
            icImagingControl1.LiveStart();

            // Store in VideoHasStarted whether a video stream
            // has been started once. If VideoHasStarted is True,
            // you can be sure that there is an image that can be processed.
            VideoHasStarted = true;

            // VideoHasStopped is set to False, because the live
            // video has just been started.
            VideoHasStopped = false;
        }
		
    }
}