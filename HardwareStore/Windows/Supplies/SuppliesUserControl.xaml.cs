using HardwareStore.Models;
using HardwareStore.Windows.Users;
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

namespace HardwareStore.Windows.Supplies
{
    /// <summary>
    /// Логика взаимодействия для SuppliesUserControl.xaml
    /// </summary>
    public partial class SuppliesUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource suppliesViewSource;

        private SuppliesFilter Filter { get; set; }

        public SuppliesUserControl()
        {
            InitializeComponent();
            suppliesViewSource = (CollectionViewSource)FindResource(nameof(suppliesViewSource));
            Filter = new(_context);
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.Supplies.Load();
            suppliesViewSource.Source = _context.Supplies.Local.ToObservableCollection();

            suppliesDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].Supplies.CanAdd;
            suppliesDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].Supplies.CanDelete;
            suppliesDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].Supplies.CanEdit;
        }

        private void updateSupplies_Click(object sender, RoutedEventArgs e)
        {
            Filter = new(_context);

            _context = new StoreContext();
            _context.Supplies.Load();
            suppliesViewSource.Source = _context.Supplies.Local.ToObservableCollection();
        }

        private void saveSupplies_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, suppliesDataGrid);
        }

        private void filterSupplies_Click(object sender, RoutedEventArgs e)
        {
            FilterSuppliesWindow filterSuppliesWindow = new()
            {
                Filter = Filter
            };

            if (filterSuppliesWindow.ShowDialog() == true)
            {
                Filter = filterSuppliesWindow.Filter;
                CollectionViewSource.GetDefaultView(suppliesDataGrid.ItemsSource).Refresh();
            }
        }

        private void CollectionViewSource_Filter(object sender, FilterEventArgs e)
        {
            if (e.Item is Supply supply)
            {
                bool IsSupplyPriceInRange = Filter.SupplyPrice.Min <= supply.SupplyPrice && supply.SupplyPrice <= Filter.SupplyPrice.Max,
                    IsAmountInRange = Filter.Amount.Min <= supply.Amount && supply.Amount <= Filter.Amount.Max,
                    IsDateInRange = Filter.Date <= supply.Date && supply.Date <= Filter.Date + 86400;

                if (!Filter.IsFiltered)
                {
                    e.Accepted = true;
                    return;
                }

                e.Accepted = IsSupplyPriceInRange && IsAmountInRange 
                    && (Filter.Date == -1 || IsDateInRange)
                    && (Filter.Id == -1 || Filter.Id == supply.Id)
                    && (Filter.ComponentId == -1 || Filter.ComponentId == supply.ComponentId)
                    && (Filter.WarehouseId == -1 || Filter.WarehouseId == supply.WarehouseId)
                    && (Filter.SupplierId == -1 || Filter.SupplierId == supply.SupplierId);
            }
        }

        private void reportSupplies_Click(object sender, RoutedEventArgs e)
        {
            long timeStampLastMoth = Utilities.DateTimeToUnixTimeStamp(DateTime.Today.AddMonths(-1));

            if (!_context.Supplies.Any(s => timeStampLastMoth <= s.Date && s.Date <= Utilities.GetCurrentUnixTimeStamp()))
            {
                MessageBox.Show("Для создания отчета необходима, как минимум, одна поставка за последний месяц!", "Ошибка");
                return;
            }

            ReportSuppliesWindow reportSuppliesWindow = new();
            reportSuppliesWindow.ShowDialog();
        }

        private void exportSupplies_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "ИД поставщика", "ИД комплектующего", "ИД склада", "Закупочная цена (руб)", "Количество товара (шт)", "Дата поставки" } };
            List<object[]> cellData = new() { };

            foreach (Supply? supply in _context.Supplies.ToList())
            {
                if (supply == null)
                    continue;

                cellData.Add(new object[] { supply.Id, supply.SupplierId, supply.ComponentId, supply.WarehouseId, supply.SupplyPrice, supply.Amount, Utilities.UnixTimeStampToDateTime(supply.Date).ToString("dd-MM-yyyy HH:mm") });
            }

            Utilities.ExportToExcel("Поставки", headerRow, cellData);
        }
    }
}
