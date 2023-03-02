using HardwareStore.Models;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HardwareStore.Models
{
    [Index(nameof(City), nameof(Street), nameof(House), IsUnique = true)]
    public class Warehouse
    {
        public int Id { get; set; }

        [StringLength(64)]
        public required string City { get; set; }

        [StringLength(64)]
        public required string Street { get; set; }

        [StringLength(8)]
        public required string House { get; set; }

        public int Zip { get; set; }
        public virtual ICollection<ComponentStorage> ComponentStorages { get; private set; } = new ObservableCollection<ComponentStorage>();
        public virtual ICollection<OrderComponent> OrderComponents { get; private set; } = new ObservableCollection<OrderComponent>();
        public virtual ICollection<Supply> Supplies { get; private set; } = new ObservableCollection<Supply>();
    }
}
