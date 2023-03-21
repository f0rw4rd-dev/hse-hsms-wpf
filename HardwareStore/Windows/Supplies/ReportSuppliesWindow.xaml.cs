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

            BarSeries series = new();

            DateTime dateTimeLastMonth = DateTime.Today.AddMonths(-1);
            long timeStampLastMoth = Utilities.DateTimeToUnixTimeStamp(dateTimeLastMonth);

            List<Models.Supply> supplies = _context.Supplies.Where(o => timeStampLastMoth <= o.Date && o.Date <= Utilities.GetCurrentUnixTimeStamp()).OrderBy(o => o.Date).ToList();

            if (supplies.Count == 0)
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

            foreach (Models.Supply supply in supplies)
            {
                DateTime supplyDateTime = Utilities.UnixTimeStampToDateTime(supply.Date);
                string day = supplyDateTime.ToString("dd.MM");

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
                Title = "Число поставок"
            };

            Model.Axes.Add(categoryAxis);
            Model.Axes.Add(amountAxis);
            Model.Series.Add(series);
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
