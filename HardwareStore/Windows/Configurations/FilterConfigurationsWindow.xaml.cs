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
using HardwareStore.Models;

namespace HardwareStore.Windows.Configurations
{
    public struct ConfigurationsFilter
    {
        public ConfigurationsFilter(StoreContext context)
        {
            Id = -1;
            ConfigurationId = -1;
            ComponentId = -1;

            Configuration? maxAmount = context.Configurations.OrderByDescending(c => c.Amount).FirstOrDefault();

            MinAmount = 0;
            MaxAmount = (maxAmount != null) ? maxAmount.Amount : 0;

            IsFiltered = false;
        }

        public int Id { get; set; }
        public int ConfigurationId { get; set; }
        public int ComponentId { get; set; }
        public int MinAmount { get; set; }
        public int MaxAmount { get; set; }

        public bool IsFiltered { get; set; }
    }

    /// <summary>
    /// Логика взаимодействия для FilterConfigurationsWindow.xaml
    /// </summary>
    public partial class FilterConfigurationsWindow : Window
    {
        public ConfigurationsFilter Filter;

        public FilterConfigurationsWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (Filter.Id >= 1)
                idTextBox.Text = Filter.Id.ToString();

            if (Filter.ComponentId >= 1)
                componentIdTextBox.Text = Filter.ComponentId.ToString();

            if (Filter.ConfigurationId >= 1)
                configurationIdTextBox.Text = Filter.ConfigurationId.ToString();

            minAmountTextBox.Text = Filter.MinAmount.ToString();
            maxAmountTextBox.Text = Filter.MaxAmount.ToString();
        }

        private void idTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void configurationIdTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void componentIdTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
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
            ConfigurationsFilter NewFilter = new()
            {
                MinAmount = Utilities.TryParse(minAmountTextBox.Text, Filter.MinAmount),
                MaxAmount = Utilities.TryParse(maxAmountTextBox.Text, Filter.MaxAmount),
                Id = Utilities.TryParse(idTextBox.Text, -1),
                ConfigurationId = Utilities.TryParse(configurationIdTextBox.Text, -1),
                ComponentId = Utilities.TryParse(componentIdTextBox.Text, -1),
                IsFiltered = true
            };

            Filter = NewFilter;

            DialogResult = true;
        }
    }
}
