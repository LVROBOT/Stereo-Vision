namespace Controlling_DV_Devices
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
            this.cmdStart = new System.Windows.Forms.Button();
            this.cmdStop = new System.Windows.Forms.Button();
            this.cmdETPlay = new System.Windows.Forms.Button();
            this.cmdETStop = new System.Windows.Forms.Button();
            this.cmdETRewind = new System.Windows.Forms.Button();
            this.cmdETFastForward = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.icImagingControl1)).BeginInit();
            this.SuspendLayout();
            // 
            // icImagingControl1
            // 
            this.icImagingControl1.BackColor = System.Drawing.Color.White;
            this.icImagingControl1.LiveDisplayPosition = new System.Drawing.Point(0, 0);
            this.icImagingControl1.Location = new System.Drawing.Point(10, 9);
            this.icImagingControl1.Name = "icImagingControl1";
            this.icImagingControl1.Size = new System.Drawing.Size(360, 216);
            this.icImagingControl1.TabIndex = 0;
            // 
            // cmdStart
            // 
            this.cmdStart.Location = new System.Drawing.Point(10, 231);
            this.cmdStart.Name = "cmdStart";
            this.cmdStart.Size = new System.Drawing.Size(55, 23);
            this.cmdStart.TabIndex = 1;
            this.cmdStart.Text = "Start";
            this.cmdStart.UseVisualStyleBackColor = true;
            this.cmdStart.Click += new System.EventHandler(this.cmdStart_Click);
            // 
            // cmdStop
            // 
            this.cmdStop.Location = new System.Drawing.Point(71, 231);
            this.cmdStop.Name = "cmdStop";
            this.cmdStop.Size = new System.Drawing.Size(55, 23);
            this.cmdStop.TabIndex = 2;
            this.cmdStop.Text = "Stop";
            this.cmdStop.UseVisualStyleBackColor = true;
            this.cmdStop.Click += new System.EventHandler(this.cmdStop_Click);
            // 
            // cmdETPlay
            // 
            this.cmdETPlay.Location = new System.Drawing.Point(132, 231);
            this.cmdETPlay.Name = "cmdETPlay";
            this.cmdETPlay.Size = new System.Drawing.Size(55, 23);
            this.cmdETPlay.TabIndex = 3;
            this.cmdETPlay.Text = "Play";
            this.cmdETPlay.UseVisualStyleBackColor = true;
            this.cmdETPlay.Click += new System.EventHandler(this.cmdETPlay_Click);
            // 
            // cmdETStop
            // 
            this.cmdETStop.Location = new System.Drawing.Point(193, 231);
            this.cmdETStop.Name = "cmdETStop";
            this.cmdETStop.Size = new System.Drawing.Size(55, 23);
            this.cmdETStop.TabIndex = 4;
            this.cmdETStop.Text = "Stop";
            this.cmdETStop.UseVisualStyleBackColor = true;
            this.cmdETStop.Click += new System.EventHandler(this.cmdETStop_Click);
            // 
            // cmdETRewind
            // 
            this.cmdETRewind.Location = new System.Drawing.Point(254, 231);
            this.cmdETRewind.Name = "cmdETRewind";
            this.cmdETRewind.Size = new System.Drawing.Size(55, 23);
            this.cmdETRewind.TabIndex = 5;
            this.cmdETRewind.Text = "Rewind";
            this.cmdETRewind.UseVisualStyleBackColor = true;
            this.cmdETRewind.Click += new System.EventHandler(this.cmdETRewind_Click);
            // 
            // cmdETFastForward
            // 
            this.cmdETFastForward.Location = new System.Drawing.Point(315, 231);
            this.cmdETFastForward.Name = "cmdETFastForward";
            this.cmdETFastForward.Size = new System.Drawing.Size(55, 23);
            this.cmdETFastForward.TabIndex = 6;
            this.cmdETFastForward.Text = "FF";
            this.cmdETFastForward.UseVisualStyleBackColor = true;
            this.cmdETFastForward.Click += new System.EventHandler(this.cmdETFastForward_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(377, 261);
            this.Controls.Add(this.cmdETFastForward);
            this.Controls.Add(this.cmdETRewind);
            this.Controls.Add(this.cmdETStop);
            this.Controls.Add(this.cmdETPlay);
            this.Controls.Add(this.cmdStop);
            this.Controls.Add(this.cmdStart);
            this.Controls.Add(this.icImagingControl1);
            this.Name = "Form1";
            this.Text = "External Transport";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.icImagingControl1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private TIS.Imaging.ICImagingControl icImagingControl1;
        private System.Windows.Forms.Button cmdStart;
        private System.Windows.Forms.Button cmdStop;
        private System.Windows.Forms.Button cmdETPlay;
        private System.Windows.Forms.Button cmdETStop;
        private System.Windows.Forms.Button cmdETRewind;
        private System.Windows.Forms.Button cmdETFastForward;
    }
}

