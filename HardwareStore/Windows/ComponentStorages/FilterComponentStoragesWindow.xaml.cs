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

namespace HardwareStore.Windows.ComponentStorages
{
    public struct ComponentStoragesFilter
    {
        public ComponentStoragesFilter(StoreContext context)
        {
            Id = -1;
            WarehouseId = -1;
            ComponentId = -1;

            ComponentStorage? maxPrice = context.ComponentStorages.OrderByDescending(cs => cs.Price).FirstOrDefault();
            ComponentStorage? maxAmount = context.ComponentStorages.OrderByDescending(cs => cs.Amount).FirstOrDefault();

            Amount = (0, (maxAmount != null) ? maxAmount.Amount : 0);
            Price = (0, (maxPrice != null) ? maxPrice.Price : 0);

            IsFiltered = false;
        }

        public int Id { get; set; }
        public int WarehouseId { get; set; }
        public int ComponentId { get; set; }

        public (float Min, float Max) Price { get; set; }
        public (int Min, int Max) Amount { get; set; }

        public bool IsFiltered { get; set; }
    }


    /// <summary>
    /// Логика взаимодействия для FilterComponentStoragesWindow.xaml
    /// </summary>
    public partial class FilterComponentStoragesWindow : Window
    {
        public ComponentStoragesFilter Filter;

        public FilterComponentStoragesWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (Filter.Id >= 1)
                idTextBox.Text = Filter.Id.ToString();

            if (Filter.WarehouseId >= 1)
                warehouseIdTextBox.Text = Filter.WarehouseId.ToString();

            if (Filter.ComponentId >= 1)
                componentIdTextBox.Text = Filter.ComponentId.ToString();

            minPriceTextBox.Text = Filter.Price.Min.ToString();
            maxPriceTextBox.Text = Filter.Price.Max.ToString();

            minAmountTextBox.Text = Filter.Amount.Min.ToString();
            maxAmountTextBox.Text = Filter.Amount.Max.ToString();
        }

        private void idTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void warehouseIdTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void componentIdTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void minPriceTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedFloatRegex(), sender, e);
        }

        private void maxPriceTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedFloatRegex(), sender, e);
        }

        private void minAmountTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void maxAmountTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void filterButton_Click(object sender, RoutedEventArgs e)
        {
            ComponentStoragesFilter NewFilter = new()
            {
                Id = Utilities.TryParse(idTextBox.Text, -1),
                WarehouseId = Utilities.TryParse(warehouseIdTextBox.Text, -1),
                ComponentId = Utilities.TryParse(componentIdTextBox.Text, -1),
                Amount = (Utilities.TryParse(minAmountTextBox.Text, Filter.Amount.Min), Utilities.TryParse(maxAmountTextBox.Text, Filter.Amount.Max)),
                Price = (Utilities.TryParse(minPriceTextBox.Text, Filter.Price.Min), Utilities.TryParse(maxPriceTextBox.Text, Filter.Price.Max)),
                IsFiltered = true
            };

            Filter = NewFilter;

            DialogResult = true;
        }
    }
}
