using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace HardwareStore
{
    public static partial class RegularExpressions
    {
        [GeneratedRegex(@"[^\d]", RegexOptions.IgnoreCase, "en-US")]
        public static partial Regex GetUnsignedIntRegex();

        [GeneratedRegex(@"[^\d,]", RegexOptions.IgnoreCase, "en-US")]
        public static partial Regex GetUnsignedFloatRegex();

        [GeneratedRegex(@"[^a-zA-Zа-яА-Я- ]", RegexOptions.IgnoreCase, "en-US")]
        public static partial Regex GetCityRegex();

        [GeneratedRegex(@"[^a-zA-Zа-яА-Я- ]", RegexOptions.IgnoreCase, "en-US")]
        public static partial Regex GetStreetRegex();

        [GeneratedRegex(@"[^a-zA-Zа-яА-Я-'\"" ]", RegexOptions.IgnoreCase, "en-US")]
        public static partial Regex GetSupplierNameRegex();

        [GeneratedRegex(@"[^a-zA-Zа-яА-Я-()\d.,/'\"" ]", RegexOptions.IgnoreCase, "en-US")]
        public static partial Regex GetCategoryTypeRegex();

        [GeneratedRegex(@"[^a-zA-Zа-яА-Я-()\d.,/ ]", RegexOptions.IgnoreCase, "en-US")]
        public static partial Regex GetDetailTypeRegex();

        [GeneratedRegex(@"[^a-zA-Zа-яА-Я-\d\[\]().,/ ]", RegexOptions.IgnoreCase, "en-US")]
        public static partial Regex GetComponentNameRegex();
    }
}
