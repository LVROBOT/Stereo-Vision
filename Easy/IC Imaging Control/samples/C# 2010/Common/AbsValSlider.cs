using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

    public partial class AbsValSlider : UserControl , IControlBase, IControlSlider
    {
        public AbsValSlider()
        {
            InitializeComponent();
        }

        // The interface this slider controls
        public TIS.Imaging.VCDAbsoluteValueProperty AbsValItf;

        // Flag to indicate that we are updating ourself, so that we have to ignore changes to the slider
        public bool updating;

        // Flag to indicate that this control was changed by the user, so that we do not have to update it
        public bool selfClicked;

        // Collection of sliders connected to interfaces of the same item
        // These sliders have to be updated when this slider is changed
        public System.Collections.ArrayList sisterSliders;


        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            try
            {

                // Only change the property if the scroll event was caused by the user
                if (!updating)
                {

                    // Get the new absolute value depending on the slider position
                    // and set the new value to the interface
                    if (!AbsValItf.ReadOnly)
                    {
                        AbsValItf.Value = GetAbsVal();
                    }

                    // Read the new value back from the absolute value interface
                    // This has to be done because we do not know the granularity of the absolute values
                    // and the value that has really been set normally differs from the value we
                    // assigned to the property
                    ScrollUpdate();

                    // If we know about possibly connected sliders, update them
                    selfClicked = true;
                    if (!(sisterSliders == null))
                    {
                        foreach (IControlSlider sld in sisterSliders)
                        {
                            sld.ScrollUpdate();
                        }
                    }
                    selfClicked = false;

                }

            }
            catch (Exception ex)
            {

                MessageBox.Show(ex.Message);

            }
        }

        private void AbsValSlider_Load(object sender, EventArgs e)
        {
            updating = false;
            selfClicked = false;
        }

        // This function calculates the needed position of the slider based on the current absolute value
        private int GetSliderPos()
        {
            double rmin = 0;
            double rmax = 0;
            double absval = 0;
            double rangelen = 0;
            double p = 0;

            // Get the property data from the interface
            rmin = AbsValItf.RangeMin;
            rmax = AbsValItf.RangeMax;
            absval = AbsValItf.Value;

            // Do calculation depending of the dimension function of the property
            if (AbsValItf.DimFunction == TIS.Imaging.AbsDimFunction.eAbsDimFunc_Log)
            {

                rangelen = System.Math.Log(rmax) - System.Math.Log(rmin);
                p = 100 / rangelen * (System.Math.Log(absval) - System.Math.Log(rmin));
            }
            else // AbsValItf.DimFunction = AbsDimFunction.eAbsDimFunc_Linear
            {
                rangelen = rmax - rmin;
                p = 100 / rangelen * (absval - rmin);
            }

            // Round to integer
            return (int)System.Math.Round(p, 0);
        }

        // This function calculates the current absolute value based on the position of the slider
        private double GetAbsVal()
        {

            double rmin = 0;
            double rmax = 0;
            double rangelen = 0;
            double value = 0;

            // Get the property data from the interface
            rmin = AbsValItf.RangeMin;
            rmax = AbsValItf.RangeMax;

            // Do calculation depending of the dimension function of the property
            if (AbsValItf.DimFunction == TIS.Imaging.AbsDimFunction.eAbsDimFunc_Log)
            {

                rangelen = System.Math.Log(rmax) - System.Math.Log(rmin);
                value = System.Math.Exp(System.Math.Log(rmin) + rangelen / 100 * Slider.Value);

            }
            else // AbsValItf.DimFunction = AbsDimFunction.eAbsDimFunc_Linear
            {

                rangelen = rmax - rmin;
                value = rmin + rangelen / 100 * Slider.Value;

            }

            // Correct the value if it is out of bounds
            if (value > rmax)
            {
                value = rmax;
            }
            if (value < rmin)
            {
                value = rmin;
            }

            return value;

        }

        public void UpdateControl()
        {

            updating = true;

            // Check whether the property is available
            if (AbsValItf.Available)
            {

                // Enable the slider
                Slider.Enabled = true;

                ScrollUpdate();
            }
            else
            {
                // Disable the slider
                Slider.Enabled = false;

                // Disable the text box
                ValueText.Text = "";
                ValueText.Enabled = false;
            }

            updating = false;
        }

        private void InitialUpdate()
        {

            Slider.Minimum = 0;
            Slider.Maximum = 100;

        }

        public void ScrollUpdate()
        {

            // Do not update if this event was caused by this control
            if (selfClicked)
            {
                return;
            }

            // Do not update if the property is not avilable
            if (!AbsValItf.Available)
            {
                return;
            }

            updating = true;

            // Assign a text representation of the current value to the text box
            ValueText.Text = AbsValItf.Value.ToString();
            if (!ValueText.Enabled)
            {
                ValueText.Enabled = true;
            }

            // Set the slider position
            Slider.Value = GetSliderPos();

            updating = false;
        }

        public void AssignItf(TIS.Imaging.VCDAbsoluteValueProperty itf)
        {

            AbsValItf = itf;

            // Setup the control to match the interface
            InitialUpdate();

            // Read the initial values
            UpdateControl();
        }

        public void setSisterSliders(System.Collections.ArrayList sliders)
        {
            sisterSliders = sliders;
        }

        private void AbsValSlider_Layout(object sender, System.Windows.Forms.LayoutEventArgs e)
        {
            if (AbsValItf == null)
            {
                return;
            }

            // Determine the length of the describing text at some points to estimate
            // a good width for the edit box
            int lenmin = 0;
            int lenmid = 0;
            int lenmax = 0;

            System.Drawing.Graphics g = this.CreateGraphics();

            lenmin = (int)g.MeasureString(AbsValItf.RangeMin.ToString(), this.Font).Width;
            double valmid = AbsValItf.RangeMax - AbsValItf.RangeMin / 2;
            lenmid = (int)g.MeasureString(valmid.ToString(), this.Font).Width;
            lenmax = (int)g.MeasureString(AbsValItf.RangeMax.ToString(), this.Font).Width;

            g.Dispose();

            int textlen = 0;
            textlen = lenmin;
            if (lenmid > textlen)
            {
                textlen = lenmid;
            }
            if (lenmax > textlen)
            {
                textlen = lenmax;
            }

            // Resize the slider and the edit box
            Slider.Width = Width - (textlen + 20);
            Slider.Height = Height;
            ValueText.Height = Height;
            ValueText.Left = Width - (textlen + 20);
            ValueText.Width = textlen + 20;
        }
    }

