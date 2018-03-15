using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace List_VCD_Properties
{
    public partial class Form1 : Form
    {

        public AbsValSlider AbsValCtrl;
        public StringCombo MapStringsCtrl;
        public PushButton ButtonCtrl;
        public Switch SwitchCtrl;
        public RangeSlider RangeCtrl;

        public Form1()
        {
            InitializeComponent();
        }

        private void btnSelectDevice_Click(object sender, EventArgs e)
        {
            // The device settings dialog needs the live mode to be stopped
            if (icImagingControl1.LiveVideoRunning)
            {
                icImagingControl1.LiveStop();
            }

            // Show the device settings dialog
            icImagingControl1.ShowDeviceSettingsDialog();

            // If no device was selected, exit
            if (!icImagingControl1.DeviceValid)
            {
                MessageBox.Show("No device was selected.");
                this.Close();
                return;
            }

            // Start live mode
            icImagingControl1.LiveStart();

            // (re-)initialize the tree view
            QueryVCDProperties();
        }

        private void btnShowPage_Click(object sender, EventArgs e)
        {
            if (icImagingControl1.DeviceValid)
            {
                // Show the built-in properties dialog
                icImagingControl1.ShowPropertyDialog();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            if (!icImagingControl1.DeviceValid)
            {
                // Show the device settings dialog.
                btnSelectDevice_Click(btnSelectDevice, new System.EventArgs());
            }

            if (icImagingControl1.DeviceValid)
            {
                ListAllPropertyItems();
                // Start live mode.
                icImagingControl1.LiveStart();

                // Query all properties of the video capture device and list
                // them in a tree control.
                QueryVCDProperties();
            }
        }

        private void QueryVCDPropertyItems(TreeNode pp, TIS.Imaging.VCDPropertyItems props)
        {
            // Iterate through all VCDPropertyItems and insert them into the tree
            foreach (TIS.Imaging.VCDPropertyItem item in props)
            {
                // Create a new tree node for the item
                TreeNode newNode = new TreeNode(item.Name, 0, 0);
                //				newNode.Tag = item.ItemID;
                newNode.Tag = null;
                pp.Nodes.Add(newNode);

                QueryVCDPropertyElements(newNode, item);
            }
        }
        private void QueryVCDPropertyElements(TreeNode pp, TIS.Imaging.VCDPropertyItem item)
        {
            TreeNode newNode = null;

            foreach (TIS.Imaging.VCDPropertyElement elem in item.Elements)
            {
                newNode = new TreeNode(elem.ElementID+": '" + elem.Name + "'", 1, 1);
                

                if ( elem.ElementID == TIS.Imaging.VCDIDs.VCDElement_Value )
                    newNode = new TreeNode("VCDElement_Value: '" + elem.Name + "'", 1, 1);
                else if ( elem.ElementID == TIS.Imaging.VCDIDs.VCDElement_Auto )
                    newNode = new TreeNode("VCDElement_Auto: '" + elem.Name + "'", 2, 2);       
                else if ( elem.ElementID == TIS.Imaging.VCDIDs.VCDElement_OnePush )
                    newNode = new TreeNode("VCDElement_OnePush: '" + elem.Name + "'", 3, 3);
                else if ( elem.ElementID == TIS.Imaging.VCDIDs.VCDElement_WhiteBalanceRed )
                    newNode = new TreeNode("VCDElement_WhiteBalanceRed: '" + elem.Name + "'", 4, 4);
                else if ( elem.ElementID == TIS.Imaging.VCDIDs.VCDElement_WhiteBalanceBlue )
                    newNode = new TreeNode("VCDElement_WhiteBalanceBlue: '" + elem.Name + "'", 4, 4);
                else
                    newNode = new TreeNode("Other Element ID: '" + elem.Name + "'", 4, 4);
                   
                newNode.Tag = null;
                pp.Nodes.Add(newNode);

                // Insert all interfaces
                QueryVCDPropertyInterface(newNode, elem);
            }
        }

        private void QueryVCDPropertyInterface(TreeNode pp, TIS.Imaging.VCDPropertyElement elem)
        {
            TreeNode newNode = null;

            foreach (TIS.Imaging.VCDPropertyInterface itf in elem)
            {
                newNode = new TreeNode(itf.InterfaceID, 4, 4);

                if ( itf.InterfaceID ==  TIS.Imaging.VCDIDs.VCDInterface_AbsoluteValue ) 
                    newNode = new TreeNode("AbsoluteValue", 4, 4);
                else if( itf.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_MapStrings )
                    newNode = new TreeNode("MapStrings", 6, 6);
                else if( itf.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_Range )
                    newNode = new TreeNode("Range", 4, 4);   
                else if( itf.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_Switch )
                    newNode = new TreeNode("Switch", 5, 5);          
                else if( itf.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_Button )
                    newNode = new TreeNode("Button", 3, 3);       

                // The Tag property holds the interface at the node.
                newNode.Tag = itf.Parent.Parent.ItemID + ":" + itf.Parent.ElementID + ":" + itf.InterfaceID;
                pp.Nodes.Add(newNode);
            }
        }

        private void QueryVCDProperties()
        {
            // Erase the complete tree.
            Tree.Nodes.Clear();

            // Fill the tree.
            TreeNode root = new TreeNode("VCDPropertyItems");
            Tree.Nodes.Add(root);

            QueryVCDPropertyItems(root, icImagingControl1.VCDPropertyItems);

            root.ExpandAll();
            Tree.SelectedNode = root;
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            // If the Tag property is empty, no leaf node was selected.
            if (Tree.SelectedNode.Tag == null)
            {
                return;
            }

            // Hide all control groups
            if (RangeCtrl != null) RangeCtrl.Dispose();
            if (SwitchCtrl != null) SwitchCtrl.Dispose();
            if (MapStringsCtrl != null) MapStringsCtrl.Dispose();
            if (ButtonCtrl != null) ButtonCtrl.Dispose();
            if (AbsValCtrl != null) AbsValCtrl.Dispose();

            string itfPath = Tree.SelectedNode.Tag.ToString();
            TIS.Imaging.VCDPropertyInterface itf = icImagingControl1.VCDPropertyItems.FindInterface(itfPath);

            if (itf != null)
            {
                itf.Update();
                // Show the control group matching the type of the selected interface
                // and initialize it.
                if ( itf.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_AbsoluteValue )
                     ShowAbsoluteValueControl(itf);
                else if( itf.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_MapStrings)
                    ShowComboBoxControl(itf);
                else if( itf.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_Range)
                    ShowRangeControl(itf);
                else if( itf.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_Switch)
                    ShowSwitchControl(itf);
                else if( itf.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_Button)
                    ShowButtonControl(itf);
            }
        }

        private void ShowAbsoluteValueControl(TIS.Imaging.VCDPropertyInterface itf)
        {
            TIS.Imaging.VCDAbsoluteValueProperty AbsValItf = (TIS.Imaging.VCDAbsoluteValueProperty)itf;
            AbsValCtrl = new AbsValSlider();
            CtrlFrame.Controls.Add(AbsValCtrl);
            AbsValCtrl.SetBounds(20, 20, 500, 27);
            AbsValCtrl.AssignItf(AbsValItf);
            CtrlFrame.Text = "Absolute Value";
        }
        private void ShowComboBoxControl(TIS.Imaging.VCDPropertyInterface itf)
        {
            TIS.Imaging.VCDMapStringsProperty MapStringsItf = (TIS.Imaging.VCDMapStringsProperty)itf;
            MapStringsCtrl = new StringCombo();
            CtrlFrame.Controls.Add(MapStringsCtrl);
            MapStringsCtrl.SetBounds(20, 20, 200, 27);
            MapStringsCtrl.AssignItf(MapStringsItf);
            CtrlFrame.Text = "MapStrings";
        }

        private void ShowRangeControl(TIS.Imaging.VCDPropertyInterface itf)
        {
            TIS.Imaging.VCDRangeProperty RangeItf = (TIS.Imaging.VCDRangeProperty)itf;
            RangeCtrl = new RangeSlider();
            CtrlFrame.Controls.Add(RangeCtrl);
            RangeCtrl.SetBounds(20, 20, 200, 27);
            RangeCtrl.AssignItf(RangeItf);
            CtrlFrame.Text = "Range";
        }

        private void ShowSwitchControl(TIS.Imaging.VCDPropertyInterface itf)
        {
            TIS.Imaging.VCDSwitchProperty SwitchItf = (TIS.Imaging.VCDSwitchProperty)itf;
            SwitchCtrl = new Switch();
            CtrlFrame.Controls.Add(SwitchCtrl);
            SwitchCtrl.SetBounds(20, 20, 200, 27);
            SwitchCtrl.AssignItf(SwitchItf);
            CtrlFrame.Text = "Switch";
        }

        private void ShowButtonControl(TIS.Imaging.VCDPropertyInterface itf)
        {
            TIS.Imaging.VCDButtonProperty buttonItf = (TIS.Imaging.VCDButtonProperty)itf;
            ButtonCtrl = new PushButton();
            CtrlFrame.Controls.Add(ButtonCtrl);
            ButtonCtrl.SetBounds(20, 20, 100, 27);
            ButtonCtrl.AssignItf(buttonItf);
            CtrlFrame.Text = "Button";
        }


        //
        // ListAllPropertyItems
        //
        // This sub builds an item - element - lists all names and values of the properties in the
        // debug window. It shows, how to enumerate all properties, elements and interfaces. The
        // interfaces have to be "casted" to the appropriate interface types like range, absolute
        // value etc. to get a correct access to the current interface's properties.
        //
        private void ListAllPropertyItems()
        {
            // Interface types for the different property interfaces.
            TIS.Imaging.VCDRangeProperty Range;
            TIS.Imaging.VCDSwitchProperty Switch;
            TIS.Imaging.VCDAbsoluteValueProperty AbsoluteValue;
            TIS.Imaging.VCDMapStringsProperty MapString;
            TIS.Imaging.VCDButtonProperty Button;

            // Get all property items
            foreach (TIS.Imaging.VCDPropertyItem PropertyItem in icImagingControl1.VCDPropertyItems)
            {
                System.Diagnostics.Debug.WriteLine(PropertyItem.Name);

                // Get all property elements of the current property item.
                foreach (TIS.Imaging.VCDPropertyElement PropertyElement in PropertyItem.Elements)
                {
                    System.Diagnostics.Debug.WriteLine("    Element : " + PropertyElement.Name);

                    // Get all interfaces of the current property element.
                    foreach (TIS.Imaging.VCDPropertyInterface PropertyInterFace in PropertyElement)
                    {
                        System.Diagnostics.Debug.Write("        Interface ");

                        try
                        {

                            // Cast the current interface into the appropriate type to access
                            // the special interface properties.

                            if (PropertyInterFace.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_AbsoluteValue)
                            {
                                AbsoluteValue = (TIS.Imaging.VCDAbsoluteValueProperty)PropertyInterFace;
                                System.Diagnostics.Debug.Write("Absolut Value : ");
                                System.Diagnostics.Debug.WriteLine(AbsoluteValue.Value.ToString());
                            }    
                            else if ( PropertyInterFace.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_MapStrings )
                            {
                                    MapString = (TIS.Imaging.VCDMapStringsProperty)PropertyInterFace;
                                    System.Diagnostics.Debug.Write("Mapstring : ");
                                    System.Diagnostics.Debug.WriteLine(MapString.String);
                            }
                             else if ( PropertyInterFace.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_Switch )
                            {
                                    Switch = (TIS.Imaging.VCDSwitchProperty)PropertyInterFace;
                                    System.Diagnostics.Debug.Write("Switch : ");
                                    System.Diagnostics.Debug.WriteLine(Switch.Switch.ToString());
                             }
                             else if (PropertyInterFace.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_Button)
                             {
                                 Button = (TIS.Imaging.VCDButtonProperty)PropertyInterFace;
                                 System.Diagnostics.Debug.WriteLine("Button");
                             }
                             else if (PropertyInterFace.InterfaceID == TIS.Imaging.VCDIDs.VCDInterface_Range)
                             {
                                 Range = (TIS.Imaging.VCDRangeProperty)PropertyInterFace;
                                 System.Diagnostics.Debug.Write("Range : ");
                                 System.Diagnostics.Debug.WriteLine(Range.Value.ToString());
                             }
                            
                        }
                        catch (Exception ex)
                        {
                            System.Diagnostics.Debug.WriteLine("<error>");
                        }
                    }
                }
            }
        }

    }
}