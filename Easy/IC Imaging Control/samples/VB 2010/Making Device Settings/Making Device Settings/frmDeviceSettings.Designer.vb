<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmDeviceSettings
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
        Me.lblErrorMessage = New System.Windows.Forms.Label
        Me.cmdOK = New System.Windows.Forms.Button
        Me.cmdCancel = New System.Windows.Forms.Button
        Me.chkFlipH = New System.Windows.Forms.CheckBox
        Me.chkFlipV = New System.Windows.Forms.CheckBox
        Me.label6 = New System.Windows.Forms.Label
        Me.txtSerial = New System.Windows.Forms.TextBox
        Me.label5 = New System.Windows.Forms.Label
        Me.cboInputChannel = New System.Windows.Forms.ComboBox
        Me.label4 = New System.Windows.Forms.Label
        Me.label3 = New System.Windows.Forms.Label
        Me.cboFrameRate = New System.Windows.Forms.ComboBox
        Me.cboVideoFormat = New System.Windows.Forms.ComboBox
        Me.cboVideoNorm = New System.Windows.Forms.ComboBox
        Me.cboDevice = New System.Windows.Forms.ComboBox
        Me.label2 = New System.Windows.Forms.Label
        Me.label1 = New System.Windows.Forms.Label
        Me.SuspendLayout()
        '
        'lblErrorMessage
        '
        Me.lblErrorMessage.AutoSize = True
        Me.lblErrorMessage.Location = New System.Drawing.Point(11, 177)
        Me.lblErrorMessage.Name = "lblErrorMessage"
        Me.lblErrorMessage.Size = New System.Drawing.Size(70, 13)
        Me.lblErrorMessage.TabIndex = 33
        Me.lblErrorMessage.Text = "<Error Label>"
        Me.lblErrorMessage.Visible = False
        '
        'cmdOK
        '
        Me.cmdOK.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.cmdOK.Location = New System.Drawing.Point(133, 198)
        Me.cmdOK.Name = "cmdOK"
        Me.cmdOK.Size = New System.Drawing.Size(75, 23)
        Me.cmdOK.TabIndex = 32
        Me.cmdOK.Text = "OK"
        Me.cmdOK.UseVisualStyleBackColor = True
        '
        'cmdCancel
        '
        Me.cmdCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.cmdCancel.Location = New System.Drawing.Point(214, 198)
        Me.cmdCancel.Name = "cmdCancel"
        Me.cmdCancel.Size = New System.Drawing.Size(75, 23)
        Me.cmdCancel.TabIndex = 31
        Me.cmdCancel.Text = "Cancel"
        Me.cmdCancel.UseVisualStyleBackColor = True
        '
        'chkFlipH
        '
        Me.chkFlipH.AutoSize = True
        Me.chkFlipH.Location = New System.Drawing.Point(199, 173)
        Me.chkFlipH.Name = "chkFlipH"
        Me.chkFlipH.Size = New System.Drawing.Size(92, 17)
        Me.chkFlipH.TabIndex = 30
        Me.chkFlipH.Text = "Flip Horizontal"
        Me.chkFlipH.UseVisualStyleBackColor = True
        '
        'chkFlipV
        '
        Me.chkFlipV.AutoSize = True
        Me.chkFlipV.Location = New System.Drawing.Point(106, 173)
        Me.chkFlipV.Name = "chkFlipV"
        Me.chkFlipV.Size = New System.Drawing.Size(80, 17)
        Me.chkFlipV.TabIndex = 29
        Me.chkFlipV.Text = "Flip Vertical"
        Me.chkFlipV.UseVisualStyleBackColor = True
        '
        'label6
        '
        Me.label6.AutoSize = True
        Me.label6.Location = New System.Drawing.Point(12, 150)
        Me.label6.Name = "label6"
        Me.label6.Size = New System.Drawing.Size(73, 13)
        Me.label6.TabIndex = 28
        Me.label6.Text = "Serial Number"
        '
        'txtSerial
        '
        Me.txtSerial.Location = New System.Drawing.Point(106, 147)
        Me.txtSerial.Name = "txtSerial"
        Me.txtSerial.ReadOnly = True
        Me.txtSerial.Size = New System.Drawing.Size(185, 20)
        Me.txtSerial.TabIndex = 27
        '
        'label5
        '
        Me.label5.AutoSize = True
        Me.label5.Location = New System.Drawing.Point(12, 123)
        Me.label5.Name = "label5"
        Me.label5.Size = New System.Drawing.Size(73, 13)
        Me.label5.TabIndex = 26
        Me.label5.Text = "Input Channel"
        '
        'cboInputChannel
        '
        Me.cboInputChannel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboInputChannel.FormattingEnabled = True
        Me.cboInputChannel.Location = New System.Drawing.Point(106, 120)
        Me.cboInputChannel.Name = "cboInputChannel"
        Me.cboInputChannel.Size = New System.Drawing.Size(185, 21)
        Me.cboInputChannel.TabIndex = 25
        '
        'label4
        '
        Me.label4.AutoSize = True
        Me.label4.Location = New System.Drawing.Point(12, 96)
        Me.label4.Name = "label4"
        Me.label4.Size = New System.Drawing.Size(62, 13)
        Me.label4.TabIndex = 24
        Me.label4.Text = "Frame Rate"
        '
        'label3
        '
        Me.label3.AutoSize = True
        Me.label3.Location = New System.Drawing.Point(12, 69)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(69, 13)
        Me.label3.TabIndex = 23
        Me.label3.Text = "Video Format"
        '
        'cboFrameRate
        '
        Me.cboFrameRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboFrameRate.FormattingEnabled = True
        Me.cboFrameRate.Location = New System.Drawing.Point(106, 93)
        Me.cboFrameRate.Name = "cboFrameRate"
        Me.cboFrameRate.Size = New System.Drawing.Size(185, 21)
        Me.cboFrameRate.TabIndex = 22
        '
        'cboVideoFormat
        '
        Me.cboVideoFormat.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboVideoFormat.FormattingEnabled = True
        Me.cboVideoFormat.Location = New System.Drawing.Point(106, 66)
        Me.cboVideoFormat.Name = "cboVideoFormat"
        Me.cboVideoFormat.Size = New System.Drawing.Size(185, 21)
        Me.cboVideoFormat.TabIndex = 21
        '
        'cboVideoNorm
        '
        Me.cboVideoNorm.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboVideoNorm.FormattingEnabled = True
        Me.cboVideoNorm.Location = New System.Drawing.Point(106, 39)
        Me.cboVideoNorm.Name = "cboVideoNorm"
        Me.cboVideoNorm.Size = New System.Drawing.Size(185, 21)
        Me.cboVideoNorm.TabIndex = 20
        '
        'cboDevice
        '
        Me.cboDevice.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboDevice.FormattingEnabled = True
        Me.cboDevice.Location = New System.Drawing.Point(106, 12)
        Me.cboDevice.Name = "cboDevice"
        Me.cboDevice.Size = New System.Drawing.Size(185, 21)
        Me.cboDevice.TabIndex = 19
        '
        'label2
        '
        Me.label2.AutoSize = True
        Me.label2.Location = New System.Drawing.Point(12, 42)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(62, 13)
        Me.label2.TabIndex = 18
        Me.label2.Text = "Video Norm"
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.Location = New System.Drawing.Point(12, 15)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(41, 13)
        Me.label1.TabIndex = 17
        Me.label1.Text = "Device"
        '
        'frmDeviceSettings
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(303, 230)
        Me.Controls.Add(Me.lblErrorMessage)
        Me.Controls.Add(Me.cmdOK)
        Me.Controls.Add(Me.cmdCancel)
        Me.Controls.Add(Me.chkFlipH)
        Me.Controls.Add(Me.chkFlipV)
        Me.Controls.Add(Me.label6)
        Me.Controls.Add(Me.txtSerial)
        Me.Controls.Add(Me.label5)
        Me.Controls.Add(Me.cboInputChannel)
        Me.Controls.Add(Me.label4)
        Me.Controls.Add(Me.label3)
        Me.Controls.Add(Me.cboFrameRate)
        Me.Controls.Add(Me.cboVideoFormat)
        Me.Controls.Add(Me.cboVideoNorm)
        Me.Controls.Add(Me.cboDevice)
        Me.Controls.Add(Me.label2)
        Me.Controls.Add(Me.label1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Name = "frmDeviceSettings"
        Me.Text = "Custom Device Settings"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents lblErrorMessage As System.Windows.Forms.Label
    Private WithEvents cmdOK As System.Windows.Forms.Button
    Private WithEvents cmdCancel As System.Windows.Forms.Button
    Private WithEvents chkFlipH As System.Windows.Forms.CheckBox
    Private WithEvents chkFlipV As System.Windows.Forms.CheckBox
    Private WithEvents label6 As System.Windows.Forms.Label
    Private WithEvents txtSerial As System.Windows.Forms.TextBox
    Private WithEvents label5 As System.Windows.Forms.Label
    Private WithEvents cboInputChannel As System.Windows.Forms.ComboBox
    Private WithEvents label4 As System.Windows.Forms.Label
    Private WithEvents label3 As System.Windows.Forms.Label
    Private WithEvents cboFrameRate As System.Windows.Forms.ComboBox
    Private WithEvents cboVideoFormat As System.Windows.Forms.ComboBox
    Private WithEvents cboVideoNorm As System.Windows.Forms.ComboBox
    Private WithEvents cboDevice As System.Windows.Forms.ComboBox
    Private WithEvents label2 As System.Windows.Forms.Label
    Private WithEvents label1 As System.Windows.Forms.Label
End Class
