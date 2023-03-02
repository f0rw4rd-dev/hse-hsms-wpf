using HardwareStore.Models;
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

namespace HardwareStore.Windows.DetailTypes
{
    /// <summary>
    /// Логика взаимодействия для DetailTypesUserControl.xaml
    /// </summary>
    public partial class DetailTypesUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource detailTypesViewSource;

        public DetailTypesUserControl()
        {
            InitializeComponent();
            detailTypesViewSource = (CollectionViewSource)FindResource(nameof(detailTypesViewSource));
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.DetailTypes.Load();
            detailTypesViewSource.Source = _context.DetailTypes.Local.ToObservableCollection();

            detailTypesDataGrid.CanUserAddRows = GroupPermissions.permissions[GroupPermissions.Group].DetailTypes.CanAdd;
            detailTypesDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].DetailTypes.CanDelete;
            detailTypesDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].DetailTypes.CanEdit;
        }

        private void updateDetailTypes_Click(object sender, RoutedEventArgs e)
        {
            _context = new StoreContext();
            _context.DetailTypes.Load();
            detailTypesViewSource.Source = _context.DetailTypes.Local.ToObservableCollection();
        }

        private void saveDetailTypes_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, detailTypesDataGrid);
        }

        private void exportDetailTypes_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "Название" } };
            List<object[]> cellData = new() { };

            foreach (DetailType? detailType in _context.DetailTypes.ToList())
            {
                if (detailType == null)
                    continue;

                cellData.Add(new object[] { detailType.Id, detailType.Name });
            }

            Utilities.ExportToExcel("Типы характеристик комплектующих", headerRow, cellData);
        }
    }
}
