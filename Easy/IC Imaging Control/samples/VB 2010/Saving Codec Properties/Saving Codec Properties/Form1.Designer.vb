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
        Me.cmdShowPropertyPage = New System.Windows.Forms.Button
        Me.cmdLoadData = New System.Windows.Forms.Button
        Me.cmdSaveData = New System.Windows.Forms.Button
        Me.cboVideoCodec = New System.Windows.Forms.ComboBox
        Me.IcImagingControl1 = New TIS.Imaging.ICImagingControl
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'cmdShowPropertyPage
        '
        Me.cmdShowPropertyPage.Location = New System.Drawing.Point(241, 208)
        Me.cmdShowPropertyPage.Name = "cmdShowPropertyPage"
        Me.cmdShowPropertyPage.Size = New System.Drawing.Size(112, 23)
        Me.cmdShowPropertyPage.TabIndex = 8
        Me.cmdShowPropertyPage.Text = "Show Property Page"
        Me.cmdShowPropertyPage.UseVisualStyleBackColor = True
        '
        'cmdLoadData
        '
        Me.cmdLoadData.Location = New System.Drawing.Point(90, 208)
        Me.cmdLoadData.Name = "cmdLoadData"
        Me.cmdLoadData.Size = New System.Drawing.Size(75, 23)
        Me.cmdLoadData.TabIndex = 7
        Me.cmdLoadData.Text = "Load Data"
        Me.cmdLoadData.UseVisualStyleBackColor = True
        '
        'cmdSaveData
        '
        Me.cmdSaveData.Location = New System.Drawing.Point(9, 208)
        Me.cmdSaveData.Name = "cmdSaveData"
        Me.cmdSaveData.Size = New System.Drawing.Size(75, 23)
        Me.cmdSaveData.TabIndex = 6
        Me.cmdSaveData.Text = "Save Data"
        Me.cmdSaveData.UseVisualStyleBackColor = True
        '
        'cboVideoCodec
        '
        Me.cboVideoCodec.FormattingEnabled = True
        Me.cboVideoCodec.Location = New System.Drawing.Point(9, 181)
        Me.cboVideoCodec.Name = "cboVideoCodec"
        Me.cboVideoCodec.Size = New System.Drawing.Size(344, 21)
        Me.cboVideoCodec.TabIndex = 5
        '
        'IcImagingControl1
        '
        Me.IcImagingControl1.BackColor = System.Drawing.Color.White
        Me.IcImagingControl1.LiveDisplayPosition = New System.Drawing.Point(0, 0)
        Me.IcImagingControl1.Location = New System.Drawing.Point(8, 8)
        Me.IcImagingControl1.Name = "IcImagingControl1"
        Me.IcImagingControl1.Size = New System.Drawing.Size(344, 163)
        Me.IcImagingControl1.TabIndex = 9
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(360, 237)
        Me.Controls.Add(Me.IcImagingControl1)
        Me.Controls.Add(Me.cmdShowPropertyPage)
        Me.Controls.Add(Me.cmdLoadData)
        Me.Controls.Add(Me.cmdSaveData)
        Me.Controls.Add(Me.cboVideoCodec)
        Me.Name = "Form1"
        Me.Text = "Saving Codec Properties"
        CType(Me.IcImagingControl1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents cmdShowPropertyPage As System.Windows.Forms.Button
    Private WithEvents cmdLoadData As System.Windows.Forms.Button
    Private WithEvents cmdSaveData As System.Windows.Forms.Button
    Private WithEvents cboVideoCodec As System.Windows.Forms.ComboBox
    Friend WithEvents IcImagingControl1 As TIS.Imaging.ICImagingControl

End Class
