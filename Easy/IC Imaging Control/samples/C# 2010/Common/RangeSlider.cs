using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;


    public partial class RangeSlider : UserControl, IControlBase, IControlSlider
    {
        public RangeSlider()
        {
            InitializeComponent();
        }

        // The interface this slider controls
        public TIS.Imaging.VCDRangeProperty RangeItf;

        // Collection of sliders connected to interfaces of the same item
        // These sliders have to be updated when this slider is changed
        public System.Collections.ArrayList sisterSliders;

        private void Slider_Scroll(object sender, EventArgs e)
        {
            try
            {
                // Assign the new value to the property
                if (!RangeItf.ReadOnly)
                {
                    RangeItf.Value = Slider.Value * RangeItf.Delta;
                }

                // Update the text box
                ValueText.Text = RangeItf.Value.ToString();

                // If we know about possibly connected sliders, update them
                if (!(sisterSliders == null))
                {
                    foreach (IControlSlider sld in sisterSliders)
                    {
                        if (!(sld == this))
                        {
                            sld.ScrollUpdate();
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

            // Check whether the property is available
            if (RangeItf.Available)
            {

                // Enable slider and textbox
                Slider.Enabled = true;
                ValueText.Enabled = true;

                // Update slider position
                ScrollUpdate();
            }
            else
            {
                // Disable slider
                Slider.Enabled = false;

                // Disable text
                ValueText.Text = "";
                ValueText.Enabled = false;
            }

        }

        private void InitialUpdate()
        {

            int min = 0;
            int max = 0;

            // Initialize the slider range
            min = RangeItf.RangeMin / RangeItf.Delta;
            max = RangeItf.RangeMax / RangeItf.Delta;

            Slider.TickFrequency = 1;
            if (max - min > 50)
            {
                Slider.TickFrequency = 10;
            }
            if (max - min > 500)
            {
                Slider.TickFrequency = 100;
            }

            Slider.Minimum = min;
            Slider.Maximum = max;

            if (min == max)
            {
                Slider.Enabled = false;
            }

        }

        public void ScrollUpdate()
        {

            if (!RangeItf.Available) return;

            // Calculate the new slider position
            int pos = 0;
            pos = RangeItf.Value / RangeItf.Delta;

            if (pos < Slider.Minimum | pos > Slider.Maximum)
            {
                Slider.Enabled = false;
            }

            Slider.Value = pos;
            ValueText.Text = pos.ToString();
        }

        public void AssignItf(TIS.Imaging.VCDRangeProperty itf)
        {
            RangeItf = itf;
            InitialUpdate();
            UpdateControl();
        }

        public void setSisterSliders(System.Collections.ArrayList sliders)
        {
            sisterSliders = sliders;
        }

        private void RangeSlider_Layout(object sender, System.Windows.Forms.LayoutEventArgs e)
        {
            // Adjust the slider and textbox position
            Slider.Width = Width * 80 / 100;
            Slider.Height = Height;
            ValueText.Height = Height;
            ValueText.Left = Width * 80 / 100;
            ValueText.Width = Width * 20 / 100;
        }

    }

