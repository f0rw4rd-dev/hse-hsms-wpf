using HardwareStore.Models;
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

namespace HardwareStore.Windows.Suppliers
{
    /// <summary>
    /// Логика взаимодействия для SuppliersUserControl.xaml
    /// </summary>
    public partial class SuppliersUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource suppliersViewSource;

        public SuppliersUserControl()
        {
            InitializeComponent();
            suppliersViewSource = (CollectionViewSource)FindResource(nameof(suppliersViewSource));
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.Suppliers.Load();
            suppliersViewSource.Source = _context.Suppliers.Local.ToObservableCollection();

            suppliersDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].Suppliers.CanAdd;
            suppliersDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].Suppliers.CanDelete;
            suppliersDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].Suppliers.CanEdit;
        }

        private void updateSuppliers_Click(object sender, RoutedEventArgs e)
        {
            _context = new StoreContext();
            _context.Suppliers.Load();
            suppliersViewSource.Source = _context.Suppliers.Local.ToObservableCollection();
        }

        private void saveSuppliers_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, suppliersDataGrid);
        }

        private void exportSuppliers_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "Наименование организации" } };
            List<object[]> cellData = new() { };

            foreach (Supplier? supplier in _context.Suppliers.ToList())
            {
                if (supplier == null)
                    continue;

                cellData.Add(new object[] { supplier.Id, supplier.Name });
            }

            Utilities.ExportToExcel("Поставщики", headerRow, cellData);
        }
    }
}
