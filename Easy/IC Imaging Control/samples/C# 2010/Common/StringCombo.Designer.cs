
    partial class StringCombo
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Combo = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // Combo
            // 
            this.Combo.FormattingEnabled = true;
            this.Combo.Location = new System.Drawing.Point(3, 4);
            this.Combo.Name = "Combo";
            this.Combo.Size = new System.Drawing.Size(245, 21);
            this.Combo.TabIndex = 0;
            this.Combo.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // StringCombo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.Combo);
            this.Name = "StringCombo";
            this.Size = new System.Drawing.Size(251, 26);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox Combo;
    }

