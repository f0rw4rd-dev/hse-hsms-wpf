using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
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
using Npgsql;

namespace HardwareStore.Windows
{
    /// <summary>
    /// Логика взаимодействия для LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        public LoginWindow()
        {
            InitializeComponent();
        }

        private void loginButton_Click(object sender, RoutedEventArgs e)
        {
            if (loginTextBox.Text.Length == 0 || passwordBox.Password.Length == 0) 
            {
                MessageBox.Show("Пожалуйста, заполните все поля!", "Ошибка");
                return;
            }

            int id = int.Parse(loginTextBox.Text);
            string encryptedPassword = Utilities.GetHash(SHA256.Create(), passwordBox.Password);

            using StoreContext context = new();

            User? user = context.Users.Where(u => u.Id == id && u.Password == encryptedPassword).FirstOrDefault();

            if (user != null)
            {
                user.LastVisitDate = Utilities.GetCurrentUnixTimeStamp();
                context.SaveChanges();

                GroupPermissions.UserId = user.Id;

                MainWindow mainWindow = new();
                Close();
                mainWindow.Show();
            }
            else
            {
                MessageBox.Show("Данного пользователя не существует!", "Ошибка");
            }
        }

        private void loginTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            string correctLogin = RegularExpressions.GetUnsignedIntRegex().Replace(((TextBox)sender).Text, "");
            ((TextBox)sender).Text = correctLogin;

            ((TextBox)sender).CaretIndex = ((TextBox)sender).Text.Length;
        }
    }
}
