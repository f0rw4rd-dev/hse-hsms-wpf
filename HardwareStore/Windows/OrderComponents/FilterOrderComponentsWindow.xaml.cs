using HardwareStore.Models;
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

namespace HardwareStore.Windows.OrderComponents
{
    public struct OrderComponentsFilter
    {
        public OrderComponentsFilter(StoreContext context)
        {
            Id = -1;
            OrderId = -1;
            ComponentId = -1;
            WarehouseId = -1;

            OrderComponent? maxPrice = context.OrderComponents.OrderByDescending(s => s.Price).FirstOrDefault();
            OrderComponent? maxAmount = context.OrderComponents.OrderByDescending(s => s.Amount).FirstOrDefault();

            Price = (0, (maxPrice != null) ? maxPrice.Price : 0);
            Amount = (0, (maxAmount != null) ? maxAmount.Amount : 0);

            IsPartOfConfiguration = false;

            IsFiltered = false;
        }

        public int Id { get; set; }
        public int OrderId { get; set; }
        public int ComponentId { get; set; }
        public int WarehouseId { get; set; }

        public (float Min, float Max) Price { get; set; }
        public (int Min, int Max) Amount { get; set; }

        public bool IsPartOfConfiguration { get; set; }

        public bool IsFiltered { get; set; }
    }

    /// <summary>
    /// Логика взаимодействия для FilterOrderComponentsWindow.xaml
    /// </summary>
    public partial class FilterOrderComponentsWindow : Window
    {
        public OrderComponentsFilter Filter;

        public FilterOrderComponentsWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (Filter.Id >= 1)
                idTextBox.Text = Filter.Id.ToString();

            if (Filter.ComponentId >= 1)
                componentIdTextBox.Text = Filter.ComponentId.ToString();

            if (Filter.WarehouseId >= 1)
                warehouseIdTextBox.Text = Filter.WarehouseId.ToString();

            if (Filter.OrderId >= 1)
                orderIdTextBox.Text = Filter.OrderId.ToString();

            minPriceTextBox.Text = Filter.Price.Min.ToString();
            maxPriceTextBox.Text = Filter.Price.Max.ToString();

            minAmountTextBox.Text = Filter.Amount.Min.ToString();
            maxAmountTextBox.Text = Filter.Amount.Max.ToString();
        }

        private void idTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void orderIdTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void componentIdTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void warehouseIdTextBox_TextChanged(object sender, TextChangedEventArgs e)
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
            OrderComponentsFilter NewFilter = new()
            {
                Price = (Utilities.TryParse(minPriceTextBox.Text, Filter.Price.Min), Utilities.TryParse(maxPriceTextBox.Text, Filter.Price.Max)),
                Amount = (Utilities.TryParse(minAmountTextBox.Text, Filter.Amount.Min), Utilities.TryParse(maxAmountTextBox.Text, Filter.Amount.Max)),
                Id = Utilities.TryParse(idTextBox.Text, -1),
                WarehouseId = Utilities.TryParse(warehouseIdTextBox.Text, -1),
                ComponentId = Utilities.TryParse(componentIdTextBox.Text, -1),
                OrderId = Utilities.TryParse(orderIdTextBox.Text, -1),
                IsFiltered = true
            };

            Filter = NewFilter;

            DialogResult = true;
        }
    }
}
