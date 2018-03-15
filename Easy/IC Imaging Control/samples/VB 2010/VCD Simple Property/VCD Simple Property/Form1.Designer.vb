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
        Me.WhitebalanceOnePushButton = New System.Windows.Forms.Button
        Me.WhiteBalBlueLabel = New System.Windows.Forms.Label
        Me.label3 = New System.Windows.Forms.Label
        Me.WhiteBalBlueTrackBar = New System.Windows.Forms.TrackBar
        Me.WhitebalanceCheckBox = New System.Windows.Forms.CheckBox
        Me.BrightnessAutoCheckBox = New System.Windows.Forms.CheckBox
        Me.WhiteBalRedLabel = New System.Windows.Forms.Label
        Me.BrightnessValueLabel = New System.Windows.Forms.Label
        Me.WhiteBalRedTrackBar = New System.Windows.Forms.TrackBar
        Me.BrightnessTrackBar = New System.Windows.Forms.TrackBar
        Me.label2 = New System.Windows.Forms.Label
        Me.label1 = New System.Windows.Forms.Label
        Me.IcImagingControl1 = New TIS.Imaging.ICImagingControl
        CType(Me.WhiteBalBlueTrackBar, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.WhiteBalRedTrackBar, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.BrightnessTrackBar, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'WhitebalanceOnePushButton
        '
        Me.WhitebalanceOnePushButton.Location = New System.Drawing.Point(470, 434)
        Me.WhitebalanceOnePushButton.Name = "WhitebalanceOnePushButton"
        Me.WhitebalanceOnePushButton.Size = New System.Drawing.Size(68, 24)
        Me.WhitebalanceOnePushButton.TabIndex = 24
        Me.WhitebalanceOnePushButton.Text = "One Push"
        Me.WhitebalanceOnePushButton.UseVisualStyleBackColor = True
        '
        'WhiteBalBlueLabel
        '
        Me.WhiteBalBlueLabel.AutoSize = True
        Me.WhiteBalBlueLabel.Location = New System.Drawing.Point(422, 459)
        Me.WhiteBalBlueLabel.Name = "WhiteBalBlueLabel"
        Me.WhiteBalBlueLabel.Size = New System.Drawing.Size(13, 13)
        Me.WhiteBalBlueLabel.TabIndex = 23
        Me.WhiteBalBlueLabel.Text = "0"
        '
        'label3
        '
        Me.label3.AutoSize = True
        Me.label3.Location = New System.Drawing.Point(19, 459)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(97, 13)
        Me.label3.TabIndex = 22
        Me.label3.Text = "Whitebalance Blue"
        '
        'WhiteBalBlueTrackBar
        '
        Me.WhiteBalBlueTrackBar.Location = New System.Drawing.Point(144, 450)
        Me.WhiteBalBlueTrackBar.Name = "WhiteBalBlueTrackBar"
        Me.WhiteBalBlueTrackBar.Size = New System.Drawing.Size(259, 45)
        Me.WhiteBalBlueTrackBar.TabIndex = 21
        '
        'WhitebalanceCheckBox
        '
        Me.WhitebalanceCheckBox.AutoSize = True
        Me.WhitebalanceCheckBox.Location = New System.Drawing.Point(470, 411)
        Me.WhitebalanceCheckBox.Name = "WhitebalanceCheckBox"
        Me.WhitebalanceCheckBox.Size = New System.Drawing.Size(48, 17)
        Me.WhitebalanceCheckBox.TabIndex = 20
        Me.WhitebalanceCheckBox.Text = "Auto"
        Me.WhitebalanceCheckBox.UseVisualStyleBackColor = True
        '
        'BrightnessAutoCheckBox
        '
        Me.BrightnessAutoCheckBox.AutoSize = True
        Me.BrightnessAutoCheckBox.Location = New System.Drawing.Point(470, 353)
        Me.BrightnessAutoCheckBox.Name = "BrightnessAutoCheckBox"
        Me.BrightnessAutoCheckBox.Size = New System.Drawing.Size(48, 17)
        Me.BrightnessAutoCheckBox.TabIndex = 19
        Me.BrightnessAutoCheckBox.Text = "Auto"
        Me.BrightnessAutoCheckBox.UseVisualStyleBackColor = True
        '
        'WhiteBalRedLabel
        '
        Me.WhiteBalRedLabel.AutoSize = True
        Me.WhiteBalRedLabel.Location = New System.Drawing.Point(422, 414)
        Me.WhiteBalRedLabel.Name = "WhiteBalRedLabel"
        Me.WhiteBalRedLabel.Size = New System.Drawing.Size(13, 13)
        Me.WhiteBalRedLabel.TabIndex = 18
        Me.WhiteBalRedLabel.Text = "0"
        '
        'BrightnessValueLabel
        '
        Me.BrightnessValueLabel.AutoSize = True
        Me.BrightnessValueLabel.Location = New System.Drawing.Point(422, 357)
        Me.BrightnessValueLabel.Name = "BrightnessValueLabel"
        Me.BrightnessValueLabel.Size = New System.Drawing.Size(13, 13)
        Me.BrightnessValueLabel.TabIndex = 17
        Me.BrightnessValueLabel.Text = "0"
        '
        'WhiteBalRedTrackBar
        '
        Me.WhiteBalRedTrackBar.Location = New System.Drawing.Point(144, 399)
        Me.WhiteBalRedTrackBar.Name = "WhiteBalRedTrackBar"
        Me.WhiteBalRedTrackBar.Size = New System.Drawing.Size(259, 45)
        Me.WhiteBalRedTrackBar.TabIndex = 16
        '
        'BrightnessTrackBar
        '
        Me.BrightnessTrackBar.Location = New System.Drawing.Point(144, 348)
        Me.BrightnessTrackBar.Name = "BrightnessTrackBar"
        Me.BrightnessTrackBar.Size = New System.Drawing.Size(259, 45)
        Me.BrightnessTrackBar.TabIndex = 15
        '
        'label2
        '
        Me.label2.AutoSize = True
        Me.label2.Location = New System.Drawing.Point(19, 414)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(96, 13)
        Me.label2.TabIndex = 14
        Me.label2.Text = "Whitebalance Red"
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.Location = New System.Drawing.Point(19, 357)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(56, 13)
        Me.label1.TabIndex = 13
        Me.label1.Text = "Brightness"
        '
        'IcImagingControl1
        '
        Me.IcImagingControl1.BackColor = System.Drawing.Color.White
        Me.IcImagingControl1.LiveDisplayPosition = New System.Drawing.Point(0, 0)
        Me.IcImagingControl1.Location = New System.Drawing.Point(11, 10)
        Me.IcImagingControl1.Name = "IcImagingControl1"
        Me.IcImagingControl1.Size = New System.Drawing.Size(526, 329)
        Me.IcImagingControl1.TabIndex = 25
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(552, 499)
        Me.Controls.Add(Me.IcImagingControl1)
        Me.Controls.Add(Me.WhitebalanceOnePushButton)
        Me.Controls.Add(Me.WhiteBalBlueLabel)
        Me.Controls.Add(Me.label3)
        Me.Controls.Add(Me.WhiteBalBlueTrackBar)
        Me.Controls.Add(Me.WhitebalanceCheckBox)
        Me.Controls.Add(Me.BrightnessAutoCheckBox)
        Me.Controls.Add(Me.WhiteBalRedLabel)
        Me.Controls.Add(Me.BrightnessValueLabel)
        Me.Controls.Add(Me.WhiteBalRedTrackBar)
        Me.Controls.Add(Me.BrightnessTrackBar)
        Me.Controls.Add(Me.label2)
        Me.Controls.Add(Me.label1)
        Me.Name = "Form1"
        Me.Text = "VCD Simple Property"
        CType(Me.WhiteBalBlueTrackBar, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.WhiteBalRedTrackBar, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.BrightnessTrackBar, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents WhitebalanceOnePushButton As System.Windows.Forms.Button
    Private WithEvents WhiteBalBlueLabel As System.Windows.Forms.Label
    Private WithEvents label3 As System.Windows.Forms.Label
    Private WithEvents WhiteBalBlueTrackBar As System.Windows.Forms.TrackBar
    Private WithEvents WhitebalanceCheckBox As System.Windows.Forms.CheckBox
    Private WithEvents BrightnessAutoCheckBox As System.Windows.Forms.CheckBox
    Private WithEvents WhiteBalRedLabel As System.Windows.Forms.Label
    Private WithEvents BrightnessValueLabel As System.Windows.Forms.Label
    Private WithEvents WhiteBalRedTrackBar As System.Windows.Forms.TrackBar
    Private WithEvents BrightnessTrackBar As System.Windows.Forms.TrackBar
    Private WithEvents label2 As System.Windows.Forms.Label
    Private WithEvents label1 As System.Windows.Forms.Label
    Friend WithEvents IcImagingControl1 As TIS.Imaging.ICImagingControl

End Class
