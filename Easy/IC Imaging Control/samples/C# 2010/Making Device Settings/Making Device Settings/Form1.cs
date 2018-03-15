using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MakingDeviceSettings
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		//
		// Form_Load
		//
		// Start the live display, if a video capture device has been selected.
		//
				private void Form1_Load( object sender, System.EventArgs e )
		{
			cmdStopLive.Enabled = false;

			if( icImagingControl1.DeviceValid )
			{
				cmdStartLive.Enabled = true;
			}
			else
			{
				cmdStartLive.Enabled = false;
			}
		}
		
		//
		// cmdDevice_Click
		//
		// Open a Device Settings dialog box.
		//
				private void cmdDevice_Click( object sender, System.EventArgs e )
		{
						using( frmDeviceSettings DeviceDialog = new frmDeviceSettings() )
			{
				DeviceDialog.ImagingControl = icImagingControl1;
				DeviceDialog.ShowDialog();
			}
			
			if( !icImagingControl1.LiveVideoRunning )
			{
				if( icImagingControl1.DeviceValid )
				{
					cmdStartLive.Enabled = true;
				}
				else
				{
					cmdStartLive.Enabled = false;
				}
			}
		}
		
		private void cmdStartLive_Click( object sender, System.EventArgs e )
		{
			try
			{
				icImagingControl1.LiveStart();
				cmdStartLive.Enabled = false;
				cmdStopLive.Enabled = true;
			}
			catch( Exception ex )
			{
				MessageBox.Show( ex.Message );
			}
		}

		private void cmdStopLive_Click( object sender, System.EventArgs e )
		{
			try
			{
				icImagingControl1.LiveStop();
				cmdStartLive.Enabled = true;
				cmdStopLive.Enabled = false;
			}
			catch( Exception ex )
			{
				MessageBox.Show( ex.Message );
			}
		}
	}
}