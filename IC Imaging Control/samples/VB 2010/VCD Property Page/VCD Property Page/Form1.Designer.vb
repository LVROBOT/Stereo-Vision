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
        Me.cmdShowOriginalDialog = New System.Windows.Forms.Button
        Me.cmdShowMyDialog = New System.Windows.Forms.Button
        Me.cmdSelectDevice = New System.Windows.Forms.Button
        Me.IcImagingControl1 = New TIS.Imaging.ICImagingControl
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'cmdShowOriginalDialog
        '
        Me.cmdShowOriginalDialog.Location = New System.Drawing.Point(473, 86)
        Me.cmdShowOriginalDialog.Name = "cmdShowOriginalDialog"
        Me.cmdShowOriginalDialog.Size = New System.Drawing.Size(98, 23)
        Me.cmdShowOriginalDialog.TabIndex = 6
        Me.cmdShowOriginalDialog.Text = "Show Original Page"
        Me.cmdShowOriginalDialog.UseVisualStyleBackColor = True
        '
        'cmdShowMyDialog
        '
        Me.cmdShowMyDialog.Location = New System.Drawing.Point(473, 57)
        Me.cmdShowMyDialog.Name = "cmdShowMyDialog"
        Me.cmdShowMyDialog.Size = New System.Drawing.Size(98, 23)
        Me.cmdShowMyDialog.TabIndex = 5
        Me.cmdShowMyDialog.Text = "Show My Dialog"
        Me.cmdShowMyDialog.UseVisualStyleBackColor = True
        '
        'cmdSelectDevice
        '
        Me.cmdSelectDevice.Location = New System.Drawing.Point(473, 12)
        Me.cmdSelectDevice.Name = "cmdSelectDevice"
        Me.cmdSelectDevice.Size = New System.Drawing.Size(98, 23)
        Me.cmdSelectDevice.TabIndex = 4
        Me.cmdSelectDevice.Text = "Select Device"
        Me.cmdSelectDevice.UseVisualStyleBackColor = True
        '
        'IcImagingControl1
        '
        Me.IcImagingControl1.BackColor = System.Drawing.Color.White
        Me.IcImagingControl1.LiveDisplayPosition = New System.Drawing.Point(0, 0)
        Me.IcImagingControl1.Location = New System.Drawing.Point(10, 8)
        Me.IcImagingControl1.Name = "IcImagingControl1"
        Me.IcImagingControl1.Size = New System.Drawing.Size(453, 364)
        Me.IcImagingControl1.TabIndex = 7
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(583, 381)
        Me.Controls.Add(Me.IcImagingControl1)
        Me.Controls.Add(Me.cmdShowOriginalDialog)
        Me.Controls.Add(Me.cmdShowMyDialog)
        Me.Controls.Add(Me.cmdSelectDevice)
        Me.Name = "Form1"
        Me.Text = "VCD Property Page Sample"
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents cmdShowOriginalDialog As System.Windows.Forms.Button
    Private WithEvents cmdShowMyDialog As System.Windows.Forms.Button
    Private WithEvents cmdSelectDevice As System.Windows.Forms.Button
    Friend WithEvents IcImagingControl1 As TIS.Imaging.ICImagingControl

End Class
