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
        Me.label1 = New System.Windows.Forms.Label
        Me.sldThresholdSlider = New System.Windows.Forms.TrackBar
        Me.cmdROICommit = New System.Windows.Forms.Button
        Me.cmdSettings = New System.Windows.Forms.Button
        Me.cmdStop = New System.Windows.Forms.Button
        Me.cmdDevice = New System.Windows.Forms.Button
        Me.cmdStart = New System.Windows.Forms.Button
        Me.IcImagingControl1 = New TIS.Imaging.ICImagingControl
        CType(Me.sldThresholdSlider, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.Location = New System.Drawing.Point(396, 51)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(54, 13)
        Me.label1.TabIndex = 14
        Me.label1.Text = "Threshold"
        '
        'sldThresholdSlider
        '
        Me.sldThresholdSlider.Location = New System.Drawing.Point(282, 12)
        Me.sldThresholdSlider.Maximum = 100
        Me.sldThresholdSlider.Name = "sldThresholdSlider"
        Me.sldThresholdSlider.Size = New System.Drawing.Size(282, 45)
        Me.sldThresholdSlider.TabIndex = 13
        '
        'cmdROICommit
        '
        Me.cmdROICommit.Location = New System.Drawing.Point(170, 12)
        Me.cmdROICommit.Name = "cmdROICommit"
        Me.cmdROICommit.Size = New System.Drawing.Size(106, 23)
        Me.cmdROICommit.TabIndex = 12
        Me.cmdROICommit.Text = "Set Current ROI"
        Me.cmdROICommit.UseVisualStyleBackColor = True
        '
        'cmdSettings
        '
        Me.cmdSettings.Location = New System.Drawing.Point(89, 41)
        Me.cmdSettings.Name = "cmdSettings"
        Me.cmdSettings.Size = New System.Drawing.Size(75, 23)
        Me.cmdSettings.TabIndex = 11
        Me.cmdSettings.Text = "Settings"
        Me.cmdSettings.UseVisualStyleBackColor = True
        '
        'cmdStop
        '
        Me.cmdStop.Location = New System.Drawing.Point(89, 12)
        Me.cmdStop.Name = "cmdStop"
        Me.cmdStop.Size = New System.Drawing.Size(75, 23)
        Me.cmdStop.TabIndex = 10
        Me.cmdStop.Text = "Stop"
        Me.cmdStop.UseVisualStyleBackColor = True
        '
        'cmdDevice
        '
        Me.cmdDevice.Location = New System.Drawing.Point(8, 41)
        Me.cmdDevice.Name = "cmdDevice"
        Me.cmdDevice.Size = New System.Drawing.Size(75, 23)
        Me.cmdDevice.TabIndex = 9
        Me.cmdDevice.Text = "Device"
        Me.cmdDevice.UseVisualStyleBackColor = True
        '
        'cmdStart
        '
        Me.cmdStart.Location = New System.Drawing.Point(8, 12)
        Me.cmdStart.Name = "cmdStart"
        Me.cmdStart.Size = New System.Drawing.Size(75, 23)
        Me.cmdStart.TabIndex = 8
        Me.cmdStart.Text = "Start"
        Me.cmdStart.UseVisualStyleBackColor = True
        '
        'IcImagingControl1
        '
        Me.IcImagingControl1.BackColor = System.Drawing.Color.White
        Me.IcImagingControl1.ImageAvailableExecutionMode = TIS.Imaging.EventExecutionMode.MultiThreaded
        Me.IcImagingControl1.LiveDisplayPosition = New System.Drawing.Point(0, 0)
        Me.IcImagingControl1.Location = New System.Drawing.Point(8, 71)
        Me.IcImagingControl1.Name = "IcImagingControl1"
        Me.IcImagingControl1.Size = New System.Drawing.Size(555, 326)
        Me.IcImagingControl1.TabIndex = 15
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(575, 404)
        Me.Controls.Add(Me.IcImagingControl1)
        Me.Controls.Add(Me.label1)
        Me.Controls.Add(Me.sldThresholdSlider)
        Me.Controls.Add(Me.cmdROICommit)
        Me.Controls.Add(Me.cmdSettings)
        Me.Controls.Add(Me.cmdStop)
        Me.Controls.Add(Me.cmdDevice)
        Me.Controls.Add(Me.cmdStart)
        Me.Name = "Form1"
        Me.Text = "Advanced Image Processing"
        CType(Me.sldThresholdSlider, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents label1 As System.Windows.Forms.Label
    Private WithEvents sldThresholdSlider As System.Windows.Forms.TrackBar
    Private WithEvents cmdROICommit As System.Windows.Forms.Button
    Private WithEvents cmdSettings As System.Windows.Forms.Button
    Private WithEvents cmdStop As System.Windows.Forms.Button
    Private WithEvents cmdDevice As System.Windows.Forms.Button
    Private WithEvents cmdStart As System.Windows.Forms.Button
    Friend WithEvents IcImagingControl1 As TIS.Imaging.ICImagingControl

End Class
