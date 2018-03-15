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
		Me.txtOutput = New System.Windows.Forms.TextBox()
		Me.cmdYGB1 = New System.Windows.Forms.Button()
		Me.cmdYGB0 = New System.Windows.Forms.Button()
		Me.cmdRGB32 = New System.Windows.Forms.Button()
		Me.cmdRGB24 = New System.Windows.Forms.Button()
		Me.cmdRGB8 = New System.Windows.Forms.Button()
		Me.cmdY800 = New System.Windows.Forms.Button()
		Me.IcImagingControl1 = New TIS.Imaging.ICImagingControl()
		Me.cmdY16 = New System.Windows.Forms.Button()
		CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.SuspendLayout()
		'
		'txtOutput
		'
		Me.txtOutput.Enabled = False
		Me.txtOutput.Location = New System.Drawing.Point(10, 247)
		Me.txtOutput.Multiline = True
		Me.txtOutput.Name = "txtOutput"
		Me.txtOutput.Size = New System.Drawing.Size(315, 76)
		Me.txtOutput.TabIndex = 14
		'
		'cmdYGB1
		'
		Me.cmdYGB1.Location = New System.Drawing.Point(332, 156)
		Me.cmdYGB1.Name = "cmdYGB1"
		Me.cmdYGB1.Size = New System.Drawing.Size(75, 23)
		Me.cmdYGB1.TabIndex = 13
		Me.cmdYGB1.Text = "YGB1"
		Me.cmdYGB1.UseVisualStyleBackColor = True
		'
		'cmdYGB0
		'
		Me.cmdYGB0.Location = New System.Drawing.Point(332, 127)
		Me.cmdYGB0.Name = "cmdYGB0"
		Me.cmdYGB0.Size = New System.Drawing.Size(75, 23)
		Me.cmdYGB0.TabIndex = 12
		Me.cmdYGB0.Text = "YGB0"
		Me.cmdYGB0.UseVisualStyleBackColor = True
		'
		'cmdRGB32
		'
		Me.cmdRGB32.Location = New System.Drawing.Point(332, 98)
		Me.cmdRGB32.Name = "cmdRGB32"
		Me.cmdRGB32.Size = New System.Drawing.Size(75, 23)
		Me.cmdRGB32.TabIndex = 11
		Me.cmdRGB32.Text = "RGB32"
		Me.cmdRGB32.UseVisualStyleBackColor = True
		'
		'cmdRGB24
		'
		Me.cmdRGB24.Location = New System.Drawing.Point(332, 69)
		Me.cmdRGB24.Name = "cmdRGB24"
		Me.cmdRGB24.Size = New System.Drawing.Size(75, 23)
		Me.cmdRGB24.TabIndex = 10
		Me.cmdRGB24.Text = "RGB24"
		Me.cmdRGB24.UseVisualStyleBackColor = True
		'
		'cmdRGB8
		'
		Me.cmdRGB8.Location = New System.Drawing.Point(332, 40)
		Me.cmdRGB8.Name = "cmdRGB8"
		Me.cmdRGB8.Size = New System.Drawing.Size(75, 23)
		Me.cmdRGB8.TabIndex = 9
		Me.cmdRGB8.Text = "RGB8"
		Me.cmdRGB8.UseVisualStyleBackColor = True
		'
		'cmdY800
		'
		Me.cmdY800.Location = New System.Drawing.Point(332, 11)
		Me.cmdY800.Name = "cmdY800"
		Me.cmdY800.Size = New System.Drawing.Size(75, 23)
		Me.cmdY800.TabIndex = 8
		Me.cmdY800.Text = "Y800"
		Me.cmdY800.UseVisualStyleBackColor = True
		'
		'IcImagingControl1
		'
		Me.IcImagingControl1.BackColor = System.Drawing.Color.White
		Me.IcImagingControl1.DeviceLostExecutionMode = TIS.Imaging.EventExecutionMode.AsyncInvoke
		Me.IcImagingControl1.ImageAvailableExecutionMode = TIS.Imaging.EventExecutionMode.MultiThreaded
		Me.IcImagingControl1.LiveDisplayPosition = New System.Drawing.Point(0, 0)
		Me.IcImagingControl1.Location = New System.Drawing.Point(9, 7)
		Me.IcImagingControl1.Name = "IcImagingControl1"
		Me.IcImagingControl1.Size = New System.Drawing.Size(315, 230)
		Me.IcImagingControl1.TabIndex = 15
		'
		'cmdY16
		'
		Me.cmdY16.Location = New System.Drawing.Point(332, 185)
		Me.cmdY16.Name = "cmdY16"
		Me.cmdY16.Size = New System.Drawing.Size(75, 23)
		Me.cmdY16.TabIndex = 16
		Me.cmdY16.Text = "Y16"
		Me.cmdY16.UseVisualStyleBackColor = True
		'
		'Form1
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(416, 334)
		Me.Controls.Add(Me.cmdY16)
		Me.Controls.Add(Me.IcImagingControl1)
		Me.Controls.Add(Me.txtOutput)
		Me.Controls.Add(Me.cmdYGB1)
		Me.Controls.Add(Me.cmdYGB0)
		Me.Controls.Add(Me.cmdRGB32)
		Me.Controls.Add(Me.cmdRGB24)
		Me.Controls.Add(Me.cmdRGB8)
		Me.Controls.Add(Me.cmdY800)
		Me.Name = "Form1"
		Me.Text = "Accessing an Image Buffer"
		CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).EndInit()
		Me.ResumeLayout(False)
		Me.PerformLayout()

	End Sub
    Private WithEvents txtOutput As System.Windows.Forms.TextBox
    Private WithEvents cmdYGB1 As System.Windows.Forms.Button
    Private WithEvents cmdYGB0 As System.Windows.Forms.Button
    Private WithEvents cmdRGB32 As System.Windows.Forms.Button
    Private WithEvents cmdRGB24 As System.Windows.Forms.Button
    Private WithEvents cmdRGB8 As System.Windows.Forms.Button
    Private WithEvents cmdY800 As System.Windows.Forms.Button
	Friend WithEvents IcImagingControl1 As TIS.Imaging.ICImagingControl
	Friend WithEvents cmdY16 As System.Windows.Forms.Button

End Class
