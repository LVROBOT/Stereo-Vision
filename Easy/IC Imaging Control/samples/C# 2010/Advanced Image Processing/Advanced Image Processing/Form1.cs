using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using TIS.Imaging;

namespace Advanced_Image_Processing
{
    public partial class Form1 : Form
    {
		        private struct RECT
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }
						private delegate void ShowBufferDelegate(TIS.Imaging.ImageBuffer buffer);
        private ImageBuffer DisplayBuffer;
        private RECT UserROI;
        private bool UserROICommited = false;
		private int threshold = 0;
		
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                cmdStart.Enabled = false;
                cmdStop.Enabled = false;
                cmdSettings.Enabled = false;
                cmdROICommit.Enabled = false;

                if (icImagingControl1.DeviceValid)
                {
                    cmdStart.Enabled = true;
                    cmdSettings.Enabled = true;

                    // Setup image buffers and the color format
                    MakeDeviceSettings();

                    DisplayBuffer = icImagingControl1.ImageBuffers[1];

                    UserROI.Top = 0;
                    UserROI.Left = 0;
                    UserROI.Bottom = icImagingControl1.ImageHeight;
                    UserROI.Right = icImagingControl1.ImageWidth;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// cmdStart_Click
        ///
        /// Starts the display.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmdStart_Click(object sender, EventArgs e)
        {
			            try
            {
                icImagingControl1.LiveStart();
                cmdStart.Enabled = false;
                cmdStop.Enabled = true;
                cmdROICommit.Enabled = true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
			        }

        /// <summary>
        /// cmdStop_Click
        ///
        /// Stops the display.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmdStop_Click(object sender, EventArgs e)
        {
			            try
            {
                cmdStart.Enabled = true;
                cmdStop.Enabled = false;
                if (UserROICommited)
                {
                    cmdROICommit_Click(sender, e);
                }

                cmdROICommit.Enabled = false;

                DisplayBuffer.ForceUnlock();

                icImagingControl1.LiveStop();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
			        }

        /// <summary>
        /// cmdDevice_Click
        ///
        /// Shows the device settings dialog and initializes some properties.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdDevice_Click(object sender, EventArgs e)
        {
            if (icImagingControl1.LiveVideoRunning)
            {
                icImagingControl1.LiveStop();
            }

            icImagingControl1.ShowDeviceSettingsDialog();

            if (icImagingControl1.DeviceValid)
            {
                cmdStart.Enabled = true;
                cmdSettings.Enabled = true;
                MakeDeviceSettings();
            }
        }
		
        /// <summary>
        /// cmdSettings_Click
        ///
        /// Shows the device settings dialog.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdSettings_Click(object sender, EventArgs e)
        {
            icImagingControl1.ShowPropertyDialog();
        }
		
        /// <summary>
        /// cmdROICommit_Click
        ///
        /// Handles the commit or resets the ROI.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
		        private void cmdROICommit_Click(object sender, EventArgs e)
        {
            if (!UserROICommited)
            {
                UserROICommited = true;
                cmdROICommit.Text = "Reset ROI";
            }
            else
            {
                UserROICommited = false;
                cmdROICommit.Text = "Set current ROI";
            }
        }
		

        /// <summary>
        /// MakeDeviceSettings
        ///
        /// Setup the ring buffer, color format and capture mode.
        /// </summary>
		        private void MakeDeviceSettings()
        {
            // Set the color format to monochrome
            icImagingControl1.MemoryCurrentGrabberColorformat = TIS.Imaging.ICImagingControlColorformats.ICY8;

            // Set the ring buffer size to 5. This ensures that the last 5
            // acquired images are in memory.
            icImagingControl1.ImageRingBufferSize = 5;

            // LiveCaptureContinuous = True means that every frame is
            // copied to the ring buffer.
            icImagingControl1.LiveCaptureContinuous = true;

            // Do not save the last image, if liveStop is called
            icImagingControl1.LiveCaptureLastImage = false;

            // Disable the live display. This allows to display images
            // from the ring buffer in ICImagingControl//s control window.
            icImagingControl1.LiveDisplay = false;

            // Set the size of ICImagingControl to the width and height
            // of the currently selected video format.
            icImagingControl1.Width = icImagingControl1.ImageWidth;
            icImagingControl1.Height = icImagingControl1.ImageHeight;

            UserROI.Top = 0;
            UserROI.Left = 0;
            UserROI.Bottom = icImagingControl1.ImageHeight;
            UserROI.Right = icImagingControl1.ImageWidth;
        }
		
        /// <summary>
        /// icImagingControl1_ImageAvailable
        ///
        /// Event is called for each frame. If an ROI is committed,
        /// it is drawn. In addition, the current buffer is displayed
        /// if a change is the ROI is recognized.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void icImagingControl1_ImageAvailable(object sender, ICImagingControl.ImageAvailableEventArgs e)
        {

            try
            {
				                RECT Region;
                Region = NormalizeRect(UserROI);

                if (!UserROICommited)
                {
                    ContinousMode(e.bufferIndex, Region);
                }
                else
                {
                    CompareMode(e.bufferIndex, Region);
                }
				            }
            catch (Exception ex)
            {
                System.Diagnostics.Trace.WriteLine(ex.Message);
            }
        }


		private void ShowImageBuffer(TIS.Imaging.ImageBuffer buffer)
		{
			icImagingControl1.DisplayImageBuffer(buffer);
		}

        /// <summary>
        /// ContinousMode
        ///
        /// This function is called if the user has not yet commited an ROI.
        /// The Region contains the ROI specified by the current mouse position.
        /// The rectangle specified by Region is drawn in the current buffer.
        /// </summary>
        /// <param name="BufferIndex"></param>
        /// <param name="Region"></param>
		        private void ContinousMode(int BufferIndex, RECT Region)
        {
            //DisplayBuffer.Unlock();
            DisplayBuffer = icImagingControl1.ImageBuffers[BufferIndex];
            //DisplayBuffer.Lock();

            DrawRectangleY8(DisplayBuffer, Region);

			this.BeginInvoke(new ShowBufferDelegate(ShowImageBuffer), DisplayBuffer);
        }
		
		

        /// <summary>
        /// CompareMode
        ///
        /// This function is called when the user commits an ROI.
        /// Compares the current DisplayBuffer with the recently copied buffer.
        /// If they differ, sets the copied buffer as DisplayBuffer.
        /// </summary>
        /// <param name="BufferIndex"></param>
        /// <param name="Region"></param>
		        private void CompareMode(int BufferIndex, RECT Region)
        {
            TIS.Imaging.ImageBuffer IBOld, IBNew;

            IBOld = DisplayBuffer;
            IBNew = icImagingControl1.ImageBuffers[BufferIndex];

            if (CompareRegion(IBOld, IBNew, Region, threshold) )
            {
                //DisplayBuffer.Unlock()
                DisplayBuffer = IBNew;
                //DisplayBuffer.Lock()

                DrawRectangleY8(IBNew, Region);

				this.BeginInvoke(new ShowBufferDelegate(ShowImageBuffer), DisplayBuffer);
            }
        }
		
        // ----------------------------------------------------------------------------
        // Helpers
        // ----------------------------------------------------------------------------

        /// <summary>
        /// NormalizeRect
        ///
        /// Returns a normalized rectangle based on Val.
        /// Normalized means:
        /// (left <= right, top <= bottom, right < MaxX, bottom < MaxY)
        /// </summary>
        /// <param name="val"></param>
        /// <returns></returns>
		        private RECT NormalizeRect(RECT val)
        {
            int Tmp;
            RECT r;

            r = val;

            if (r.Top > r.Bottom)
            {
                Tmp = r.Top;
                r.Top = r.Bottom;
                r.Bottom = Tmp;
            }

            if (r.Left > r.Right)
            {
                Tmp = r.Left;
                r.Left = r.Right;
                r.Right = Tmp;
            }

            if (r.Top < 0)
            {
                r.Top = 0;
            }

            if (r.Left < 0)
            {
                r.Left = 0;
            }

            if (r.Bottom >= icImagingControl1.ImageHeight)
            {
                r.Bottom = icImagingControl1.ImageHeight - 1;
            }

            if (r.Right >= icImagingControl1.ImageWidth)
            {
                r.Right = icImagingControl1.ImageWidth - 1;
            }

            return r;
        }
		
        /// <summary>
        /// CompareRegion
        ///
        /// Compares the contents of Arr with Arr2 in the rectangle
        /// defined by Region. If both arrays differ by more then the
        /// Threshold value,  the function returns true, otherwise false.
        /// </summary>
        /// <param name="Buf"></param>
        /// <param name="Buf2"></param>
        /// <param name="Region"></param>
        /// <param name="Threshold"></param>
        /// <returns></returns>
		        private bool CompareRegion(TIS.Imaging.ImageBuffer Buf, TIS.Imaging.ImageBuffer Buf2, RECT Region, int Threshold)
        {
            int x, y;
            int GreyscaleDifference;
            int PixelCount;

            PixelCount = (Region.Bottom - Region.Top) * (Region.Right - Region.Left);
            if (PixelCount > 0)
            {
                GreyscaleDifference = 0;
                for (y = Region.Top; y <= Region.Bottom; y++)
                {
                    for (x = Region.Left; x <= Region.Right; x++)
                    {
                        GreyscaleDifference = GreyscaleDifference + Math.Abs((int)(Buf[x, y]) - (int)(Buf2[x, y]));
                    }
                }
                GreyscaleDifference = GreyscaleDifference / PixelCount;
                if (GreyscaleDifference > Threshold)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
		
        /// <summary>
        /// IcImagingControl1_MouseDown
        ///
        /// MouseDown event. Resets the user ROI,
        /// if the left mouse button is pressed.
        /// </summary>
        /// <param name="Buf"></param>
        /// <param name="Region"></param>
        private void DrawRectangleY8(TIS.Imaging.ImageBuffer Buf, RECT Region)
        {
            const int RECT_COLOR = 255;
            int x, y;

            for (x = Region.Left; x <= Region.Right; x++)
            {
                Buf[x, Region.Top] = RECT_COLOR;
            }

            for (x = Region.Left; x <= Region.Right; x++)
            {
                Buf[x, Region.Bottom] = RECT_COLOR;
            }

            for (y = Region.Top; y <= Region.Bottom; y++)
            {
                Buf[Region.Left, y] = RECT_COLOR;
            }

            for (y = Region.Top; y <= Region.Bottom; y++)
            {
                Buf[Region.Right, y] = RECT_COLOR;
            }
        }

        /// <summary>
        /// IcImagingControl1_MouseDown
        ///
        /// MouseDown event. Resets the user ROI,
        /// if the left mouse button is pressed.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void icImagingControl1_MouseDown(object sender, MouseEventArgs e)
        {
			            if (!UserROICommited && (e.Button == MouseButtons.Left))
            {
                UserROI.Left = e.Location.X;
                UserROI.Top = icImagingControl1.Height - e.Location.Y;
            }
			        }

        /// <summary>
        /// IcImagingControl1_MouseMove
        ///
        /// MouseMove event. Sets the user ROI to the current mouse cursor
        /// position, if the left mouse button is pressed.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void icImagingControl1_MouseMove(object sender, MouseEventArgs e)
        {
			            if (!UserROICommited && (e.Button == MouseButtons.Left))
            {
                UserROI.Right = e.Location.X;
                UserROI.Bottom = icImagingControl1.Height - e.Location.Y;
            }
			        }

        /// <summary>
        /// IcImagingControl1_MouseUp
        ///
        /// MouseUp event. Sets the user ROI, if the left
        /// mouse button is released.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void icImagingControl1_MouseUp(object sender, MouseEventArgs e)
        {
			            if (!UserROICommited && !(e.Button == MouseButtons.Left))
            {
                UserROI.Right = e.Location.X;
                UserROI.Bottom = icImagingControl1.Height - e.Location.Y;
            }
			        }

		private void sldThresholdSlider_Scroll(object sender, EventArgs e)
		{
			threshold = sldThresholdSlider.Value;
		}


    }
}