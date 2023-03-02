using HardwareStore.Models;
using HardwareStore.Windows.Supplies;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Configuration;
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

namespace HardwareStore.Windows.OrderComponents
{
    /// <summary>
    /// Логика взаимодействия для OrderComponentsUserControl.xaml
    /// </summary>
    public partial class OrderComponentsUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource orderComponentsViewSource;

        private OrderComponentsFilter Filter { get; set; }

        public OrderComponentsUserControl()
        {
            InitializeComponent();
            orderComponentsViewSource = (CollectionViewSource)FindResource(nameof(orderComponentsViewSource));
            Filter = new(_context);
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.OrderComponents.Load();

            orderComponentsViewSource.GroupDescriptions.Clear();
            orderComponentsViewSource.GroupDescriptions.Add(new PropertyGroupDescription("OrderId"));
            orderComponentsViewSource.Source = _context.OrderComponents.Local.ToObservableCollection();

            orderComponentsDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].OrderComponents.CanAdd;
            orderComponentsDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].OrderComponents.CanDelete;
            orderComponentsDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].OrderComponents.CanEdit;
        }

        private void updateOrderComponents_Click(object sender, RoutedEventArgs e)
        {
            Filter = new(_context);

            _context = new StoreContext();
            _context.OrderComponents.Load();

            orderComponentsViewSource.GroupDescriptions.Clear();
            orderComponentsViewSource.GroupDescriptions.Add(new PropertyGroupDescription("OrderId"));
            orderComponentsViewSource.Source = _context.OrderComponents.Local.ToObservableCollection();
        }

        private void saveOrderComponents_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, orderComponentsDataGrid);
        }

        private void filterOrderComponents_Click(object sender, RoutedEventArgs e)
        {
            FilterOrderComponentsWindow filterSuppliesWindow = new()
            {
                Filter = Filter
            };

            if (filterSuppliesWindow.ShowDialog() == true)
            {
                Filter = filterSuppliesWindow.Filter;
                CollectionViewSource.GetDefaultView(orderComponentsDataGrid.ItemsSource).Refresh();
            }
        }

        private void CollectionViewSource_Filter(object sender, FilterEventArgs e)
        {
            if (e.Item is OrderComponent orderComponent)
            {
                bool IsPriceInRange = Filter.Price.Min <= orderComponent.Price && orderComponent.Price <= Filter.Price.Max,
                    IsAmountInRange = Filter.Amount.Min <= orderComponent.Amount && orderComponent.Amount <= Filter.Amount.Max;

                if (!Filter.IsFiltered)
                {
                    e.Accepted = true;
                    return;
                }

                e.Accepted = IsPriceInRange && IsAmountInRange
                    && (Filter.Id == -1 || Filter.Id == orderComponent.Id)
                    && (Filter.ComponentId == -1 || Filter.ComponentId == orderComponent.ComponentId)
                    && (Filter.WarehouseId == -1 || Filter.WarehouseId == orderComponent.WarehouseId)
                    && (Filter.OrderId == -1 || Filter.OrderId == orderComponent.OrderId);
            }
        }

        private void exportOrderComponents_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "ИД заказа", "ИД склада", "ИД комплектующего", "Цена (руб)", "Количество (шт)", "Часть конфигурации" } };
            List<object[]> cellData = new() { };

            foreach (OrderComponent? orderComponent in _context.OrderComponents.ToList())
            {
                if (orderComponent == null)
                    continue;

                cellData.Add(new object[] { orderComponent.Id, orderComponent.OrderId, orderComponent.WarehouseId, orderComponent.ComponentId, orderComponent.Price, orderComponent.Amount, orderComponent.IsPartOfConfiguration });
            }

            Utilities.ExportToExcel("Содержимое заказов", headerRow, cellData);
        }
    }
}
