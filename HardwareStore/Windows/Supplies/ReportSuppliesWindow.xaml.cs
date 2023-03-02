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
using System.Xml.Linq;
using Microsoft.EntityFrameworkCore;
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;
using OxyPlot.Wpf;

namespace HardwareStore.Windows.Supplies
{
    public class SuppliesPlotModel
    {
        private StoreContext _context = new();

        public PlotModel Model { get; private set; }

        public SuppliesPlotModel()
        {
            Model = new()
            { 
                Title = "Число поставок за последние 30 дней",
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

            List<Models.Supply> supplies = _context.Supplies.Where(s => timeStampLastMoth <= s.Date && s.Date <= Utilities.GetCurrentUnixTimeStamp()).OrderBy(s => s.Date).ToList();

            if (supplies.Count == 0)
                return;

            DateTime supplyDateTime = new(1970, 1, 1), previousDateTime = Utilities.UnixTimeStampToDateTime(supplies.First().Date);
            int amountInDay = 0;

            foreach (Models.Supply supply in supplies)
            {
                supplyDateTime = Utilities.UnixTimeStampToDateTime(supply.Date);

                if (supplyDateTime.Day != previousDateTime.Day)
                {
                    line.Points.Add(new DataPoint(DateTimeAxis.ToDouble(new DateTime(previousDateTime.Year, previousDateTime.Month, previousDateTime.Day)), amountInDay));
                    previousDateTime = supplyDateTime;
                    amountInDay = 0;
                }

                amountInDay++;

            }

            line.Points.Add(new DataPoint(DateTimeAxis.ToDouble(new DateTime(previousDateTime.Year, previousDateTime.Month, previousDateTime.Day)), amountInDay));

            DateTimeAxis xAxis = new()
            {
                Key = "X0",
                Position = AxisPosition.Bottom,
                Minimum = DateTimeAxis.ToDouble(Utilities.UnixTimeStampToDateTime(supplies.First().Date)),
                Maximum = DateTimeAxis.ToDouble(Utilities.UnixTimeStampToDateTime(Utilities.DateTimeToUnixTimeStamp(DateTime.Now))),
                //Maximum = DateTimeAxis.ToDouble(Utilities.UnixTimeStampToDateTime(supplies.Last().Date)),
                IntervalType = DateTimeIntervalType.Days,
                MajorGridlineStyle = LineStyle.Solid,
                StringFormat = "dd/MM",
                MajorStep = 1,
                IsZoomEnabled = true,
                MaximumPadding = 1,
                MinimumPadding = 1,
                TickStyle = TickStyle.None,
                Title = "Дата поставки",
                MinimumDataMargin = 15
            };

            LinearAxis yAxis = new()
            {
                Position = AxisPosition.Left,
                MajorStep = 1,
                Title = "Число поставок"
            };

            Model.Axes.Add(xAxis);
            Model.Axes.Add(yAxis);
            Model.Series.Add(line);
        }
    }

    /// <summary>
    /// Логика взаимодействия для ReportSuppliesWindow.xaml
    /// </summary>
    public partial class ReportSuppliesWindow : Window
    {
        public ReportSuppliesWindow()
        {
            InitializeComponent();
        }
    }
}
