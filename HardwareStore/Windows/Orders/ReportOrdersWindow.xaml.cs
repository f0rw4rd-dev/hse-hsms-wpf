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

            LineSeries line = new()
            {
                MarkerType = MarkerType.Circle,
                MarkerFill = OxyColors.SteelBlue,
                MarkerSize = 6,
            };

            DateTime dateTimeLastMonth = DateTime.Today.AddMonths(-1);
            long timeStampLastMoth = Utilities.DateTimeToUnixTimeStamp(dateTimeLastMonth);

            List<Models.Order> orders = _context.Orders.Where(o => timeStampLastMoth <= o.Date && o.Date <= Utilities.GetCurrentUnixTimeStamp()).OrderBy(o => o.Date).ToList();

            if (orders.Count == 0)
                return;

            DateTime orderDateTime = new(1970, 1, 1), previousDateTime = Utilities.UnixTimeStampToDateTime(orders.First().Date);
            int amountInDay = 0;

            foreach (Models.Order order in orders)
            {
                orderDateTime = Utilities.UnixTimeStampToDateTime(order.Date);

                if (orderDateTime.Day != previousDateTime.Day)
                {
                    line.Points.Add(new DataPoint(DateTimeAxis.ToDouble(new DateTime(previousDateTime.Year, previousDateTime.Month, previousDateTime.Day)), amountInDay));
                    previousDateTime = orderDateTime;
                    amountInDay = 0;
                }

                amountInDay++;
            }

            line.Points.Add(new DataPoint(DateTimeAxis.ToDouble(new DateTime(previousDateTime.Year, previousDateTime.Month, previousDateTime.Day)), amountInDay));

            DateTimeAxis xAxis = new()
            {
                Key = "X0",
                Position = AxisPosition.Bottom,
                Minimum = DateTimeAxis.ToDouble(Utilities.UnixTimeStampToDateTime(orders.First().Date)),
                Maximum = DateTimeAxis.ToDouble(Utilities.UnixTimeStampToDateTime(Utilities.DateTimeToUnixTimeStamp(DateTime.Now))),
                IntervalType = DateTimeIntervalType.Days,
                MajorGridlineStyle = LineStyle.Solid,
                StringFormat = "dd/MM",
                MajorStep = 1,
                IsZoomEnabled = true,
                MaximumPadding = 1,
                MinimumPadding = 1,
                TickStyle = TickStyle.None,
                Title = "Дата заказа",
                MinimumDataMargin = 15
            };

            LinearAxis yAxis = new()
            {
                Position = AxisPosition.Left,
                MajorStep = 1,
                Title = "Число заказов"
            };

            Model.Axes.Add(xAxis);
            Model.Axes.Add(yAxis);
            Model.Series.Add(line);
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
