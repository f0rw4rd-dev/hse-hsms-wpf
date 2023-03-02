using HardwareStore.Windows.Supplies;
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

namespace HardwareStore.Windows.Warehouses
{
    public struct WarehousesFilter
    {
        public WarehousesFilter()
        {
            Id = -1;
            Zip = -1;

            City = "";
            Street = "";
            House = "";

            IsFiltered = false;
        }

        public int Id { get; set; }
        public string City { get; set; }
        public string Street { get; set; }
        public string House { get; set; }
        public int Zip { get; set; }
        public bool IsFiltered { get; set; }
    }

    /// <summary>
    /// Логика взаимодействия для FilterWarehousesWindow.xaml
    /// </summary>
    public partial class FilterWarehousesWindow : Window
    {
        public WarehousesFilter Filter { get; set; }

        public FilterWarehousesWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (Filter.Id >= 1)
                idTextBox.Text = Filter.Id.ToString();

            if (Filter.Zip >= 0)
                zipTextBox.Text = Filter.Zip.ToString();

            cityTextBox.Text = Filter.City.ToString();
            streetTextBox.Text = Filter.Street.ToString();
            houseTextBox.Text = Filter.House.ToString();
        }

        private void idTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void cityTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void streetTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void houseTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void zipTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void filterButton_Click(object sender, RoutedEventArgs e)
        {
            WarehousesFilter NewFilter = new()
            {
                Id = Utilities.TryParse(idTextBox.Text, -1),
                City = cityTextBox.Text,
                Street = streetTextBox.Text,
                House = houseTextBox.Text,
                Zip = Utilities.TryParse(zipTextBox.Text, -1),
                IsFiltered = true
            };

            Filter = NewFilter;

            DialogResult = true;
        }
    }
}
