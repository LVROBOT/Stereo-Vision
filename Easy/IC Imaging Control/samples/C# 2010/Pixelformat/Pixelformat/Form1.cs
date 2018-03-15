using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Pixelformat
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private TIS.Imaging.VideoFormat CurrentVideoFormat
        {
            get
            {
                foreach (TIS.Imaging.VideoFormat fmt in icImagingControl1.VideoFormats)
                {
                    if (fmt.Name == icImagingControl1.VideoFormat)
                    {
                        return fmt;
                    }
                }

                throw new Exception("Invalid video format selected");
            }
        }

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

            cmdYGB0.Enabled = icImagingControl1.VideoFormat.StartsWith("YGB0");
            cmdYGB1.Enabled = icImagingControl1.VideoFormat.StartsWith("YGB1");
			cmdY16.Enabled = icImagingControl1.VideoFormat.StartsWith("Y16");

            icImagingControl1.OverlayBitmapPosition = TIS.Imaging.PathPositions.None;
            icImagingControl1.LiveCaptureLastImage = false;
            icImagingControl1.LiveStart();
        }

        private TIS.Imaging.ImageBuffer GrabImage(Guid colorFormat)
        {
            bool wasLive = icImagingControl1.LiveVideoRunning;
            icImagingControl1.LiveStop();

            TIS.Imaging.BaseSink oldSink = icImagingControl1.Sink;

            TIS.Imaging.FrameHandlerSink fhs = new TIS.Imaging.FrameHandlerSink();
            fhs.FrameTypes.Add(new TIS.Imaging.FrameType(colorFormat));

            icImagingControl1.Sink = fhs;

            try
            {
                icImagingControl1.LiveStart();
            }
            catch (TIS.Imaging.ICException ex)
            {
                MessageBox.Show(ex.Message);
                return null;
            }

            TIS.Imaging.ImageBuffer rval = null;

            try
            {
                fhs.SnapImage(1000);
                rval = fhs.LastAcquiredBuffer;
            }
            catch (TIS.Imaging.ICException ex)
            {
                MessageBox.Show(ex.Message);
            }

            icImagingControl1.LiveStop();

            icImagingControl1.Sink = oldSink;

            if (wasLive) icImagingControl1.LiveStart();

            return rval;
        }


        private void cmdY800_Click(object sender, EventArgs e)
        {

            TIS.Imaging.ImageBuffer buf = GrabImage(TIS.Imaging.MediaSubtypes.Y800);
            if (buf == null) return;

            // Y800 is top-down, the first line has index 0
            int y = 0;

            txtOutput.Text = "Image buffer pixel format is Y800\r\n";
            txtOutput.Text += "Pixel 1: " + buf[0, y] + "\r\n";
            txtOutput.Text += "Pixel 2: " + buf[1, y];

            // Set the first pixel to 0 (black)
            buf[0, y] = 0;
            // Set the second pixel to 128 (gray)
            buf[1, y] = 128;
            // Set the third pixel to 255 (white)
            buf[2, y] = 255;

            buf.SaveAsBitmap("Y800.bmp");
        }

        private void cmdRGB8_Click(object sender, EventArgs e)
        {
            TIS.Imaging.ImageBuffer buf = GrabImage(TIS.Imaging.MediaSubtypes.RGB8);
            if (buf == null) return;

            // RGB8 is bottom-up, the first line has index lines-1
            int y = buf.Lines - 1;

            txtOutput.Text = "Image buffer pixel format is RGB8\r\n";
            txtOutput.Text += "Pixel 1: " + buf[0, y] + "\r\n";
            txtOutput.Text += "Pixel 2: " + buf[1, y];


            // Set the first pixel to 0 (black)
            buf[0, y] = 0;
            // Set the second pixel to 128 (gray)
            buf[1, y] = 128;
            // Set the third pixel to 255 (white)
            buf[2, y] = 255;

            buf.SaveAsBitmap("RGB8.bmp");
        }

        private void cmdRGB24_Click(object sender, EventArgs e)
        {
            TIS.Imaging.ImageBuffer buf = GrabImage(TIS.Imaging.MediaSubtypes.RGB24);
            if (buf == null) return;
            // RGB24 is bottom-up, the first line has index lines-1
            int y = buf.Lines - 1;

            txtOutput.Text = "Image buffer pixel format is RGB24\r\n";
            txtOutput.Text += "Pixel 1: ";
            txtOutput.Text += "R=" + buf[0 * 3 + 2, y] + ", ";
            txtOutput.Text += "G=" + buf[0 * 3 + 1, y] + ", ";
            txtOutput.Text += "B=" + buf[0 * 3 + 0, y] + "\r\n";
            txtOutput.Text += "Pixel 2: ";
            txtOutput.Text += "R=" + buf[1 * 3 + 2, y] + ", ";
            txtOutput.Text += "G=" + buf[1 * 3 + 1, y] + ", ";
            txtOutput.Text += "B=" + buf[1 * 3 + 0, y];


            // Set the first pixel to red (255 0 0)
            buf[0 * 3 + 2, y] = 255;
            buf[0 * 3 + 1, y] = 0;
            buf[0 * 3 + 0, y] = 0;
            // Set the second pixel to 128 (gray)
            buf[1 * 3 + 2, y] = 0;
            buf[1 * 3 + 1, y] = 255;
            buf[1 * 3 + 0, y] = 0;
            // Set the third pixel to 255 (white)
            buf[2 * 3 + 2, y] = 0;
            buf[2 * 3 + 1, y] = 0;
            buf[2 * 3 + 0, y] = 255;

            buf.SaveAsBitmap("RGB24.bmp");
        }

        private void cmdRGB32_Click(object sender, EventArgs e)
        {
            TIS.Imaging.ImageBuffer buf = GrabImage(TIS.Imaging.MediaSubtypes.RGB32);
            if (buf == null) return;

            // RGB32is bottom-up, the first line has index lines-1
            int y = buf.Lines - 1;

            txtOutput.Text = "Image buffer pixel format is RGB32\r\n";
            txtOutput.Text += "Pixel 1: ";
            txtOutput.Text += "R=" + buf[0 * 4 + 2, y] + ", ";
            txtOutput.Text += "G=" + buf[0 * 4 + 1, y] + ", ";
            txtOutput.Text += "B=" + buf[0 * 4 + 0, y] + "\r\n";
            txtOutput.Text += "Pixel 2: ";
            txtOutput.Text += "R=" + buf[1 * 4 + 2, y] + ", ";
            txtOutput.Text += "G=" + buf[1 * 4 + 1, y] + ", ";
            txtOutput.Text += "B=" + buf[1 * 4 + 0, y];

            // Set the first pixel to red (255 0 0)
            buf[0 * 4 + 2, y] = 255;
            buf[0 * 4 + 1, y] = 0;
            buf[0 * 4 + 0, y] = 0;
            // Set the second pixel to 128 (gray)
            buf[1 * 4 + 2, y] = 0;
            buf[1 * 4 + 1, y] = 255;
            buf[1 * 4 + 0, y] = 0;
            // Set the third pixel to 255 (white)
            buf[2 * 4 + 2, y] = 0;
            buf[2 * 4 + 1, y] = 0;
            buf[2 * 4 + 0, y] = 255;

            buf.SaveAsBitmap("RGB32.bmp");
        }

        private UInt16 UInt16ValueFromYGB1Bytes(byte b1, byte b2)
        {
            return (UInt16)((b1 << 8) | b2);
        }

        private void YGB1BytesFromUInt16Value(UInt16 val, out byte b1, out byte b2)
        {
            b1 = (byte)(val >> 8);
            b2 = (byte)(val & 0xff);
        }

        private void cmdYGB1_Click(object sender, EventArgs e)
        {
            TIS.Imaging.ImageBuffer buf = GrabImage(TIS.Imaging.MediaSubtypes.YGB1);
            if (buf == null) return;

            // YGB1 is top-down, the first line has index 0
            int y = 0;

            UInt16 val0 = UInt16ValueFromYGB1Bytes(buf[0, y], buf[1, y]);
            UInt16 val1 = UInt16ValueFromYGB1Bytes(buf[2, y], buf[3, y]);

            txtOutput.Text = "Image buffer pixel format is YGB1\r\n";
            txtOutput.Text += "Pixel 1: " + val0 + "\r\n";
            txtOutput.Text += "Pixel 2: " + val1;

            byte b1, b2;
            YGB1BytesFromUInt16Value(0, out b1, out b2);
            buf[0, y] = b1;
            buf[1, y] = b2;
            YGB1BytesFromUInt16Value(512, out b1, out b2);
            buf[2, y] = b1;
            buf[3, y] = b2;
            YGB1BytesFromUInt16Value(1023, out b1, out b2);
            buf[4, y] = b1;
            buf[5, y] = b2;

            buf.SaveAsBitmap("ygb1.bmp", TIS.Imaging.ICImagingControlColorformats.ICY800);
        }

        private UInt16 UInt16ValueFromYGB0Bytes(byte b1, byte b2)
        {
            return (UInt16)(((b1 << 8) | b2) >> 6);
        }

        private void YGB0BytesFromUInt16Value(UInt16 val, out byte b1, out byte b2)
        {
            val <<= 6;
            b1 = (byte)(val >> 8);
            b2 = (byte)(val & 0xff);
        }
        private void cmdYGB0_Click(object sender, EventArgs e)
        {
            TIS.Imaging.ImageBuffer buf = GrabImage(TIS.Imaging.MediaSubtypes.YGB0);
            if (buf == null) return;

            // YGB0 is top-down, the first line has index 0
            int y = 0;

            UInt16 val0 = UInt16ValueFromYGB0Bytes(buf[0 * 2 + 0, y], buf[0 * 2 + 1, y]);
            UInt16 val1 = UInt16ValueFromYGB0Bytes(buf[1 * 2 + 0, y], buf[1 * 2 + 1, y]);

            txtOutput.Text = "Image buffer pixel format is YGB0\r\n";
            txtOutput.Text += "Pixel 1: " + val0 + "\r\n";
            txtOutput.Text += "Pixel 2: " + val1;

            byte b1, b2;
            YGB0BytesFromUInt16Value(0, out b1, out b2);
            buf[0 * 2 + 0, y] = b1;
            buf[0 * 2 + 1, y] = b2;
            YGB0BytesFromUInt16Value(512, out b1, out b2);
            buf[1 * 2 + 0, y] = b1;
            buf[1 * 2 + 1, y] = b2;
            YGB0BytesFromUInt16Value(1023, out b1, out b2);
            buf[2 * 2 + 0, y] = b1;
            buf[2 * 2 + 1, y] = b2;

            buf.SaveAsBitmap("ygb0.bmp", TIS.Imaging.ICImagingControlColorformats.ICY800);
        }


		private UInt16 ReadY16(TIS.Imaging.ImageBuffer buf, int row, int col)
		{
			// Y16 is top-down, the first line has index 0
			int offset = row * buf.BytesPerLine + col * 2;

			return (UInt16)System.Runtime.InteropServices.Marshal.ReadInt16(buf.GetIntPtr(), offset);
		}

		private void WriteY16(TIS.Imaging.ImageBuffer buf, int row, int col, UInt16 value)
		{
			int offset = row * buf.BytesPerLine + col * 2;

			System.Runtime.InteropServices.Marshal.WriteInt16(buf.GetIntPtr(), offset, (short)value);
		}

		private void cmdY16_Click(object sender, EventArgs e)
		{
			TIS.Imaging.ImageBuffer buf = GrabImage(TIS.Imaging.MediaSubtypes.Y16);
			if (buf == null) return;

			UInt32 val0 = ReadY16(buf, 0, 0);
			UInt32 val1 = ReadY16(buf, 0, 1);

			txtOutput.Text = "Image buffer pixel format is Y16\r\n";
			txtOutput.Text += "Pixel 1: " + val0 + "\r\n";
			txtOutput.Text += "Pixel 2: " + val1;

			WriteY16(buf, 0, 0, 0x0000); // Black
			WriteY16(buf, 0, 1, 0x8000); // Gray
			WriteY16(buf, 0, 2, 0xFFFF); // White

			buf.SaveAsTiff("y16.tiff");
		}
    }
}