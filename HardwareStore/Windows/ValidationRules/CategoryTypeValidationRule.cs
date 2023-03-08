﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace HardwareStore.Windows.ValidationRules
{
    public class ComponentTypeValidationRule : ValidationRule
    {
        public override ValidationResult Validate(object value, System.Globalization.CultureInfo cultureInfo)
        {
            string? input = value.ToString();

            if (input == null || input == string.Empty)
                return new ValidationResult(false, "Поле должно быть заполнено");

            if (RegularExpressions.GetComponentTypeRegex().IsMatch(input))
                return new ValidationResult(false, "В ячейке присутствуют запрещенные символы");

            return new ValidationResult(true, null);
        }
    }
}
