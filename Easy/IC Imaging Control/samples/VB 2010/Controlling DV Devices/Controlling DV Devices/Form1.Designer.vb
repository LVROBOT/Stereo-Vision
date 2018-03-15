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
        Me.cmdETFastForward = New System.Windows.Forms.Button
        Me.cmdETRewind = New System.Windows.Forms.Button
        Me.cmdETStop = New System.Windows.Forms.Button
        Me.cmdETPlay = New System.Windows.Forms.Button
        Me.cmdStop = New System.Windows.Forms.Button
        Me.cmdStart = New System.Windows.Forms.Button
        Me.IcImagingControl1 = New TIS.Imaging.ICImagingControl
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'cmdETFastForward
        '
        Me.cmdETFastForward.Location = New System.Drawing.Point(312, 231)
        Me.cmdETFastForward.Name = "cmdETFastForward"
        Me.cmdETFastForward.Size = New System.Drawing.Size(55, 23)
        Me.cmdETFastForward.TabIndex = 12
        Me.cmdETFastForward.Text = "FF"
        Me.cmdETFastForward.UseVisualStyleBackColor = True
        '
        'cmdETRewind
        '
        Me.cmdETRewind.Location = New System.Drawing.Point(251, 231)
        Me.cmdETRewind.Name = "cmdETRewind"
        Me.cmdETRewind.Size = New System.Drawing.Size(55, 23)
        Me.cmdETRewind.TabIndex = 11
        Me.cmdETRewind.Text = "Rewind"
        Me.cmdETRewind.UseVisualStyleBackColor = True
        '
        'cmdETStop
        '
        Me.cmdETStop.Location = New System.Drawing.Point(190, 231)
        Me.cmdETStop.Name = "cmdETStop"
        Me.cmdETStop.Size = New System.Drawing.Size(55, 23)
        Me.cmdETStop.TabIndex = 10
        Me.cmdETStop.Text = "Stop"
        Me.cmdETStop.UseVisualStyleBackColor = True
        '
        'cmdETPlay
        '
        Me.cmdETPlay.Location = New System.Drawing.Point(129, 231)
        Me.cmdETPlay.Name = "cmdETPlay"
        Me.cmdETPlay.Size = New System.Drawing.Size(55, 23)
        Me.cmdETPlay.TabIndex = 9
        Me.cmdETPlay.Text = "Play"
        Me.cmdETPlay.UseVisualStyleBackColor = True
        '
        'cmdStop
        '
        Me.cmdStop.Location = New System.Drawing.Point(68, 231)
        Me.cmdStop.Name = "cmdStop"
        Me.cmdStop.Size = New System.Drawing.Size(55, 23)
        Me.cmdStop.TabIndex = 8
        Me.cmdStop.Text = "Stop"
        Me.cmdStop.UseVisualStyleBackColor = True
        '
        'cmdStart
        '
        Me.cmdStart.Location = New System.Drawing.Point(7, 231)
        Me.cmdStart.Name = "cmdStart"
        Me.cmdStart.Size = New System.Drawing.Size(55, 23)
        Me.cmdStart.TabIndex = 7
        Me.cmdStart.Text = "Start"
        Me.cmdStart.UseVisualStyleBackColor = True
        '
        'IcImagingControl1
        '
        Me.IcImagingControl1.BackColor = System.Drawing.Color.White
        Me.IcImagingControl1.LiveDisplayPosition = New System.Drawing.Point(0, 0)
        Me.IcImagingControl1.Location = New System.Drawing.Point(8, 9)
        Me.IcImagingControl1.Name = "IcImagingControl1"
        Me.IcImagingControl1.Size = New System.Drawing.Size(358, 213)
        Me.IcImagingControl1.TabIndex = 13
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(377, 261)
        Me.Controls.Add(Me.IcImagingControl1)
        Me.Controls.Add(Me.cmdETFastForward)
        Me.Controls.Add(Me.cmdETRewind)
        Me.Controls.Add(Me.cmdETStop)
        Me.Controls.Add(Me.cmdETPlay)
        Me.Controls.Add(Me.cmdStop)
        Me.Controls.Add(Me.cmdStart)
        Me.Name = "Form1"
        Me.Text = "External Transport"
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents cmdETFastForward As System.Windows.Forms.Button
    Private WithEvents cmdETRewind As System.Windows.Forms.Button
    Private WithEvents cmdETStop As System.Windows.Forms.Button
    Private WithEvents cmdETPlay As System.Windows.Forms.Button
    Private WithEvents cmdStop As System.Windows.Forms.Button
    Private WithEvents cmdStart As System.Windows.Forms.Button
    Friend WithEvents IcImagingControl1 As TIS.Imaging.ICImagingControl

End Class
