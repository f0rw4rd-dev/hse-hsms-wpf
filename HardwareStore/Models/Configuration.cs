using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HardwareStore.Models
{
    [Index(nameof(ConfigurationId), nameof(ComponentId), IsUnique = true)]
    public class Configuration
    {
        public int Id { get; set; }
        public int ConfigurationId { get; set; }
        public int Amount { get; set; }

        public int ComponentId { get; set; }
        public virtual Component Component { get; set; } = null!;
    }
}
