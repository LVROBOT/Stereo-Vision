<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.cmdDevice = New System.Windows.Forms.Button
        Me.cmdStopLive = New System.Windows.Forms.Button
        Me.cmdStartLive = New System.Windows.Forms.Button
        Me.IcImagingControl1 = New TIS.Imaging.ICImagingControl
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'cmdDevice
        '
        Me.cmdDevice.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.cmdDevice.Location = New System.Drawing.Point(319, 310)
        Me.cmdDevice.Name = "cmdDevice"
        Me.cmdDevice.Size = New System.Drawing.Size(75, 23)
        Me.cmdDevice.TabIndex = 6
        Me.cmdDevice.Text = "Device"
        Me.cmdDevice.UseVisualStyleBackColor = True
        '
        'cmdStopLive
        '
        Me.cmdStopLive.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.cmdStopLive.Location = New System.Drawing.Point(93, 310)
        Me.cmdStopLive.Name = "cmdStopLive"
        Me.cmdStopLive.Size = New System.Drawing.Size(75, 23)
        Me.cmdStopLive.TabIndex = 5
        Me.cmdStopLive.Text = "Stop Live"
        Me.cmdStopLive.UseVisualStyleBackColor = True
        '
        'cmdStartLive
        '
        Me.cmdStartLive.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.cmdStartLive.Location = New System.Drawing.Point(12, 310)
        Me.cmdStartLive.Name = "cmdStartLive"
        Me.cmdStartLive.Size = New System.Drawing.Size(75, 23)
        Me.cmdStartLive.TabIndex = 4
        Me.cmdStartLive.Text = "Start Live"
        Me.cmdStartLive.UseVisualStyleBackColor = True
        '
        'IcImagingControl1
        '
        Me.IcImagingControl1.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
                    Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.IcImagingControl1.BackColor = System.Drawing.Color.White
        Me.IcImagingControl1.ImageAvailableExecutionMode = TIS.Imaging.EventExecutionMode.MultiThreaded
        Me.IcImagingControl1.LiveDisplayPosition = New System.Drawing.Point(0, 0)
        Me.IcImagingControl1.Location = New System.Drawing.Point(12, 12)
        Me.IcImagingControl1.Name = "IcImagingControl1"
        Me.IcImagingControl1.Size = New System.Drawing.Size(382, 292)
        Me.IcImagingControl1.TabIndex = 7
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(406, 345)
        Me.Controls.Add(Me.IcImagingControl1)
        Me.Controls.Add(Me.cmdDevice)
        Me.Controls.Add(Me.cmdStopLive)
        Me.Controls.Add(Me.cmdStartLive)
        Me.Name = "Form1"
        Me.Text = "Making Device Settings"
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents cmdDevice As System.Windows.Forms.Button
    Private WithEvents cmdStopLive As System.Windows.Forms.Button
    Private WithEvents cmdStartLive As System.Windows.Forms.Button
    Friend WithEvents IcImagingControl1 As TIS.Imaging.ICImagingControl

End Class
