using HardwareStore.Models;
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
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace HardwareStore.Windows.Supplies
{
    public struct SuppliesFilter
    {
        public SuppliesFilter(StoreContext context)
        {
            Id = -1;
            SupplierId = -1;
            ComponentId = -1;
            WarehouseId = -1;

            Supply? maxSupplyPrice = context.Supplies.OrderByDescending(s => s.SupplyPrice).FirstOrDefault();
            Supply? maxAmount = context.Supplies.OrderByDescending(s => s.Amount).FirstOrDefault();

            SupplyPrice = (0, (maxSupplyPrice != null) ? maxSupplyPrice.SupplyPrice : 0);
            Amount = (0, (maxAmount != null) ? maxAmount.Amount : 0);

            Date = -1;

            IsFiltered = false;
        }

        public int Id { get; set; }
        public int SupplierId { get; set; }
        public int ComponentId { get; set; }
        public int WarehouseId { get; set; }

        public (float Min, float Max) SupplyPrice { get; set; }
        public (int Min, int Max) Amount { get; set; }

        public long Date { get; set; }
        public bool IsFiltered { get; set; }
    }

    /// <summary>
    /// Логика взаимодействия для FilterSuppliesWindow.xaml
    /// </summary>
    public partial class FilterSuppliesWindow : Window
    {
        public SuppliesFilter Filter;

        public FilterSuppliesWindow()
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

            if (Filter.SupplierId >= 1)
                supplierIdTextBox.Text = Filter.SupplierId.ToString();

            if (Filter.Date >= 0)
                supplyDatePicker.SelectedDate = Utilities.UnixTimeStampToDateTime(Filter.Date);

            minSupplyPriceTextBox.Text = Filter.SupplyPrice.Min.ToString();
            maxSupplyPriceTextBox.Text = Filter.SupplyPrice.Max.ToString();

            minAmountTextBox.Text = Filter.Amount.Min.ToString();
            maxAmountTextBox.Text = Filter.Amount.Max.ToString();
        }

        private void idTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void supplierIdTextBox_TextChanged(object sender, TextChangedEventArgs e)
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

        private void minSupplyPriceTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedFloatRegex(), sender, e);
        }

        private void maxSupplyPriceTextBox_TextChanged(object sender, TextChangedEventArgs e)
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
            SuppliesFilter NewFilter = new()
            {
                SupplyPrice = (Utilities.TryParse(minSupplyPriceTextBox.Text, Filter.SupplyPrice.Min), Utilities.TryParse(maxSupplyPriceTextBox.Text, Filter.SupplyPrice.Max)),
                Amount = (Utilities.TryParse(minAmountTextBox.Text, Filter.Amount.Min), Utilities.TryParse(maxAmountTextBox.Text, Filter.Amount.Max)),
                Id = Utilities.TryParse(idTextBox.Text, -1),
                WarehouseId = Utilities.TryParse(warehouseIdTextBox.Text, -1),
                ComponentId = Utilities.TryParse(componentIdTextBox.Text, -1),
                SupplierId = Utilities.TryParse(supplierIdTextBox.Text, -1),
                IsFiltered = true
            };

            if (supplyDatePicker.SelectedDate != null)
            {
                DateTime selectedDateTime = (DateTime)supplyDatePicker.SelectedDate;
                NewFilter.Date = Utilities.DateTimeToUnixTimeStamp(new DateTime(selectedDateTime.Year, selectedDateTime.Month, selectedDateTime.Day));
            }
            else
            {
                NewFilter.Date = -1;
            }

            Filter = NewFilter;

            DialogResult = true;
        }
    }
}
