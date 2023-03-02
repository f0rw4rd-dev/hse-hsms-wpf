using HardwareStore.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.Win32;
using OfficeOpenXml;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows;

namespace HardwareStore
{
    public static class Utilities
    {
        public static string GetHash(HashAlgorithm hashAlgorithm, string input)
        {
            byte[] data = hashAlgorithm.ComputeHash(Encoding.UTF8.GetBytes(input));
            var sBuilder = new StringBuilder();

            for (int i = 0; i < data.Length; i++)
                sBuilder.Append(data[i].ToString("x2"));

            return sBuilder.ToString();
        }

        public static DateTime UnixTimeStampToDateTime(long unixTimeStamp)
        {
            DateTime dateTime = new(1970, 1, 1, 0, 0, 0, 0, DateTimeKind.Utc);
            dateTime = dateTime.AddSeconds(unixTimeStamp).ToLocalTime();
            return dateTime;
        }

        public static long DateTimeToUnixTimeStamp(DateTime time)
        {
            return ((DateTimeOffset)time).ToUnixTimeSeconds();
        }

        public static long GetCurrentUnixTimeStamp()
        {
            return new DateTimeOffset(DateTime.UtcNow).ToUnixTimeSeconds();
        }

        public static void ValidateTextBox(Regex regex, object sender, TextChangedEventArgs e)
        {
            string correct = regex.Replace(((TextBox)sender).Text, "");

            ((TextBox)sender).Text = correct;
            ((TextBox)sender).CaretIndex = ((TextBox)sender).Text.Length;
        }

        public static int TryParse(string source, int defaultValue)
        {
            if (int.TryParse(source, out int result))
                return result;
            else

                return defaultValue;
        }

        public static float TryParse(string source, float defaultValue)
        {
            if (float.TryParse(source, out float result))
                return result;
            else
                return defaultValue;
        }

        public static void ExportToExcel(string worksheetName, List<string[]> headerRow, List<object[]> cellData)
        {
            SaveFileDialog saveFileDialog = new()
            {
                Filter = "Excel files (*.xlsx)|*.xlsx"
            };

            if (saveFileDialog.ShowDialog() == true)
            {
                ExcelPackage.LicenseContext = LicenseContext.NonCommercial;

                using ExcelPackage excel = new();

                excel.Workbook.Worksheets.Add(worksheetName);

                string headerRange = "A1:" + Char.ConvertFromUtf32(headerRow[0].Length + 64) + "1";

                ExcelWorksheet worksheet = excel.Workbook.Worksheets[worksheetName];
                worksheet.Cells[headerRange].LoadFromArrays(headerRow);

                worksheet.Cells[2, 1].LoadFromArrays(cellData);

                FileInfo excelFile = new(saveFileDialog.FileName);
                excel.SaveAs(excelFile);

                MessageBox.Show("Данные успешно экспортированы!", "Успех");
            }
        }

        public static void HandleSaveDataGrid(in StoreContext context, in DataGrid dataGrid)
        {
            string messageError = "Убедитесь в правительности заполнения всех данных! После добавления или изменения записи необходимо нажать Enter.";

            try
            {
                context.SaveChanges();
                dataGrid.Items.Refresh();
            }
            catch (DbUpdateException)
            {
                MessageBox.Show(messageError, "Ошибка");
            }
            catch (InvalidOperationException)
            {
                MessageBox.Show(messageError, "Ошибка");
            }
        }
    }
}
