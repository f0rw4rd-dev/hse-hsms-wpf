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
using Microsoft.EntityFrameworkCore;

namespace HardwareStore.Windows.Users
{
    /// <summary>
    /// Логика взаимодействия для UsersUserControl.xaml
    /// </summary>
    public partial class UsersUserControl : UserControl
    {
        private StoreContext _context = new();

        private readonly CollectionViewSource usersViewSource;

        public UsersUserControl()
        {
            InitializeComponent();
            usersViewSource = (CollectionViewSource)FindResource(nameof(usersViewSource));
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            _context.Users.Load();
            usersViewSource.Source = _context.Users.Local.ToObservableCollection();

            usersDataGrid.CanUserDeleteRows = GroupPermissions.permissions[GroupPermissions.Group].Users.CanDelete;
            usersDataGrid.IsReadOnly = !GroupPermissions.permissions[GroupPermissions.Group].Users.CanEdit;

            addUser.IsEnabled = GroupPermissions.permissions[GroupPermissions.Group].Users.CanAdd;
            removeUser.IsEnabled = GroupPermissions.permissions[GroupPermissions.Group].Users.CanDelete;
            setUser.IsEnabled = GroupPermissions.permissions[GroupPermissions.Group].Users.CanEdit;
        }

        private void updateUsers_Click(object sender, RoutedEventArgs e)
        {
            _context = new StoreContext();
            _context.Users.Load();
            usersViewSource.Source = _context.Users.Local.ToObservableCollection();
        }

        private void saveUsers_Click(object sender, RoutedEventArgs e)
        {
            Utilities.HandleSaveDataGrid(_context, usersDataGrid);
        }

        private void addUser_Click(object sender, RoutedEventArgs e)
        {
            AddUserWindow addUserWindow = new();

            if (addUserWindow.ShowDialog() == true)
            {
                MessageBox.Show($"Пользователь с ИД {addUserWindow.UserID} успешно создан!", "Успех");
                updateUsers_Click(sender, e);
            }
        }

        private void setUser_Click(object sender, RoutedEventArgs e)
        {
            SetUserWindow setUserWindow = new();

            if (setUserWindow.ShowDialog() == true)
            {
                MessageBox.Show($"Данные о пользователе успешно изменены!", "Успех");
                updateUsers_Click(sender, e);
            }
        }

        private void removeUser_Click(object sender, RoutedEventArgs e)
        {
            RemoveUserWindow removeUserWindow = new();

            if (removeUserWindow.ShowDialog() == true)
            {
                MessageBox.Show($"Данные о пользователе удалены!", "Успех");
                updateUsers_Click(sender, e);
            }
        }

        private void exportUsers_Click(object sender, RoutedEventArgs e)
        {
            List<string[]> headerRow = new() { new string[] { "ИД", "Группа прав", "Дата последнего входа", "Дата регистрации" } };
            List<object[]> cellData = new() { };

            foreach (User? user in _context.Users.ToList())
            {
                if (user == null)
                    continue;

                cellData.Add(new object[] { user.Id, user.Group, user.LastVisitDateText, user.RegistrationDateText });
            }

            Utilities.ExportToExcel("Пользователи", headerRow, cellData);
        }
    }
}
