using HardwareStore.Models;
using HardwareStore.Windows.Supplies;
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

namespace HardwareStore.Windows.Orders
{
    /// <summary>
    /// Логика взаимодействия для OrdersUserControl.xaml
    /// </summary>
    public partial class OrdersUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource ordersViewSource;

        private OrdersFilter Filter { get; set; }

        public OrdersUserControl()
        {
            InitializeComponent();
            ordersViewSource = (CollectionViewSource)FindResource(nameof(ordersViewSource));
            Filter = new();
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.Orders.Load();
            ordersViewSource.Source = _context.Orders.Local.ToObservableCollection();

            ordersDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].Orders.CanAdd;
            ordersDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].Orders.CanDelete;
            ordersDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].Orders.CanEdit;
        }

        private void updateOrders_Click(object sender, RoutedEventArgs e)
        {
            Filter = new();

            _context = new StoreContext();
            _context.Orders.Load();
            ordersViewSource.Source = _context.Orders.Local.ToObservableCollection();
        }

        private void saveOrders_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, ordersDataGrid);
        }

        private void filterOrders_Click(object sender, RoutedEventArgs e)
        {
            FilterOrdersWindow filterOrdersWindow = new()
            {
                Filter = Filter
            };

            if (filterOrdersWindow.ShowDialog() == true)
            {
                Filter = filterOrdersWindow.Filter;
                CollectionViewSource.GetDefaultView(ordersDataGrid.ItemsSource).Refresh();
            }
        }

        private void CollectionViewSource_Filter(object sender, FilterEventArgs e)
        {
            if (e.Item is Order order)
            {
                bool IsDateInRange = Filter.Date <= order.Date && order.Date <= Filter.Date + 86400;

                if (!Filter.IsFiltered)
                {
                    e.Accepted = true;
                    return;
                }

                e.Accepted = (Filter.Date == -1 || IsDateInRange)
                    && (Filter.Id == -1 || Filter.Id == order.Id)
                    && (Filter.Status == -1 || Filter.Status == (int)order.Status);
            }
        }

        private void reportOrders_Click(object sender, RoutedEventArgs e)
        {
            long timeStampLastMoth = Utilities.DateTimeToUnixTimeStamp(DateTime.Today.AddMonths(-1));

            if (!_context.Orders.Any(o => timeStampLastMoth <= o.Date && o.Date <= Utilities.GetCurrentUnixTimeStamp()))
            {
                MessageBox.Show("Для создания отчета необходимо наличие, как минимум, одного заказа за последний месяц!", "Ошибка");
                return;
            }

            ReportOrdersWindow reportOrdersWindow = new();
            reportOrdersWindow.ShowDialog();
        }

        private void exportOrders_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "Дата заказа", "Статус заказа" } };
            List<object[]> cellData = new() { };

            foreach (Order? order in _context.Orders.ToList())
            {
                if (order == null)
                    continue;

                cellData.Add(new object[] { order.Id, Utilities.UnixTimeStampToDateTime(order.Date).ToString("dd-MM-yyyy HH:mm"), order.Status });
            }

            Utilities.ExportToExcel("Заказы", headerRow, cellData);
        }
    }
}
