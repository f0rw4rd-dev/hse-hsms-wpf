using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HardwareStore.Models
{
    public class Supply
    {
        public int Id { get; set; }
        public float SupplyPrice { get; set; }
        public int Amount { get; set; }
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

        public int SupplierId { get; set; }
        public virtual Supplier Supplier { get; set; } = null!;

        public int ComponentId { get; set; }
        public virtual Component Component { get; set; } = null!;

        public int WarehouseId { get; set; }
        public virtual Warehouse Warehouse { get; set; } = null!;
    }
}
