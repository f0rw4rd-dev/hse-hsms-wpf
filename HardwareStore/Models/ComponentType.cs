using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;

namespace HardwareStore.Models
{
    [Index(nameof(Name), IsUnique = true)]
    public class ComponentType
    {
        public int Id { get; set; }

        [StringLength(64)]
        public required string Name { get; set; }
        public virtual ICollection<Component> Components { get; private set; } = new ObservableCollection<Component>();
    }
}
