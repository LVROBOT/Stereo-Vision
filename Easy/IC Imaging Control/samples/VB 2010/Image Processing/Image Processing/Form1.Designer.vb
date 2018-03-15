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
        Me.cmdProcess = New System.Windows.Forms.Button
        Me.cmdStopLive = New System.Windows.Forms.Button
        Me.cmdStartLive = New System.Windows.Forms.Button
        Me.IcImagingControl1 = New TIS.Imaging.ICImagingControl
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'cmdProcess
        '
        Me.cmdProcess.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.cmdProcess.Location = New System.Drawing.Point(174, 493)
        Me.cmdProcess.Name = "cmdProcess"
        Me.cmdProcess.Size = New System.Drawing.Size(75, 23)
        Me.cmdProcess.TabIndex = 6
        Me.cmdProcess.Text = "Process"
        Me.cmdProcess.UseVisualStyleBackColor = True
        '
        'cmdStopLive
        '
        Me.cmdStopLive.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.cmdStopLive.Location = New System.Drawing.Point(93, 493)
        Me.cmdStopLive.Name = "cmdStopLive"
        Me.cmdStopLive.Size = New System.Drawing.Size(75, 23)
        Me.cmdStopLive.TabIndex = 5
        Me.cmdStopLive.Text = "Stop Live"
        Me.cmdStopLive.UseVisualStyleBackColor = True
        '
        'cmdStartLive
        '
        Me.cmdStartLive.Anchor = CType((System.Windows.Forms.AnchorStyles.Bottom Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.cmdStartLive.Location = New System.Drawing.Point(12, 493)
        Me.cmdStartLive.Name = "cmdStartLive"
        Me.cmdStartLive.Size = New System.Drawing.Size(75, 23)
        Me.cmdStartLive.TabIndex = 4
        Me.cmdStartLive.Text = "Start Live"
        '
        'IcImagingControl1
        '
        Me.IcImagingControl1.BackColor = System.Drawing.Color.White
        Me.IcImagingControl1.LiveDisplayPosition = New System.Drawing.Point(0, 0)
        Me.IcImagingControl1.Location = New System.Drawing.Point(11, 9)
        Me.IcImagingControl1.Name = "IcImagingControl1"
        Me.IcImagingControl1.Size = New System.Drawing.Size(626, 475)
        Me.IcImagingControl1.TabIndex = 7
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(657, 528)
        Me.Controls.Add(Me.IcImagingControl1)
        Me.Controls.Add(Me.cmdProcess)
        Me.Controls.Add(Me.cmdStopLive)
        Me.Controls.Add(Me.cmdStartLive)
        Me.Name = "Form1"
        Me.Text = "Performing Image Processing"
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents cmdProcess As System.Windows.Forms.Button
    Private WithEvents cmdStopLive As System.Windows.Forms.Button
    Private WithEvents cmdStartLive As System.Windows.Forms.Button
    Friend WithEvents IcImagingControl1 As TIS.Imaging.ICImagingControl

End Class
