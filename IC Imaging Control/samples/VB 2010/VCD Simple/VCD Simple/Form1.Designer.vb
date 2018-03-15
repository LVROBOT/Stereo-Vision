<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing AndAlso components IsNot Nothing Then
            components.Dispose()
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.chkBrightnessAuto = New System.Windows.Forms.CheckBox
        Me.sldBrightness = New System.Windows.Forms.TrackBar
        Me.label1 = New System.Windows.Forms.Label
        Me.IcImagingControl1 = New TIS.Imaging.ICImagingControl
        CType(Me.sldBrightness, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'chkBrightnessAuto
        '
        Me.chkBrightnessAuto.AutoSize = True
        Me.chkBrightnessAuto.Location = New System.Drawing.Point(367, 300)
        Me.chkBrightnessAuto.Name = "chkBrightnessAuto"
        Me.chkBrightnessAuto.Size = New System.Drawing.Size(48, 17)
        Me.chkBrightnessAuto.TabIndex = 6
        Me.chkBrightnessAuto.Text = "Auto"
        Me.chkBrightnessAuto.UseVisualStyleBackColor = True
        '
        'sldBrightness
        '
        Me.sldBrightness.Location = New System.Drawing.Point(75, 293)
        Me.sldBrightness.Name = "sldBrightness"
        Me.sldBrightness.Size = New System.Drawing.Size(286, 45)
        Me.sldBrightness.TabIndex = 5
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.Location = New System.Drawing.Point(13, 297)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(56, 13)
        Me.label1.TabIndex = 4
        Me.label1.Text = "Brightness"
        '
        'IcImagingControl1
        '
        Me.IcImagingControl1.BackColor = System.Drawing.Color.White
        Me.IcImagingControl1.LiveDisplayPosition = New System.Drawing.Point(0, 0)
        Me.IcImagingControl1.Location = New System.Drawing.Point(7, 10)
        Me.IcImagingControl1.Name = "IcImagingControl1"
        Me.IcImagingControl1.Size = New System.Drawing.Size(425, 273)
        Me.IcImagingControl1.TabIndex = 7
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(438, 331)
        Me.Controls.Add(Me.IcImagingControl1)
        Me.Controls.Add(Me.chkBrightnessAuto)
        Me.Controls.Add(Me.sldBrightness)
        Me.Controls.Add(Me.label1)
        Me.Name = "Form1"
        Me.Text = "VCD Simple"
        CType(Me.sldBrightness, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents chkBrightnessAuto As System.Windows.Forms.CheckBox
    Private WithEvents sldBrightness As System.Windows.Forms.TrackBar
    Private WithEvents label1 As System.Windows.Forms.Label
    Friend WithEvents IcImagingControl1 As TIS.Imaging.ICImagingControl

End Class
