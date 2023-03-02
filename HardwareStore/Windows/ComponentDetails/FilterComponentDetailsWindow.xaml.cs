using HardwareStore.Models;
using HardwareStore.Windows.Components;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace HardwareStore.Windows.ComponentDetails
{
    public struct ComponentDetailsFilter
    {
        public ComponentDetailsFilter()
        {
            Id = -1;
            DetailTypeId = -1;
            ComponentId = -1;

            Value = "";

            IsFiltered = false;
        }

        public int Id { get; set; }
        public int DetailTypeId { get; set; }
        public int ComponentId { get; set; }
        public string Value { get; set; }

        public bool IsFiltered { get; set; }
    }

    /// <summary>
    /// Логика взаимодействия для FilterComponentDetailsWindow.xaml
    /// </summary>
    public partial class FilterComponentDetailsWindow : Window
    {
        public ComponentDetailsFilter Filter;

        public FilterComponentDetailsWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (Filter.Id >= 1)
                idTextBox.Text = Filter.Id.ToString();

            if (Filter.DetailTypeId >= 1)
                detailTypeIdTextBox.Text = Filter.DetailTypeId.ToString();

            if (Filter.ComponentId >= 1)
                componentIdTextBox.Text = Filter.ComponentId.ToString();

            valueTextBox.Text = Filter.Value;
        }

        private void idTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void detailTypeIdTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void componentIdTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void filterButton_Click(object sender, RoutedEventArgs e)
        {
            ComponentDetailsFilter NewFilter = new()
            {
                Id = Utilities.TryParse(idTextBox.Text, -1),
                DetailTypeId = Utilities.TryParse(detailTypeIdTextBox.Text, -1),
                ComponentId = Utilities.TryParse(componentIdTextBox.Text, -1),
                Value = valueTextBox.Text,
                IsFiltered = true
            };

            Filter = NewFilter;

            DialogResult = true;
        }
    }
}
