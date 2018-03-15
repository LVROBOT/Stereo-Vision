using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace MakingDeviceSettings
{
	public partial class frmDeviceSettings : Form
	{
				public TIS.Imaging.ICImagingControl ImagingControl;
		private string DeviceState;
		private const string NOT_AVAILABLE = "n\\a";
		
		public frmDeviceSettings()
		{
			InitializeComponent();
		}

		// ------------------------------------------------------------------------------
		// Form events
		// ------------------------------------------------------------------------------

		//
		// Form_Load
		//
		// Fill the Video Sources combo box with names of all available
		// video capture devices and select the first one. This will trigger
		// a click event on the Video Sources combo box and open the device.
		//
				private void frmDeviceSettings_Load( object sender, EventArgs e )
		{
			if( ImagingControl.DeviceValid )
			{
				if( ImagingControl.LiveVideoRunning )
				{
					lblErrorMessage.Text = "The device settings dialog is not available while the live video is running.\n\nStop the live video first.";
					lblErrorMessage.AutoSize = false;
					lblErrorMessage.Padding = new Padding( 8 );
					lblErrorMessage.SetBounds( 0, 0, 100, cmdOK.Top );
					lblErrorMessage.Dock = DockStyle.Top;
					lblErrorMessage.Visible = true;
					return;
				}
				else
				{
					lblErrorMessage.Visible = false;
				}
			}

			SaveDeviceSettings();

			UpdateDevices();
		}
		
		private void SaveDeviceSettings()
		{
			DeviceState = ImagingControl.DeviceState;
		}

		private void RestoreDeviceSettings()
		{
			try
			{
				ImagingControl.DeviceState = DeviceState;
			}
			catch (System.Exception)
			{
			}			
		}

		// ------------------------------------------------------------------------------
		// UI Update
		// ------------------------------------------------------------------------------

		//
		// UpdateDevices
		//
		// Fills cboDevice
		//
				private void UpdateDevices()
		{
			cboDevice.Items.Clear();
			if( ImagingControl.Devices.Length > 0 )
			{
				foreach( object Item in ImagingControl.Devices )
				{
					cboDevice.Items.Add( Item.ToString() );
				}

				if( ImagingControl.DeviceValid )
				{
					cboDevice.SelectedItem = ImagingControl.Device;
				}
				else
				{
					cboDevice.SelectedIndex = 0;
				}
				cboDevice.Enabled = true;
			}
			else
			{
				cboDevice.Items.Add( NOT_AVAILABLE );
				cboDevice.Enabled = false;
				cboDevice.SelectedIndex = 0;
			}
		}
		
		//
		// UpdateVideoNorms
		//
		// Fills cboVideoNorm
		//
				private void UpdateVideoNorms()
		{
			cboVideoNorm.Items.Clear();
			if( ImagingControl.VideoNormAvailable )
			{
				foreach( object Item in ImagingControl.VideoNorms )
				{
					cboVideoNorm.Items.Add( Item.ToString() );
				}

				cboVideoNorm.SelectedItem = ImagingControl.VideoNorm.ToString();
				cboVideoNorm.Enabled = true;
			}
			else
			{
				cboVideoNorm.Items.Add( NOT_AVAILABLE );
				cboVideoNorm.Enabled = false;
				cboVideoNorm.SelectedIndex = 0;
			}
		}
		
		//
		// UpdateVideoFormats
		//
		// Fills cboVideoFormat
		//
				private void UpdateVideoFormats()
		{
			cboVideoFormat.Items.Clear();
			if( ImagingControl.DeviceValid )
			{
				foreach( object Item in ImagingControl.VideoFormats )
				{
					cboVideoFormat.Items.Add( Item.ToString() );
				}

				cboVideoFormat.SelectedItem = ImagingControl.VideoFormat.ToString();
				cboVideoFormat.Enabled = true;
			}
			else
			{
				cboVideoFormat.Items.Add( NOT_AVAILABLE );
				cboVideoFormat.Enabled = false;
				cboVideoFormat.SelectedIndex = 0;
			}
		}
		
		//
		// UpdateInputChannels
		//
		// Fills cboInputChannel
		//
				private void UpdateInputChannels()
		{
			cboInputChannel.Items.Clear();
			if( ImagingControl.InputChannelAvailable )
			{
				foreach( object Item in ImagingControl.InputChannels )
				{
					cboInputChannel.Items.Add( Item.ToString() );
				}

				cboInputChannel.SelectedItem = ImagingControl.InputChannel;
				cboInputChannel.Enabled = true;
			}
			else
			{
				cboInputChannel.Items.Add( NOT_AVAILABLE );
				cboInputChannel.Enabled = false;
				cboInputChannel.SelectedIndex = 0;
			}
		}
		
		//
		// UpdateFrameRates
		//
		// Fills cboFrameRates
		//
				private void UpdateFrameRates()
		{
			cboFrameRate.Items.Clear();
			if( ImagingControl.DeviceFrameRateAvailable )
			{
				foreach( object Item in ImagingControl.DeviceFrameRates )
				{
					cboFrameRate.Items.Add( Item.ToString() );
				}

				cboFrameRate.SelectedItem = ( ImagingControl.DeviceFrameRate ).ToString();
				cboFrameRate.Enabled = true;
			}
			else
			{
				cboFrameRate.Items.Add( NOT_AVAILABLE );
				cboFrameRate.Enabled = false;
				cboFrameRate.SelectedIndex = 0;
			}
		}
		
		//
		// UpdateFlip
		//
		// updates the flip checkboxes
		//
				private void UpdateFlip()
		{
			if( ImagingControl.DeviceFlipHorizontalAvailable )
			{
				chkFlipH.Enabled = true;
				if( ImagingControl.DeviceFlipHorizontal )
				{
					chkFlipH.Checked = true;
				}
				else
				{
					chkFlipH.Checked = false;
				}
			}
			else
			{
				chkFlipH.Enabled = false;
				chkFlipH.Checked = false;
			}

			if( ImagingControl.DeviceFlipVerticalAvailable )
			{
				chkFlipV.Enabled = true;
				if( ImagingControl.DeviceFlipVertical )
				{
					chkFlipV.Checked = true;
				}
				else
				{
					chkFlipV.Checked = false;
				}
			}
			else
			{
				chkFlipV.Enabled = false;
				chkFlipV.Checked = false;
			}
		}
		//>


		// ------------------------------------------------------------------------------
		// UI events
		// ------------------------------------------------------------------------------

		//
		// cboDevice_SelectedIndexChanged
		//
		// Get available inputs and video formats for the selected
		// device and enter the information in the respective combo
		// boxes.
		//
				private void cboDevice_SelectedIndexChanged( object sender, System.EventArgs e )
		{
			string Serial = "";

			try
			{
				// Open the device
				if( cboDevice.Enabled )
				{
					int index = 0;
					ImagingControl.Device = cboDevice.Text;

					txtSerial.Text = NOT_AVAILABLE;

					foreach( object Item in ImagingControl.Devices )
					{
						if( Item.ToString() == cboDevice.Text )
						{
							if( ImagingControl.Devices[index].GetSerialNumber( out Serial ) )
							{
								txtSerial.Text = Serial;
								break;
							}
						}
						index++;
					}
				}
				// Get supported video norms, formats and inputs
				UpdateVideoNorms();
				UpdateInputChannels();
				UpdateFlip();
			}
			catch( Exception ex )
			{
				MessageBox.Show( ex.Message );
			}
		}
		
		//
		// cboVideoNorm_SelectedIndexChanged
		//
		// Select a video norm.
		//
				private void cboVideoNorm_SelectedIndexChanged( object sender, System.EventArgs e )
		{
			try
			{
				if( cboVideoNorm.Enabled )
				{
					ImagingControl.VideoNorm = cboVideoNorm.Text;
				}

				UpdateVideoFormats();
			}
			catch( Exception ex )
			{
				MessageBox.Show( ex.Message );
			}
		}
		
		//
		// cboInputChannel_SelectedIndexChanged
		//
		// Select an input channel.
		//
				private void cboInputChannel_SelectedIndexChanged( object sender, System.EventArgs e )
		{
			try
			{
				if( cboInputChannel.Enabled )
				{
					ImagingControl.InputChannel = cboInputChannel.Text;
				}
			}
			catch( Exception ex )
			{
				MessageBox.Show( ex.Message );
			}
		}
		
		//
		// cboVideoFormat_SelectedIndexChanged
		//
		// Select a video format.
		//	
				private void cboVideoFormat_SelectedIndexChanged( object sender, System.EventArgs e )
		{
			try
			{
				if( cboVideoFormat.Enabled )
				{
					ImagingControl.VideoFormat = cboVideoFormat.Text;
				}

				UpdateFrameRates();
			}
			catch( Exception ex )
			{
				MessageBox.Show( ex.Message );
			}
		}
		
		//
		// cboFrameRate_SelectedIndexChanged
		//
		// Select a frame rate
		//
				private void cboFrameRate_SelectedIndexChanged( object sender, System.EventArgs e )
		{
			try
			{
				if( cboFrameRate.Enabled )
				{
					ImagingControl.DeviceFrameRate = (float)( System.Convert.ToDouble( cboFrameRate.Text ) );
				}
			}
			catch( Exception ex )
			{
				MessageBox.Show( ex.Message );
			}
		}
		
		//
		// chkFlipV
		//
		// Switch flip vertical on/off
		//
				private void chkFlipV_CheckedChanged( object sender, System.EventArgs e )
		{
			if( ImagingControl.DeviceFlipVerticalAvailable )
			{
				ImagingControl.DeviceFlipVertical = ( chkFlipV.Checked == true );
			}
		}
		
		//
		// chkFlipH
		//
		// Switch flip horizontal on/off
		//
		private void chkFlipH_CheckedChanged( object sender, System.EventArgs e )
		{
			if( ImagingControl.DeviceFlipHorizontalAvailable )
			{
				ImagingControl.DeviceFlipHorizontal = ( chkFlipH.Checked == true );
			}
		}


		// ------------------------------------------------------------------------------
		// Buttons
		// ------------------------------------------------------------------------------

		//
		// cmdOK_Click
		//
		// Close form.
		//
				private void cmdOK_Click( object sender, System.EventArgs e )
		{
			this.Close();
		}
		
		//
		// cmdCancel_Click
		//
		// Close form and set canceled to true.
		//
				private void cmdCancel_Click( object sender, System.EventArgs e )
		{
			RestoreDeviceSettings();

			this.Close();
		}
			}
}