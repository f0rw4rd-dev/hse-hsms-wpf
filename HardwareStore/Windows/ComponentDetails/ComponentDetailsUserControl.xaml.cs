using HardwareStore.Windows.Components;
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
using HardwareStore.Models;
using System.IO;
using OfficeOpenXml;
using Microsoft.Win32;
using System.ComponentModel;

namespace HardwareStore.Windows.ComponentDetails
{
    /// <summary>
    /// Логика взаимодействия для ComponentDetailsUserControl.xaml
    /// </summary>
    public partial class ComponentDetailsUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource componentDetailsViewSource;
        private readonly CollectionViewSource detailTypesViewSource;

        private ComponentDetailsFilter Filter { get; set; }

        public ComponentDetailsUserControl()
        {
            InitializeComponent();
            componentDetailsViewSource = (CollectionViewSource)FindResource(nameof(componentDetailsViewSource));
            detailTypesViewSource = (CollectionViewSource)FindResource(nameof(detailTypesViewSource));
            Filter = new();
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.ComponentDetails.Load();
            _context.DetailTypes.Load();

            componentDetailsViewSource.GroupDescriptions.Clear();
            componentDetailsViewSource.GroupDescriptions.Add(new PropertyGroupDescription("ComponentId"));
            componentDetailsViewSource.Source = _context.ComponentDetails.Local.ToObservableCollection();

            detailTypesViewSource.Source = _context.DetailTypes.Local.ToObservableCollection();

            componentDetailsDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].ComponentDetails.CanAdd;
            componentDetailsDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].ComponentDetails.CanDelete;
            componentDetailsDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].ComponentDetails.CanEdit;
        }

        private void updateComponentDetails_Click(object sender, RoutedEventArgs e)
        {
            Filter = new();

            _context = new StoreContext();
            _context.ComponentDetails.Load();
            _context.DetailTypes.Load();

            componentDetailsViewSource.GroupDescriptions.Clear();
            componentDetailsViewSource.GroupDescriptions.Add(new PropertyGroupDescription("ComponentId"));
            componentDetailsViewSource.Source = _context.ComponentDetails.Local.ToObservableCollection();

            detailTypesViewSource.Source = _context.DetailTypes.Local.ToObservableCollection();
        }

        private void saveComponentDetails_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, componentDetailsDataGrid);
        }

        private void filterComponentDetails_Click(object sender, RoutedEventArgs e)
        {
            FilterComponentDetailsWindow filterComponentDetailsWindow = new()
            {
                Filter = Filter
            };

            if (filterComponentDetailsWindow.ShowDialog() == true)
            {
                Filter = filterComponentDetailsWindow.Filter;
                CollectionViewSource.GetDefaultView(componentDetailsDataGrid.ItemsSource).Refresh();
            }
        }

        private void exportComponentDetails_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "ИД комплектующего", "ИД характеристики", "Название характеристики", "Значение" } };
            List<object[]> cellData = new() { };

            foreach (ComponentDetail? componentDetail in _context.ComponentDetails.ToList())
            {
                if (componentDetail == null)
                    continue;

                cellData.Add(new object[] { componentDetail.Id, componentDetail.ComponentId, componentDetail.DetailTypeId, componentDetail.DetailType.Name, componentDetail.Value });
            }

            Utilities.ExportToExcel("Характеристики комплектующих", headerRow, cellData);
        }

        private void CollectionViewSource_Filter(object sender, FilterEventArgs e)
        {
            if (e.Item is ComponentDetail componentDetail)
            {
                if (!Filter.IsFiltered)
                {
                    e.Accepted = true;
                    return;
                }

                e.Accepted = (Filter.Id == -1 || Filter.Id == componentDetail.Id)
                    && (Filter.ComponentId == -1 || Filter.Id == componentDetail.ComponentId)
                    && (Filter.DetailTypeId == -1 || Filter.Id == componentDetail.DetailTypeId)
                    && (Filter.Value.Length == 0 || Filter.Value == componentDetail.Value);
            }
        }
    }
}
