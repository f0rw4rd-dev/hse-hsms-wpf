using HardwareStore.Models;
using HardwareStore.Windows.ComponentStorages;
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

namespace HardwareStore.Windows.Orders
{
    public struct OrdersFilter
    {
        public OrdersFilter()
        {
            Id = -1;
            Status = -1;
            Date = -1;

            IsFiltered = false;
        }

        public int Id { get; set; }
        public int Status { get; set; }
        public long Date { get; set; }

        public bool IsFiltered { get; set; }
    }

    /// <summary>
    /// Логика взаимодействия для FilterOrdersWindow.xaml
    /// </summary>
    public partial class FilterOrdersWindow : Window
    {
        public OrdersFilter Filter;

        public FilterOrdersWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (Filter.Id >= 1)
                idTextBox.Text = Filter.Id.ToString();

            if (Filter.Date >= 0)
                datePicker.SelectedDate = Utilities.UnixTimeStampToDateTime(Filter.Date);

            for (int i = 0; i < statusComboBox.Items.Count; i++)
            {
                ComboBoxItem? comboBoxItem = statusComboBox.Items[i] as ComboBoxItem;

                if (comboBoxItem != null && comboBoxItem.Tag.ToString() == Filter.Status.ToString())
                {
                    statusComboBox.SelectedIndex = i;
                    break;
                }
            }
        }

        private void idTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void filterButton_Click(object sender, RoutedEventArgs e)
        {
            OrdersFilter NewFilter = new()
            {
                Id = Utilities.TryParse(idTextBox.Text, -1),
                Status = int.Parse((string)((ComboBoxItem)statusComboBox.SelectedItem).Tag),
                IsFiltered = true
            };

            if (datePicker.SelectedDate != null)
            {
                DateTime selectedDateTime = (DateTime)datePicker.SelectedDate;
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
