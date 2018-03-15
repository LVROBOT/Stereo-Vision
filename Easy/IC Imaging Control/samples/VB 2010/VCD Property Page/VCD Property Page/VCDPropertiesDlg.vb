Public Class VCDPropertiesDlg

    Private Sub VCDPropertiesDlg_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Dim height As Integer = 7

        ' Iterate through the categories
        For Each Cat As String In IC.VCDPropertyItems.CategoryMap.Categories
            Dim subHeight As Integer
            ' Insert a frame for the category and controls for its items
            InsertCategory(Cat, 7, height, PAGE_WIDTH - 14, subHeight)
            height = height + subHeight
        Next

        ' Resize the page and adjust the button's positions
        Me.Width = PAGE_WIDTH
        Me.Height = height + OKButton.Height + 14 + 14 + 7
        OKButton.Top = height
        OKButton.Left = Me.Width - 14 - OKButton.Width
        UpdateButton.Top = height
        UpdateButton.Left = OKButton.Left - 7 - UpdateButton.Width
    End Sub

    Dim IC As TIS.Imaging.ICImagingControl

    ' The frame of the category that is currently filled with controls
    Dim currentFrame As System.Windows.Forms.GroupBox

    ' The controls of an item are put into a collection to allow fast updates after checking switches
    Dim currentSisterControls As System.Collections.ArrayList

    ' The Sliders of an item are put into a separate collection to allow even faster updates of
    ' connected sliders
    Dim currentSisterSliders As System.Collections.ArrayList

    ' This is a collection of all controls for the global update event
    Dim allControls As New System.Collections.ArrayList

    ' These constants control the layout of the property page
    Dim CTRL_HEIGHT As Short = 27
    Dim ROW_HEIGHT As Short = 33
    Dim PAGE_WIDTH As Short = 500

    Dim LABEL_WIDTH As Short = 100
    Dim SLIDER_WIDTH As Short = 180

    Dim COMBO_EXTRA_WIDTH As Short = 33
    Dim BUTTON_EXTRA_WIDTH As Short = 20
    Dim CHECK_EXTRA_WIDTH As Short = 27

    Dim CTRL_MARGIN As Short = 3

    Public Sub SetIC(ByRef ImagingControl As TIS.Imaging.ICImagingControl)
        IC = ImagingControl
    End Sub

    Private Sub CreateCategoryFrame(ByRef name As String, ByRef left As Integer, ByRef top As Integer, ByRef width As Integer)

        ' Create a frame object
        Dim frm As New System.Windows.Forms.GroupBox
        frm.Name = "Group" & allControls.Count
        Me.Controls.Add(frm)

        frm.Text = name
        frm.SetBounds(left, top, width, 0)

        ' Set the global frame reference to this new frame
        currentFrame = frm
    End Sub

    Private Sub CreatePropertyLabel(ByRef name As String, ByRef left As Integer, ByRef top As Integer, ByRef width As Integer, ByRef height As Integer)

        ' Create a label object
        Dim lbl As New System.Windows.Forms.Label
        lbl.Name = "Label" & allControls.Count
        currentFrame.Controls.Add(lbl)

        lbl.SetBounds(left, top, width, height)
        lbl.Text = name
    End Sub

    Private Sub CreateRangeSlider(ByRef itf As TIS.Imaging.VCDRangeProperty, ByRef left As Integer, ByRef top As Integer, ByRef width As Integer, ByRef height As Integer)

        ' Create a RangeSlider control
        Dim Slider As New RangeSlider
        Slider.Name = "slider" & allControls.Count()
        currentFrame.Controls.Add(Slider)

        Slider.SetBounds(left, top, width, height)

        ' Assign the range interface to the control
        Slider.AssignItf(itf)

        ' Add the control to the current sistercontrols collection
        currentSisterControls.Add(Slider)
        ' Add the control to the current sistersliders collection
        currentSisterSliders.Add(Slider)

        ' Tell the control the sistersliders group it belongs to
        Slider.setSisterSliders(currentSisterSliders)

        ' Add the control to the global list of all controls
        allControls.Add(Slider)
    End Sub

    Private Sub CreateAbsValSlider(ByRef itf As TIS.Imaging.VCDAbsoluteValueProperty, ByRef left As Integer, ByRef top As Integer, ByRef width As Integer, ByRef height As Integer)

        ' Create a AbsValSlider control
        Dim Slider As New AbsValSlider
        Slider.Name = "absvalslider" & allControls.Count()
        currentFrame.Controls.Add(Slider)

        Slider.SetBounds(left, top, width, height)

        ' Assign the absolute value interface to the control
        Slider.AssignItf(itf)

        ' Add the control to the current sistercontrols collection
        currentSisterControls.Add(Slider)
        ' Add the control to the current sistersliders collection
        currentSisterSliders.Add(Slider)

        ' Tell the control the sistersliders group it belongs to
        Slider.setSisterSliders(currentSisterSliders)

        ' Add the control to the global list of all controls
        allControls.Add(Slider)
    End Sub

    Private Sub CreateSwitch(ByRef itf As TIS.Imaging.VCDSwitchProperty, ByRef left As Integer, ByRef top As Integer, ByRef width As Integer, ByRef height As Integer, ByRef name As String)

        ' Create a Switch Control
        Dim swtch As New Switch

        swtch.Name = "switch" & allControls.Count()
        currentFrame.Controls.Add(swtch)

        swtch.SetBounds(left, top, width, height)

        ' Assign the absolute value interface to the control
        swtch.AssignItf(itf)

        ' Add the control to the current sistercontrols collection
        currentSisterControls.Add(swtch)

        ' Tell the control the sister controls group it belongs to
        swtch.setSisterControls(currentSisterControls)

        ' Add the control to the global list of all controls
        allControls.Add(swtch)
    End Sub

    Private Sub CreateButton(ByRef itf As TIS.Imaging.VCDButtonProperty, ByRef left As Integer, ByRef top As Integer, ByRef width As Integer, ByRef height As Integer, ByRef name As String)

        ' Create a PushButton control
        Dim btn As New PushButton
        btn.Name = "button" & allControls.Count
        currentFrame.Controls.Add(btn)

        btn.SetBounds(left, top, width, height)

        ' Assign the absolute value interface to the control
        btn.AssignItf(itf)

        ' Add the control to the current sistercontrols collection
        currentSisterControls.Add(btn)

        ' Tell the control the sister controls group it belongs to
        btn.setSisterControls(currentSisterControls)

        ' Add the control to the global list of all controls
        allControls.Add(btn)
    End Sub

    Private Sub CreateCombo(ByRef itf As TIS.Imaging.VCDMapStringsProperty, ByRef left As Integer, ByRef top As Integer, ByVal width As Integer, ByRef height As Integer)

        ' Create a StringCombo control
        Dim cbo As New StringCombo
        cbo.Name = "combo" & allControls.Count
        currentFrame.Controls.Add(cbo)

        cbo.SetBounds(left, top, width, height)

        ' Assign the absolute value interface to the control
        cbo.AssignItf(itf)

        ' Add the control to the current sistercontrols collection
        currentSisterControls.Add(cbo)
        ' Add the control to the current sistersliders collection
        currentSisterSliders.Add(cbo)

        ' Tell the control the sistersliders group it belongs to
        cbo.setSisterSliders(currentSisterSliders)

        ' Add the control to the global list of all controls
        allControls.Add(cbo)
    End Sub

    Private Sub InsertElement(ByRef elem As TIS.Imaging.VCDPropertyElement, ByRef x As Integer, ByRef y As Integer, ByRef txt As String)

        Dim AbsValItf As TIS.Imaging.VCDAbsoluteValueProperty
        Dim MapStringsItf As TIS.Imaging.VCDMapStringsProperty
        Dim RangeItf As TIS.Imaging.VCDRangeProperty
        Dim SwitchItf As TIS.Imaging.VCDSwitchProperty
        Dim buttonItf As TIS.Imaging.VCDButtonProperty

        ' Try to get all known interfaces. Some may be 'Nothing'
        AbsValItf = elem.FindInterface(TIS.Imaging.VCDIDs.VCDInterface_AbsoluteValue)
        MapStringsItf = elem.FindInterface(TIS.Imaging.VCDIDs.VCDInterface_MapStrings)
        RangeItf = elem.FindInterface(TIS.Imaging.VCDIDs.VCDInterface_Range)
        SwitchItf = elem.FindInterface(TIS.Imaging.VCDIDs.VCDInterface_Switch)
        buttonItf = elem.FindInterface(TIS.Imaging.VCDIDs.VCDInterface_Button)

        ' A label is only needed if the interface is AbsValItf, MapStringsItf or RangeItf,
        ' because they are represented by sliders and sliders don't show the name of a property
        Dim labelWidth As Integer
        If (Not (AbsValItf Is Nothing And MapStringsItf Is Nothing And RangeItf Is Nothing)) And (txt <> "") Then
            labelWidth = TextWidth(txt)
            If labelWidth < LABEL_WIDTH Then labelWidth = LABEL_WIDTH

            CreatePropertyLabel(txt, x, y + CTRL_HEIGHT / 4, labelWidth, CTRL_HEIGHT / 4 * 3)
            x = x + labelWidth
        End If

        Dim w As Integer

        ' If we were able to acquire an Absolute Value Interface, create an appropriate slider
        If Not AbsValItf Is Nothing Then

            CreateAbsValSlider(AbsValItf, x, y, SLIDER_WIDTH, CTRL_HEIGHT)
            x = x + SLIDER_WIDTH + CTRL_MARGIN

            ' If we were able to acquire an MapStrings Interface, create a combo box
        ElseIf Not MapStringsItf Is Nothing Then

            ' Calculate the needed with of the combo box
            ' based on the width of the entries
            Dim boxWidth As Integer = 0
            For Each s As String In MapStringsItf.Strings
                w = TextWidth(s)
                If w > boxWidth Then boxWidth = w
            Next

            ' Add some more space for the dropdown button
            boxWidth = boxWidth + COMBO_EXTRA_WIDTH

            CreateCombo(MapStringsItf, x, y, boxWidth, CTRL_HEIGHT)
            x = x + boxWidth + CTRL_MARGIN

            ' If we were able to acquire a range interface, create a range slider
        ElseIf Not RangeItf Is Nothing Then

            CreateRangeSlider(RangeItf, x, y, SLIDER_WIDTH, CTRL_HEIGHT)
            x = x + SLIDER_WIDTH + CTRL_MARGIN

            ' If we acquired a switch interface, create a switch checkbox
        ElseIf Not SwitchItf Is Nothing Then

            ' Determine the needed width of the switch control
            Dim switchWidth As Integer = TextWidth(elem.Name)
            switchWidth = switchWidth + CHECK_EXTRA_WIDTH

            CreateSwitch(SwitchItf, x, y, switchWidth, CTRL_HEIGHT, elem.Name)
            x = x + switchWidth + CTRL_MARGIN

            ' If we got a button interface, create a button control
        ElseIf Not buttonItf Is Nothing Then

            ' Determine the needed width of the button control
            Dim buttonWidth As Integer = TextWidth(elem.Name)
            buttonWidth = buttonWidth + BUTTON_EXTRA_WIDTH

            CreateButton(buttonItf, x, y, buttonWidth, CTRL_HEIGHT, elem.Name)
            x = x + buttonWidth + CTRL_MARGIN
        End If

    End Sub

    Private Sub InsertItem(ByRef item As TIS.Imaging.VCDPropertyItem, ByRef y As Integer)

        Dim x As Integer = 20

        Dim valueElem As TIS.Imaging.VCDPropertyElement
        Dim autoElem As TIS.Imaging.VCDPropertyElement
        Dim onepushElem As TIS.Imaging.VCDPropertyElement

        ' Try to find the 'default' elements (Value, Auto and One Push)
        valueElem = item.Elements.FindElement(TIS.Imaging.VCDIDs.VCDElement_Value)
        autoElem = item.Elements.FindElement(TIS.Imaging.VCDIDs.VCDElement_Auto)
        onepushElem = item.Elements.FindElement(TIS.Imaging.VCDIDs.VCDElement_OnePush)

        ' Hide the whitebalance value slider in case we have red and blue components available
        If item.ItemID = TIS.Imaging.VCDIDs.VCDID_WhiteBalance Then
            If Not item.Elements.FindElement(TIS.Imaging.VCDIDs.VCDElement_WhiteBalanceRed) Is Nothing Then
                valueElem = Nothing
            End If
        End If

        ' Create a label with appropriate size
        Dim labelWidth As Integer = TextWidth(item.Name)
        If labelWidth < LABEL_WIDTH Then labelWidth = LABEL_WIDTH

        CreatePropertyLabel((item.Name), x, y + CTRL_HEIGHT / 4, labelWidth, CTRL_HEIGHT / 4 * 3)
        x = x + labelWidth + CTRL_MARGIN

        ' If we found 'default' elements, create controls for them
        If Not valueElem Is Nothing Then InsertElement(valueElem, x, y, "")
        If Not autoElem Is Nothing Then InsertElement(autoElem, x, y, "")
        If Not onepushElem Is Nothing Then InsertElement(onepushElem, x, y, "")

        y = y + ROW_HEIGHT

        ' Find any non-default elements we did not create controls for yet
        For Each elem As TIS.Imaging.VCDPropertyElement In item.Elements
            Dim guid As String = elem.ElementID

            If guid <> TIS.Imaging.VCDIDs.VCDElement_Value And guid <> TIS.Imaging.VCDIDs.VCDElement_Auto And guid <> TIS.Imaging.VCDIDs.VCDElement_OnePush Then

                x = 25
                InsertElement(elem, x, y, (elem.Name))
                y = y + ROW_HEIGHT

            End If
        Next
    End Sub

    Private Sub InsertCategory(ByRef category As String, ByRef left As Integer, ByRef top As Integer, ByRef right As Integer, ByRef height As Integer)

        Dim y As Integer = 20

        ' Create a frame for the category
        CreateCategoryFrame(category, left, top, right - left)

        ' Create new containers for control groups
        currentSisterControls = New System.Collections.ArrayList
        currentSisterSliders = New System.Collections.ArrayList

        ' Iterate through the items in this category
        For Each itemID As String In IC.VCDPropertyItems.CategoryMap.ItemsInCategory(category)

            Dim item As TIS.Imaging.VCDPropertyItem = IC.VCDPropertyItems.FindItem(itemID)

            ' If we got a valid item, insert controls for it
            If Not item Is Nothing Then
                InsertItem(item, y)
            End If
        Next itemID

        ' Adjust the frame height
        currentFrame.Height = y + 7

        ' Return the vertical space the created frame occupies
        height = y + 14
    End Sub

    Private Sub OKButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OKButton.Click
        Me.Close()
    End Sub

    Private Sub UpdateButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles UpdateButton.Click
        UpdateButton.Enabled = False
        UpdateControls()
        UpdateButton.Enabled = True
    End Sub

    Private Sub UpdateControls()
        ' Update all controls
        IC.VCDPropertyItems.Update()
        For Each ctl As IControlBase In allControls
            ctl.UpdateControl()
        Next
    End Sub

    Private Function TextWidth(ByVal s As String)
        Dim g As System.Drawing.Graphics
        g = Me.CreateGraphics()
        TextWidth = g.MeasureString(s, Me.Font).Width + 7
        g.Dispose()
    End Function

    Private Sub UpdateTimer_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles UpdateTimer.Tick
        UpdateControls()
    End Sub

End Class