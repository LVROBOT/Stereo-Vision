<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class VCDPropertiesDlg
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
        Me.components = New System.ComponentModel.Container
        Me.UpdateButton = New System.Windows.Forms.Button
        Me.OKButton = New System.Windows.Forms.Button
        Me.UpdateTimer = New System.Windows.Forms.Timer(Me.components)
        Me.SuspendLayout()
        '
        'UpdateButton
        '
        Me.UpdateButton.Location = New System.Drawing.Point(296, 12)
        Me.UpdateButton.Name = "UpdateButton"
        Me.UpdateButton.Size = New System.Drawing.Size(75, 23)
        Me.UpdateButton.TabIndex = 3
        Me.UpdateButton.Text = "Update"
        Me.UpdateButton.UseVisualStyleBackColor = True
        '
        'OKButton
        '
        Me.OKButton.Location = New System.Drawing.Point(377, 12)
        Me.OKButton.Name = "OKButton"
        Me.OKButton.Size = New System.Drawing.Size(75, 23)
        Me.OKButton.TabIndex = 2
        Me.OKButton.Text = "OK"
        Me.OKButton.UseVisualStyleBackColor = True
        '
        'UpdateTimer
        '
        '
        'VCDPropertiesDlg
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(464, 41)
        Me.Controls.Add(Me.UpdateButton)
        Me.Controls.Add(Me.OKButton)
        Me.Name = "VCDPropertiesDlg"
        Me.Text = "VCDPropertiesDlg"
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents UpdateButton As System.Windows.Forms.Button
    Private WithEvents OKButton As System.Windows.Forms.Button
    Friend WithEvents UpdateTimer As System.Windows.Forms.Timer
End Class
