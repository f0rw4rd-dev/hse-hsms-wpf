using HardwareStore.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HardwareStore.Models
{
    public class Component
    {
        public int Id { get; set; }

        public int ComponentTypeId { get; set; }
        public virtual ComponentType ComponentType { get; set; } = null!;

        [StringLength(256)]
        public required string Name { get; set; }
        public int Warranty { get; set; }

        public virtual ICollection<ComponentDetail> ComponentDetails { get; private set; } = new ObservableCollection<ComponentDetail>();
        public virtual ICollection<ComponentStorage> ComponentStorages { get; private set; } = new ObservableCollection<ComponentStorage>();
        public virtual ICollection<OrderComponent> OrderComponents { get; private set; } = new ObservableCollection<OrderComponent>();
        public virtual ICollection<Configuration> Configurations { get; private set; } = new ObservableCollection<Configuration>();
        public virtual ICollection<Supply> Supplies { get; private set; } = new ObservableCollection<Supply>();
    }
}
