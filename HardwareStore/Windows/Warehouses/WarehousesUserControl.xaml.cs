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
using HardwareStore.Windows.Supplies;
using HardwareStore.Windows.Users;
using Microsoft.EntityFrameworkCore;

namespace HardwareStore.Windows.Warehouses
{
    /// <summary>
    /// Логика взаимодействия для WarehousesUserControl.xaml
    /// </summary>
    public partial class WarehousesUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource warehousesViewSource;

        private WarehousesFilter Filter { get; set; }

        public WarehousesUserControl()
        {
            InitializeComponent();
            warehousesViewSource = (CollectionViewSource)FindResource(nameof(warehousesViewSource));
            Filter = new();
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.Warehouses.Load();
            warehousesViewSource.Source = _context.Warehouses.Local.ToObservableCollection();

            warehousesDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].Warehouses.CanAdd;
            warehousesDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].Warehouses.CanDelete;
            warehousesDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].Warehouses.CanEdit;
        }

        private void updateWarehouses_Click(object sender, RoutedEventArgs e)
        {
            Filter = new();

            _context = new StoreContext();
            _context.Warehouses.Load();
            warehousesViewSource.Source = _context.Warehouses.Local.ToObservableCollection();
        }

        private void saveWarehouses_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, warehousesDataGrid);
        }

        private void filterWarehouses_Click(object sender, RoutedEventArgs e)
        {
            FilterWarehousesWindow filterWarehousesWindow = new()
            {
                Filter = Filter
            };

            if (filterWarehousesWindow.ShowDialog() == true)
            {
                Filter = filterWarehousesWindow.Filter;
                CollectionViewSource.GetDefaultView(warehousesDataGrid.ItemsSource).Refresh();
            }
        }

        private void CollectionViewSource_Filter(object sender, FilterEventArgs e)
        {
            if (e.Item is Warehouse warehouse)
            {
                if (!Filter.IsFiltered)
                {
                    e.Accepted = true;
                    return;
                }

                e.Accepted = (Filter.Id == -1 || Filter.Id == warehouse.Id)
                    && (Filter.Zip == -1 || Filter.Zip == warehouse.Zip)
                    && (Filter.City.Length == 0 || Filter.City == warehouse.City)
                    && (Filter.Street.Length == 0 || Filter.Street == warehouse.Street)
                    && (Filter.House.Length == 0 || Filter.House == warehouse.House);
            }
        }

        private void exportWarehouses_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "Город", "Улица", "Дом", "Индекс" } };
            List<object[]> cellData = new() { };

            foreach (Warehouse? warehouse in _context.Warehouses.ToList())
            {
                if (warehouse == null)
                    continue;

                cellData.Add(new object[] { warehouse.Id, warehouse.City, warehouse.Street, warehouse.House, warehouse.Zip });
            }

            Utilities.ExportToExcel("Склады", headerRow, cellData);
        }
    }
}
