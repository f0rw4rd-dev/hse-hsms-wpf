using HardwareStore.Models;
using HardwareStore.Windows.Suppliers;
using HardwareStore.Windows.Warehouses;
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

namespace HardwareStore.Windows.ComponentTypes
{
    /// <summary>
    /// Логика взаимодействия для ComponentTypesUserControl.xaml
    /// </summary>
    public partial class ComponentTypesUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource componentTypesViewSource;

        public ComponentTypesUserControl()
        {
            InitializeComponent();
            componentTypesViewSource = (CollectionViewSource)FindResource(nameof(componentTypesViewSource));
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.ComponentTypes.Load();
            componentTypesViewSource.Source = _context.ComponentTypes.Local.ToObservableCollection();

            componentTypesDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].ComponentTypes.CanAdd;
            componentTypesDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].ComponentTypes.CanDelete;
            componentTypesDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].ComponentTypes.CanEdit;
        }

        private void updateComponentTypes_Click(object sender, RoutedEventArgs e)
        {
            _context = new StoreContext();
            _context.ComponentTypes.Load();
            componentTypesViewSource.Source = _context.ComponentTypes.Local.ToObservableCollection();
        }

        private void saveComponentTypes_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, componentTypesDataGrid);
        }

        private void exportComponentTypes_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "Название" } };
            List<object[]> cellData = new() { };

            foreach (ComponentType? componentType in _context.ComponentTypes.ToList())
            {
                if (componentType == null)
                    continue;

                cellData.Add(new object[] { componentType.Id, componentType.Name });
            }

            Utilities.ExportToExcel("Категории комплектующих", headerRow, cellData);
        }
    }
}
