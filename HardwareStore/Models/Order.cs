using HardwareStore.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Documents;

namespace HardwareStore.Models
{
    public enum OrderStatus : int
    {
        [Description("Создан")]
        Created = 0,
        [Description("В обработке")]
        Processing = 1,
        [Description("Готов")]
        Ready = 2,
        [Description("Получен")]
        Received = 3,
        [Description("Отменен")]
        Canceled = 4
    }

    public class Order
    {
        public int Id { get; set; }
        public long Date { get; set; }

        [NotMapped]
        public DateTime DateHandler
        {
            get
            {
                return Utilities.UnixTimeStampToDateTime(Date);
            }
            set
            {
                Date = Utilities.DateTimeToUnixTimeStamp(value);
            }
        }

        public OrderStatus Status { get; set; }

        public virtual ICollection<OrderComponent> OrderComponents { get; private set; } = new ObservableCollection<OrderComponent>();
    }
}
