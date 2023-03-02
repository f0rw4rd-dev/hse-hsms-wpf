using HardwareStore.Models;
using HardwareStore.Windows.OrderComponents;
using HardwareStore.Windows.Orders;
using HardwareStore.Windows.Suppliers;
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

namespace HardwareStore.Windows.Components
{
    /// <summary>
    /// Логика взаимодействия для ComponentsUserControl.xaml
    /// </summary>
    public partial class ComponentsUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource componentsViewSource;
        private readonly CollectionViewSource componentTypesViewSource;

        private ComponentsFilter Filter { get; set; }

        public ComponentsUserControl()
        {
            InitializeComponent();
            componentsViewSource = (CollectionViewSource)FindResource(nameof(componentsViewSource));
            componentTypesViewSource = (CollectionViewSource)FindResource(nameof(componentTypesViewSource));
            Filter = new(_context);
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.Components.Load();
            _context.ComponentTypes.Load();

            componentsViewSource.Source = _context.Components.Local.ToObservableCollection();
            componentTypesViewSource.Source = _context.ComponentTypes.Local.ToObservableCollection();

            componentsDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].Components.CanAdd;
            componentsDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].Components.CanDelete;
            componentsDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].Components.CanEdit;
        }

        private void updateComponents_Click(object sender, RoutedEventArgs e)
        {
            Filter = new(_context);

            _context = new StoreContext();
            _context.Components.Load();
            _context.ComponentTypes.Load();
            componentsViewSource.Source = _context.Components.Local.ToObservableCollection();
            componentTypesViewSource.Source = _context.ComponentTypes.Local.ToObservableCollection();
        }

        private void saveComponents_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, componentsDataGrid);
        }

        private void filterComponents_Click(object sender, RoutedEventArgs e)
        {
            FilterComponentsWindow filterComponentsWindow = new()
            {
                Filter = Filter
            };

            if (filterComponentsWindow.ShowDialog() == true)
            {
                Filter = filterComponentsWindow.Filter;
                CollectionViewSource.GetDefaultView(componentsDataGrid.ItemsSource).Refresh();
            }
        }

        private void CollectionViewSource_Filter(object sender, FilterEventArgs e)
        {
            if (e.Item is Component component)
            {
                bool IsWarrantyInRange = Filter.Warranty.Min <= component.Warranty && component.Warranty <= Filter.Warranty.Max;

                if (!Filter.IsFiltered)
                {
                    e.Accepted = true;
                    return;
                }

                e.Accepted = IsWarrantyInRange 
                    && (Filter.Id == -1 || Filter.Id == component.Id)
                    && (Filter.Name.Length == 0 || component.Name == Filter.Name)
                    && (Filter.ComponentTypeId == -1 || Filter.ComponentTypeId == component.ComponentTypeId);
            }
        }

        private void reportComponents_Click(object sender, RoutedEventArgs e)
        {
            if (!_context.Components.Any())
            {
                MessageBox.Show("Для создания отчета необходима, как минимум, одна запись!", "Ошибка");
                return;
            }

            ReportComponentsWindow reportComponentsWindow = new();
            reportComponentsWindow.ShowDialog();
        }

        private void exportComponents_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "Модель", "ИД категории", "Название категории", "Гарантия (мес)" } };
            List<object[]> cellData = new() { };

            foreach (Component? component in _context.Components.ToList())
            {
                if (component == null)
                    continue;

                cellData.Add(new object[] { component.Id, component.Name, component.ComponentTypeId, component.ComponentType.Name, component.Warranty });
            }

            Utilities.ExportToExcel("Комплектующие", headerRow, cellData);
        }
    }
}
