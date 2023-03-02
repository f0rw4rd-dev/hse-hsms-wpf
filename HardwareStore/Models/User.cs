using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace HardwareStore.Models
{
    public enum Group : int
    {
        [Description("Продавец-консультант")]
        Consultant = 0,

        [Description("Менеджер по закупкам")]
        PurchasingManager = 1,

        [Description("Складской работник")]
        WarehouseWorker = 2,

        [Description("Аналитик")]
        Analyst = 3,

        [Description("Администратор")]
        Admin = 4,
    }

    public class User
    {
        public int Id { get; set; }
        public required string Password { get; set; }
        public long RegistrationDate { get; set; }
        public long? LastVisitDate { get; set; }
        public Group Group { get; set; }

        [NotMapped]
        public string RegistrationDateText
        {
            get
            {
                DateTime dateTime = Utilities.UnixTimeStampToDateTime(RegistrationDate);
                return dateTime.ToString("dd-MM-yyyy HH:mm");
            }
        }

        [NotMapped]
        public string LastVisitDateText
        {
            get
            {
                if (LastVisitDate == null)
                    return "";

                DateTime dateTime = Utilities.UnixTimeStampToDateTime((long)LastVisitDate);
                return dateTime.ToString("dd-MM-yyyy HH:mm");
            }
        }
    }
}
