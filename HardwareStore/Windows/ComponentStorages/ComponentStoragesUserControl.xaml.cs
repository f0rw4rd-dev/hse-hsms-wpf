using Microsoft.EntityFrameworkCore;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using HardwareStore.Models;
using HardwareStore.Windows.Components;
using System.ComponentModel;

namespace HardwareStore.Windows.ComponentStorages
{
    /// <summary>
    /// Логика взаимодействия для ComponentStoragesUserControl.xaml
    /// </summary>
    public partial class ComponentStoragesUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource componentStoragesViewSource;

        private ComponentStoragesFilter Filter { get; set; }

        public ComponentStoragesUserControl()
        {
            InitializeComponent();
            componentStoragesViewSource = (CollectionViewSource)FindResource(nameof(componentStoragesViewSource));
            Filter = new(_context);
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.ComponentStorages.Load();
            componentStoragesViewSource.Source = _context.ComponentStorages.Local.ToObservableCollection();

            componentStoragesDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].ComponentStorages.CanAdd;
            componentStoragesDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].ComponentStorages.CanDelete;
            componentStoragesDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].ComponentStorages.CanEdit;
        }

        private void updateComponentStorages_Click(object sender, RoutedEventArgs e)
        {
            Filter = new(_context);

            _context = new StoreContext();
            _context.ComponentStorages.Load();
            componentStoragesViewSource.Source = _context.ComponentStorages.Local.ToObservableCollection();
        }

        private void saveComponentStorages_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, componentStoragesDataGrid);
        }

        private void filterComponentStorages_Click(object sender, RoutedEventArgs e)
        {
            FilterComponentStoragesWindow filterComponentStoragesWindow = new()
            {
                Filter = Filter
            };

            if (filterComponentStoragesWindow.ShowDialog() == true)
            {
                Filter = filterComponentStoragesWindow.Filter;
                CollectionViewSource.GetDefaultView(componentStoragesDataGrid.ItemsSource).Refresh();
            }
        }

        private void CollectionViewSource_Filter(object sender, FilterEventArgs e)
        {
            if (e.Item is ComponentStorage componentStorage)
            {
                bool IsAmountInRange = Filter.Amount.Min <= componentStorage.Amount && componentStorage.Amount <= Filter.Amount.Max,
                    IsPriceInRange = Filter.Price.Min <= componentStorage.Price && componentStorage.Price <= Filter.Price.Max;

                if (!Filter.IsFiltered)
                {
                    e.Accepted = true;
                    return;
                }

                e.Accepted = IsAmountInRange && IsPriceInRange
                    && (Filter.Id == -1 || Filter.Id == componentStorage.Id)
                    && (Filter.ComponentId == -1 || Filter.ComponentId == componentStorage.ComponentId)
                    && (Filter.WarehouseId == -1 || Filter.WarehouseId == componentStorage.WarehouseId);
            }
        }

        private void exportComponentStorages_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "ИД склада", "ИД комплектующего", "Цена (руб)", "Количество (шт)" } };
            List<object[]> cellData = new() { };

            foreach (ComponentStorage? componentStorage in _context.ComponentStorages.ToList())
            {
                if (componentStorage == null)
                    continue;

                cellData.Add(new object[] { componentStorage.Id, componentStorage.WarehouseId, componentStorage.ComponentId, componentStorage.Price, componentStorage.Amount });
            }

            Utilities.ExportToExcel("Учет комплектующих", headerRow, cellData);
        }
    }
}
