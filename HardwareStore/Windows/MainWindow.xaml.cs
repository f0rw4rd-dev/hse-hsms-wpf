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

namespace HardwareStore.Windows
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var visibility = (bool permissionOption) => (permissionOption) ? Visibility.Visible : Visibility.Collapsed;

            componentsTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].Components.CanView);
            componentDetailsTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].ComponentDetails.CanView);
            componentStoragesTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].ComponentStorages.CanView);
            componentTypesTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].ComponentTypes.CanView);
            configurationsTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].Configurations.CanView);
            detailTypesTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].DetailTypes.CanView);
            ordersTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].Orders.CanView);
            orderComponentsTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].OrderComponents.CanView);
            suppliersTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].Suppliers.CanView);
            suppliesTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].Supplies.CanView);
            usersTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].Users.CanView);
            warehousesTab.Visibility = visibility(GroupPermissions.permissions[GroupPermissions.Group].Warehouses.CanView);

            foreach (TabItem tabItem in tabControl.Items)
            {
                if (tabItem.Visibility == Visibility.Visible)
                {
                    tabControl.SelectedIndex = tabItem.TabIndex;
                    break;
                }
            }
        }
    }
}
