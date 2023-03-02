using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace HardwareStore.Windows.ValidationRules
{
    public class UnsignedIntValidationRule : ValidationRule
    {
        public override ValidationResult Validate(object value, System.Globalization.CultureInfo cultureInfo)
        {
            string? input = value.ToString();

            if (input == null || input == string.Empty)
                return new ValidationResult(false, "Поле должно быть заполнено");

            if (!int.TryParse(input, out int proposedValue))
                return new ValidationResult(false, "Данные некорректны");

            if (proposedValue < 0)
                return new ValidationResult(false, "Значение в ячейке не может быть отрицательным");

            return new ValidationResult(true, null);
        }
    }
}
