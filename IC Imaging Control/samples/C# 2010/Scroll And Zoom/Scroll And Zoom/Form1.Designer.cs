namespace Scroll_And_Zoom
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.icImagingControl1 = new TIS.Imaging.ICImagingControl();
			this.sldZoom = new System.Windows.Forms.TrackBar();
			this.cmdStart = new System.Windows.Forms.Button();
			this.cmdDevice = new System.Windows.Forms.Button();
			this.cmdStop = new System.Windows.Forms.Button();
			this.cmdImageSettings = new System.Windows.Forms.Button();
			this.chkDisplayDefault = new System.Windows.Forms.CheckBox();
			this.chkScrollbarsEnable = new System.Windows.Forms.CheckBox();
			this.lblZoomPercent = new System.Windows.Forms.Label();
			this.lblZoom = new System.Windows.Forms.Label();
			this.lblScrollPosition = new System.Windows.Forms.Label();
			( (System.ComponentModel.ISupportInitialize)( this.icImagingControl1 ) ).BeginInit();
			( (System.ComponentModel.ISupportInitialize)( this.sldZoom ) ).BeginInit();
			this.SuspendLayout();
			// 
			// icImagingControl1
			// 
			this.icImagingControl1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
						| System.Windows.Forms.AnchorStyles.Left )
						| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.icImagingControl1.BackColor = System.Drawing.Color.White;
			this.icImagingControl1.ImageAvailableExecutionMode = TIS.Imaging.EventExecutionMode.MultiThreaded;
			this.icImagingControl1.LiveDisplayPosition = new System.Drawing.Point( 0, 0 );
			this.icImagingControl1.Location = new System.Drawing.Point( 8, 7 );
			this.icImagingControl1.Name = "icImagingControl1";
			this.icImagingControl1.Size = new System.Drawing.Size( 320, 232 );
			this.icImagingControl1.TabIndex = 0;
			this.icImagingControl1.Scroll += new System.Windows.Forms.ScrollEventHandler( this.icImagingControl1_Scroll );
			// 
			// sldZoom
			// 
			this.sldZoom.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
						| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.sldZoom.Location = new System.Drawing.Point( 334, 28 );
			this.sldZoom.Maximum = 30;
			this.sldZoom.Name = "sldZoom";
			this.sldZoom.Orientation = System.Windows.Forms.Orientation.Vertical;
			this.sldZoom.Size = new System.Drawing.Size( 45, 211 );
			this.sldZoom.TabIndex = 1;
			this.sldZoom.Scroll += new System.EventHandler( this.sldZoom_Scroll );
			// 
			// cmdStart
			// 
			this.cmdStart.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.cmdStart.Location = new System.Drawing.Point( 8, 245 );
			this.cmdStart.Name = "cmdStart";
			this.cmdStart.Size = new System.Drawing.Size( 75, 23 );
			this.cmdStart.TabIndex = 2;
			this.cmdStart.Text = "Start";
			this.cmdStart.UseVisualStyleBackColor = true;
			this.cmdStart.Click += new System.EventHandler( this.cmdStart_Click );
			// 
			// cmdDevice
			// 
			this.cmdDevice.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.cmdDevice.Location = new System.Drawing.Point( 8, 274 );
			this.cmdDevice.Name = "cmdDevice";
			this.cmdDevice.Size = new System.Drawing.Size( 75, 23 );
			this.cmdDevice.TabIndex = 3;
			this.cmdDevice.Text = "Device";
			this.cmdDevice.UseVisualStyleBackColor = true;
			this.cmdDevice.Click += new System.EventHandler( this.cmdDevice_Click );
			// 
			// cmdStop
			// 
			this.cmdStop.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.cmdStop.Location = new System.Drawing.Point( 89, 245 );
			this.cmdStop.Name = "cmdStop";
			this.cmdStop.Size = new System.Drawing.Size( 75, 23 );
			this.cmdStop.TabIndex = 4;
			this.cmdStop.Text = "Stop";
			this.cmdStop.UseVisualStyleBackColor = true;
			this.cmdStop.Click += new System.EventHandler( this.cmdStop_Click );
			// 
			// cmdImageSettings
			// 
			this.cmdImageSettings.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.cmdImageSettings.Location = new System.Drawing.Point( 89, 274 );
			this.cmdImageSettings.Name = "cmdImageSettings";
			this.cmdImageSettings.Size = new System.Drawing.Size( 75, 23 );
			this.cmdImageSettings.TabIndex = 5;
			this.cmdImageSettings.Text = "Settings";
			this.cmdImageSettings.UseVisualStyleBackColor = true;
			this.cmdImageSettings.Click += new System.EventHandler( this.cmdImageSettings_Click );
			// 
			// chkDisplayDefault
			// 
			this.chkDisplayDefault.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.chkDisplayDefault.AutoSize = true;
			this.chkDisplayDefault.Location = new System.Drawing.Point( 202, 245 );
			this.chkDisplayDefault.Name = "chkDisplayDefault";
			this.chkDisplayDefault.Size = new System.Drawing.Size( 125, 17 );
			this.chkDisplayDefault.TabIndex = 6;
			this.chkDisplayDefault.Text = "Default Window Size";
			this.chkDisplayDefault.UseVisualStyleBackColor = true;
			this.chkDisplayDefault.CheckedChanged += new System.EventHandler( this.chkDisplayDefault_CheckedChanged );
			// 
			// chkScrollbarsEnable
			// 
			this.chkScrollbarsEnable.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.chkScrollbarsEnable.AutoSize = true;
			this.chkScrollbarsEnable.Location = new System.Drawing.Point( 202, 268 );
			this.chkScrollbarsEnable.Name = "chkScrollbarsEnable";
			this.chkScrollbarsEnable.Size = new System.Drawing.Size( 72, 17 );
			this.chkScrollbarsEnable.TabIndex = 7;
			this.chkScrollbarsEnable.Text = "Scrollbars";
			this.chkScrollbarsEnable.UseVisualStyleBackColor = true;
			this.chkScrollbarsEnable.CheckedChanged += new System.EventHandler( this.chkScrollbarsEnable_CheckedChanged );
			// 
			// lblZoomPercent
			// 
			this.lblZoomPercent.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.lblZoomPercent.AutoSize = true;
			this.lblZoomPercent.Location = new System.Drawing.Point( 335, 255 );
			this.lblZoomPercent.Name = "lblZoomPercent";
			this.lblZoomPercent.Size = new System.Drawing.Size( 35, 13 );
			this.lblZoomPercent.TabIndex = 8;
			this.lblZoomPercent.Text = "label1";
			// 
			// lblZoom
			// 
			this.lblZoom.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.lblZoom.AutoSize = true;
			this.lblZoom.Location = new System.Drawing.Point( 335, 12 );
			this.lblZoom.Name = "lblZoom";
			this.lblZoom.Size = new System.Drawing.Size( 34, 13 );
			this.lblZoom.TabIndex = 9;
			this.lblZoom.Text = "Zoom";
			// 
			// lblScrollPosition
			// 
			this.lblScrollPosition.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.lblScrollPosition.AutoSize = true;
			this.lblScrollPosition.Location = new System.Drawing.Point( 220, 288 );
			this.lblScrollPosition.Name = "lblScrollPosition";
			this.lblScrollPosition.Size = new System.Drawing.Size( 24, 13 );
			this.lblScrollPosition.TabIndex = 10;
			this.lblScrollPosition.Text = "0/0";
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 382, 307 );
			this.Controls.Add( this.lblScrollPosition );
			this.Controls.Add( this.lblZoom );
			this.Controls.Add( this.lblZoomPercent );
			this.Controls.Add( this.chkScrollbarsEnable );
			this.Controls.Add( this.chkDisplayDefault );
			this.Controls.Add( this.cmdImageSettings );
			this.Controls.Add( this.cmdStop );
			this.Controls.Add( this.cmdDevice );
			this.Controls.Add( this.cmdStart );
			this.Controls.Add( this.sldZoom );
			this.Controls.Add( this.icImagingControl1 );
			this.Name = "Form1";
			this.Text = "Scroll And Zoom";
			( (System.ComponentModel.ISupportInitialize)( this.icImagingControl1 ) ).EndInit();
			( (System.ComponentModel.ISupportInitialize)( this.sldZoom ) ).EndInit();
			this.ResumeLayout( false );
			this.PerformLayout();

        }

        #endregion

        private TIS.Imaging.ICImagingControl icImagingControl1;
        private System.Windows.Forms.TrackBar sldZoom;
        private System.Windows.Forms.Button cmdStart;
        private System.Windows.Forms.Button cmdDevice;
        private System.Windows.Forms.Button cmdStop;
        private System.Windows.Forms.Button cmdImageSettings;
        private System.Windows.Forms.CheckBox chkDisplayDefault;
        private System.Windows.Forms.CheckBox chkScrollbarsEnable;
        private System.Windows.Forms.Label lblZoomPercent;
        private System.Windows.Forms.Label lblZoom;
		private System.Windows.Forms.Label lblScrollPosition;
    }
}

