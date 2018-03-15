using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;


    public partial class StringCombo : UserControl, IControlBase
    {
        public StringCombo()
        {
            InitializeComponent();
        }

        // The interface this combo controls
        public TIS.Imaging.VCDMapStringsProperty MapStringsItf;

        // Flag to indicate that we are updating ourself, so that we have to ignore changes to the slider
        public bool updating;

        // Collection of sliders connected to interfaces of the same item
        // These sliders have to be updated when this combo is changed
        public System.Collections.ArrayList sisterSliders;


        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {

                // Only change the property if the click event was caused by the user
                if (!updating)
                {

                    // Assign the new string
                    if (!MapStringsItf.ReadOnly)
                    {
                        MapStringsItf.String = Combo.Text;
                    }

                    // If we know about possibly connected sliders, update them
                    if (!(sisterSliders == null))
                    {
                        foreach (IControlBase ctl in sisterSliders)
                        {
                            ctl.UpdateControl();
                        }
                    }

                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public void UpdateControl()
        {
            updating = true;

            // Check whether the property is available
            Combo.Enabled = MapStringsItf.Available;

            // Select the current string
            ScrollUpdate();

            updating = false;
        }

        private void InitialUpdate()
        {

            // Fill the combo box with the available strings
            Combo.Items.Clear();
            foreach (string s in MapStringsItf.Strings)
            {
                Combo.Items.Add(s);
            }

        }

        public void ScrollUpdate()
        {

            updating = true;

            // Calculate the new position
            Combo.SelectedIndex = MapStringsItf.Value - MapStringsItf.RangeMin;

            updating = false;

        }

        private void StringCombo_Resize(object eventSender, System.EventArgs eventArgs)
        {
            Combo.Width = Width;
        }

        public void AssignItf(TIS.Imaging.VCDMapStringsProperty itf)
        {
            MapStringsItf = itf;
            InitialUpdate();
            UpdateControl();
        }

        public void setSisterSliders(System.Collections.ArrayList sliders)
        {
            sisterSliders = sliders;
        }


    }
