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
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;
using OxyPlot.Wpf;

namespace HardwareStore.Windows.Orders
{
    public class OrdersPlotModel
    {
        private StoreContext _context = new();

        public PlotModel Model { get; private set; }

        public OrdersPlotModel()
        {
            Model = new()
            {
                Title = "Число заказов за последние 30 дней",
                DefaultColors = new List<OxyColor> { OxyColors.SteelBlue, },
            };

            BarSeries series = new();

            DateTime dateTimeLastMonth = DateTime.Today.AddMonths(-1);
            long timeStampLastMoth = Utilities.DateTimeToUnixTimeStamp(dateTimeLastMonth);

            List<Models.Order> orders = _context.Orders.Where(o => timeStampLastMoth <= o.Date && o.Date <= Utilities.GetCurrentUnixTimeStamp()).OrderBy(o => o.Date).ToList();

            if (orders.Count == 0)
                return;

            Dictionary<string, int> days = new();

            CategoryAxis categoryAxis = new()
            {
                Position = AxisPosition.Left,
                Title = "Дата поставки"
            };

            for (int i = 0; i < 30; i++)
            {
                string day = DateTime.Today.AddDays(-i).ToString("dd.MM");

                categoryAxis.Labels.Add(day);
                days[day] = i;
            }

            Dictionary<string, int> amounts = new();

            foreach (Models.Order order in orders)
            {
                DateTime orderDateTime = Utilities.UnixTimeStampToDateTime(order.Date);
                string day = orderDateTime.ToString("dd.MM");

                if (!amounts.ContainsKey(day))
                    amounts[day] = 0;

                amounts[day]++;
            }

            foreach (KeyValuePair<string, int> amount in amounts)
            {
                series.Items.Add(new BarItem(amount.Value, days[amount.Key]));
            }

            LinearAxis amountAxis = new()
            {
                Position = AxisPosition.Bottom,
                MinimumMajorStep = 1,
                Title = "Число заказов"
            };

            Model.Axes.Add(categoryAxis);
            Model.Axes.Add(amountAxis);
            Model.Series.Add(series);
        }
    }

    /// <summary>
    /// Логика взаимодействия для ReportOrdersWindow.xaml
    /// </summary>
    public partial class ReportOrdersWindow : Window
    {
        public ReportOrdersWindow()
        {
            InitializeComponent();
        }
    }
}
