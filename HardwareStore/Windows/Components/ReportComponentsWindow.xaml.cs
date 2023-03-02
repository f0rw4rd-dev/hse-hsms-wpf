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
using HardwareStore.Models;

namespace HardwareStore.Windows.Components
{
    public class ComponentsPlotModel
    {
        private StoreContext _context = new();

        public PlotModel Model { get; private set; }

        public ComponentsPlotModel()
        {
            Model = new() { Title = "Доля категорий комплектующих" };

            dynamic series = new PieSeries() { StrokeThickness = 2.0, InsideLabelPosition = 0.8, AngleSpan = 360, StartAngle = 0 };

            int totalEntries = _context.Components.Count();

            var categories = _context.Components.GroupBy(c => c.ComponentTypeId).Select(c => new { categoryTypeId = c.Key, count = c.Count() }).ToList();

            foreach (var category in categories)
            {
                ComponentType? componentType = _context.ComponentTypes.Find(category.categoryTypeId);

                if (componentType != null)
                {
                    series.Slices.Add(new PieSlice(componentType.Name, category.count)
                    {
                        IsExploded = false
                    });
                }
            }

            Model.Series.Add(series);
        }
    }

    /// <summary>
    /// Логика взаимодействия для ReportComponentsWindow.xaml
    /// </summary>
    public partial class ReportComponentsWindow : Window
    {
        public ReportComponentsWindow()
        {
            InitializeComponent();
        }
    }
}
