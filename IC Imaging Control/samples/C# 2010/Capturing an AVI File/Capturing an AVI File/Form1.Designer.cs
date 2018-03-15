namespace Capturing_an_AVI_File
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
            this.cmdCaptureAVI = new System.Windows.Forms.Button();
            this.cmdStartLive = new System.Windows.Forms.Button();
            this.cmdStopLive = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.icImagingControl1)).BeginInit();
            this.SuspendLayout();
            // 
            // icImagingControl1
            // 
            this.icImagingControl1.BackColor = System.Drawing.Color.White;
            this.icImagingControl1.LiveDisplayPosition = new System.Drawing.Point(0, 0);
            this.icImagingControl1.Location = new System.Drawing.Point(11, 10);
            this.icImagingControl1.Name = "icImagingControl1";
            this.icImagingControl1.Size = new System.Drawing.Size(324, 168);
            this.icImagingControl1.TabIndex = 0;
            // 
            // cmdCaptureAVI
            // 
            this.cmdCaptureAVI.Location = new System.Drawing.Point(243, 185);
            this.cmdCaptureAVI.Name = "cmdCaptureAVI";
            this.cmdCaptureAVI.Size = new System.Drawing.Size(92, 23);
            this.cmdCaptureAVI.TabIndex = 2;
            this.cmdCaptureAVI.Text = "Capture AVI";
            this.cmdCaptureAVI.UseVisualStyleBackColor = true;
            this.cmdCaptureAVI.Click += new System.EventHandler(this.cmdCaptureAVI_Click);
            // 
            // cmdStartLive
            // 
            this.cmdStartLive.Location = new System.Drawing.Point(12, 185);
            this.cmdStartLive.Name = "cmdStartLive";
            this.cmdStartLive.Size = new System.Drawing.Size(92, 23);
            this.cmdStartLive.TabIndex = 3;
            this.cmdStartLive.Text = "Start Live";
            this.cmdStartLive.UseVisualStyleBackColor = true;
            this.cmdStartLive.Click += new System.EventHandler(this.cmdStartLive_Click);
            // 
            // cmdStopLive
            // 
            this.cmdStopLive.Location = new System.Drawing.Point(127, 185);
            this.cmdStopLive.Name = "cmdStopLive";
            this.cmdStopLive.Size = new System.Drawing.Size(92, 23);
            this.cmdStopLive.TabIndex = 4;
            this.cmdStopLive.Text = "Stop Live";
            this.cmdStopLive.UseVisualStyleBackColor = true;
            this.cmdStopLive.Click += new System.EventHandler(this.cmdStopLive_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(344, 213);
            this.Controls.Add(this.cmdStopLive);
            this.Controls.Add(this.cmdStartLive);
            this.Controls.Add(this.cmdCaptureAVI);
            this.Controls.Add(this.icImagingControl1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.icImagingControl1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private TIS.Imaging.ICImagingControl icImagingControl1;
        private System.Windows.Forms.Button cmdCaptureAVI;
        private System.Windows.Forms.Button cmdStartLive;
        private System.Windows.Forms.Button cmdStopLive;
    }
}

