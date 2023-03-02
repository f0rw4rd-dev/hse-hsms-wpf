using HardwareStore.Windows.OrderComponents;
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

namespace HardwareStore.Windows.Components
{
    public struct ComponentsFilter
    {
        public ComponentsFilter(StoreContext context)
        {
            Id = -1;
            ComponentTypeId = -1;

            Name = "";

            Component? maxWarranty = context.Components.OrderByDescending(c => c.Warranty).FirstOrDefault();

            Warranty = (0, (maxWarranty != null) ? maxWarranty.Warranty : 0);

            IsFiltered = false;
        }

        public int Id { get; set; }
        public string Name { get; set; }
        public int ComponentTypeId { get; set; }

        public (int Min, int Max) Warranty { get; set; }

        public bool IsFiltered { get; set; }
    }

    /// <summary>
    /// Логика взаимодействия для FilterComponentsWindow.xaml
    /// </summary>
    public partial class FilterComponentsWindow : Window
    {
        public ComponentsFilter Filter;

        public FilterComponentsWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            if (Filter.Id >= 1)
                idTextBox.Text = Filter.Id.ToString();

            minWarrantyTextBox.Text = Filter.Warranty.Min.ToString();
            maxWarrantyTextBox.Text = Filter.Warranty.Max.ToString();

            nameTextBox.Text = Filter.Name;

            StoreContext context = new();

            foreach (ComponentType componentType in context.ComponentTypes.ToList())
            {
                ComboBoxItem componentTypeComboBoxItem = new()
                {
                    Tag = componentType.Id.ToString(),
                    Content = componentType.Name
                };

                componentTypeComboBox.Items.Add(componentTypeComboBoxItem);
            }

            for (int i = 0; i < componentTypeComboBox.Items.Count; i++)
            {
                if (componentTypeComboBox.Items[i] is ComboBoxItem comboBoxItem && comboBoxItem.Tag.ToString() == Filter.ComponentTypeId.ToString())
                {
                    componentTypeComboBox.SelectedIndex = i;
                    break;
                }
            }
        }

        private void idTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void nameTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            //Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void minWarrantyTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void maxWarrantyTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);
        }

        private void filterButton_Click(object sender, RoutedEventArgs e)
        {
            ComponentsFilter NewFilter = new()
            {
                Warranty = (Utilities.TryParse(minWarrantyTextBox.Text, Filter.Warranty.Min), Utilities.TryParse(maxWarrantyTextBox.Text, Filter.Warranty.Max)),
                Id = Utilities.TryParse(idTextBox.Text, -1),
                ComponentTypeId = int.Parse((string)((ComboBoxItem)componentTypeComboBox.SelectedItem).Tag),
                Name = nameTextBox.Text,
                IsFiltered = true
            };

            Filter = NewFilter;

            DialogResult = true;
        }
    }
}
