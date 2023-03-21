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
using System.Security.Cryptography;
using System.Text.RegularExpressions;
using HardwareStore.Models;

namespace HardwareStore.Windows.Users
{
    /// <summary>
    /// Логика взаимодействия для SetUserWindow.xaml
    /// </summary>
    public partial class SetUserWindow : Window
    {
        public SetUserWindow()
        {
            InitializeComponent();
        }

        private void setButton_Click(object sender, RoutedEventArgs e)
        {
            if (idTextBox.Text.Length == 0)
            {
                MessageBox.Show("Введите ИД пользователя!", "Ошибка");
                return;
            }

            using StoreContext context = new();
            User? user = context.Users.Where(u => u.Id == int.Parse(idTextBox.Text)).FirstOrDefault();
            if (user != null)
            {
                if (passwordBox.Password.Length > 0)
                    user.Password = Utilities.GetHash(SHA256.Create(), passwordBox.Password);

                user.Group = (Models.Group)int.Parse((string)((TextBlock)groupComboBox.SelectedItem).Tag);
                context.SaveChanges();

                DialogResult = true;
            }
            else
            {
                MessageBox.Show("Данного пользователя не существует!", "Ошибка");
            }
        }

        private void idTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            Utilities.ValidateTextBox(RegularExpressions.GetUnsignedIntRegex(), sender, e);

            using StoreContext context = new();

            User? user = context.Users.Where(u => u.Id == int.Parse(idTextBox.Text)).FirstOrDefault();
            if (user != null)
            {
                groupComboBox.SelectedIndex = (int)user.Group;
            }
        }
    }
}
