using HardwareStore.Models;
using HardwareStore.Windows.Supplies;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.ComponentModel;
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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace HardwareStore.Windows.Configurations
{
    /// <summary>
    /// Логика взаимодействия для ConfigurationsUserControl.xaml
    /// </summary>
    public partial class ConfigurationsUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource configurationsViewSource;

        private ConfigurationsFilter Filter { get; set; }

        public ConfigurationsUserControl()
        {
            InitializeComponent();
            configurationsViewSource = (CollectionViewSource)FindResource(nameof(configurationsViewSource));
            Filter = new(_context);
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.Configurations.Load();

            configurationsViewSource.GroupDescriptions.Clear();
            configurationsViewSource.GroupDescriptions.Add(new PropertyGroupDescription("ConfigurationId"));
            configurationsViewSource.Source = _context.Configurations.Local.ToObservableCollection();

            configurationsDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].Configurations.CanAdd;
            configurationsDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].Configurations.CanDelete;
            configurationsDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].Configurations.CanEdit;
        }

        private void updateConfigurations_Click(object sender, RoutedEventArgs e)
        {
            Filter = new(_context);

            _context = new StoreContext();
            _context.Configurations.Load();

            configurationsViewSource.GroupDescriptions.Clear();
            configurationsViewSource.GroupDescriptions.Add(new PropertyGroupDescription("ConfigurationId"));
            configurationsViewSource.Source = _context.Configurations.Local.ToObservableCollection();
        }

        private void saveConfigurations_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, configurationsDataGrid);
        }

        private void filterConfigurations_Click(object sender, RoutedEventArgs e)
        {
            FilterConfigurationsWindow filterConfigurationsWindow = new()
            {
                Filter = Filter
            };

            if (filterConfigurationsWindow.ShowDialog() == true)
            {
                Filter = filterConfigurationsWindow.Filter;
                CollectionViewSource.GetDefaultView(configurationsDataGrid.ItemsSource).Refresh();
            }
        }

        private void CollectionViewSource_Filter(object sender, FilterEventArgs e)
        {
            if (e.Item is Configuration configuration)
            {
                bool IsAmountInRange = Filter.MinAmount <= configuration.Amount && configuration.Amount <= Filter.MaxAmount;

                if (!Filter.IsFiltered)
                {
                    e.Accepted = true;
                    return;
                }

                e.Accepted = IsAmountInRange
                    && (Filter.Id == -1 || Filter.Id == configuration.Id)
                    && (Filter.ComponentId == -1 || Filter.ComponentId == configuration.ComponentId)
                    && (Filter.ConfigurationId == -1 || Filter.ConfigurationId == configuration.ConfigurationId);
            }
        }

        private void exportConfigurations_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "ИД конфигурации", "ИД комплектующего", "Количество" } };
            List<object[]> cellData = new() { };

            foreach (Configuration? configuration in _context.Configurations.ToList())
            {
                if (configuration == null)
                    continue;

                cellData.Add(new object[] { configuration.Id, configuration.ConfigurationId, configuration.ComponentId, configuration.Amount });
            }

            Utilities.ExportToExcel("Конфигурации", headerRow, cellData);
        }
    }
}
