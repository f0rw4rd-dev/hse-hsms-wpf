using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
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
using HardwareStore.Models;

namespace HardwareStore.Windows.Users
{
    /// <summary>
    /// Логика взаимодействия для AddUserWindow.xaml
    /// </summary>
    public partial class AddUserWindow : Window
    {
        public int UserID { get; private set; }

        public AddUserWindow()
        {
            InitializeComponent();
        }

        private void addButton_Click(object sender, RoutedEventArgs e)
        {
            if (passwordBox.Password.Length == 0)
            {
                MessageBox.Show("Введите пароль!", "Ошибка");
                return;
            }

            using StoreContext context = new();

            Group group = (Group)int.Parse((string)((TextBlock)groupComboBox.SelectedItem).Tag);

            User user = new() { Password = Utilities.GetHash(SHA256.Create(), passwordBox.Password), Group = group, RegistrationDate = DateTimeOffset.Now.ToUnixTimeSeconds() };

            context.Users.Add(user);
            context.SaveChanges();

            UserID = context.Users.OrderBy(u => u.Id).Last().Id;

            DialogResult = true;
        }
    }
}
