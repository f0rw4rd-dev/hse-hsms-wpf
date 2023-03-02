using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HardwareStore.Models;

namespace HardwareStore
{
    public struct PermissionOptions
    {
        public PermissionOptions() { }

        public PermissionOptions(bool CanAdd, bool CanEdit, bool CanDelete, bool CanView)
        {
            this.CanAdd = CanAdd;
            this.CanEdit = CanEdit;
            this.CanDelete = CanDelete;
            this.CanView = CanView;
        }

        public PermissionOptions(string permission)
        {
            if (permission.Length != 4 || (permission.Count(c => c == '0') + permission.Count(c => c == '1')) != 4)
                throw new ArgumentException("Permission string does not fit the format!");

            CanAdd = permission[0] == '1';
            CanEdit = permission[1] == '1';
            CanDelete = permission[2] == '1';
            CanView = permission[3] == '1';
        }

        public bool CanAdd { get; set; }
        public bool CanEdit { get; set; }
        public bool CanDelete { get; set; }
        public bool CanView { get; set; }
    }

    public class GroupPermissions
    {
        public static int UserId { get; set; }

        public static Group Group
        {
            get
            {
                using StoreContext context = new();

                User? user = context.Users.Find(UserId);

                return (user != null) ? user.Group : Group.Consultant;
            }
        }

        public static Dictionary<Group, GroupPermissions> permissions = new()
        {
            {
                Group.Consultant, new GroupPermissions
                {
                    Components = new("1111"),
                    ComponentDetails = new("1111"),
                    ComponentStorages = new("0101"),
                    ComponentTypes = new("0001"),
                    Configurations = new("1111"),
                    DetailTypes = new("0001"),
                    Orders = new("1111"),
                    OrderComponents = new("1111"),
                    Suppliers = new("0001"),
                    Supplies = new("0001"),
                    Warehouses = new("0001"),
                    Users = new("0000")
                }
            },
            {
                Group.PurchasingManager, new GroupPermissions
                {
                    Components = new("0001"),
                    ComponentDetails = new("0001"),
                    ComponentStorages = new("0001"),
                    ComponentTypes = new("0001"),
                    Configurations = new("0001"),
                    DetailTypes = new("0001"),
                    Orders = new("0001"),
                    OrderComponents = new("0001"),
                    Suppliers = new("1111"),
                    Supplies = new("1111"),
                    Warehouses = new("0001"),
                    Users = new("0000")
                }
            },
            {
                Group.WarehouseWorker, new GroupPermissions
                {
                    Components = new("0001"),
                    ComponentDetails = new("0001"),
                    ComponentStorages = new("1111"),
                    ComponentTypes = new("0001"),
                    Configurations = new("0001"),
                    DetailTypes = new("0001"),
                    Orders = new("0001"),
                    OrderComponents = new("0001"),
                    Suppliers = new("0001"),
                    Supplies = new("0001"),
                    Warehouses = new("1111"),
                    Users = new("0000")
                }
            },
            {
                Group.Analyst, new GroupPermissions
                {
                    Components = new("0001"),
                    ComponentDetails = new("0001"),
                    ComponentStorages = new("0001"),
                    ComponentTypes = new("0001"),
                    Configurations = new("0001"),
                    DetailTypes = new("0001"),
                    Orders = new("0001"),
                    OrderComponents = new("0001"),
                    Suppliers = new("0000"),
                    Supplies = new("0000"),
                    Warehouses = new("0001"),
                    Users = new("0000")
                }
            },
            {
                Group.Admin, new GroupPermissions
                {
                    Components = new("1111"),
                    ComponentDetails = new("1111"),
                    ComponentStorages = new("1111"),
                    ComponentTypes = new("1111"),
                    Configurations = new("1111"),
                    DetailTypes = new("1111"),
                    Orders = new("1111"),
                    OrderComponents = new("1111"),
                    Suppliers = new("1111"),
                    Supplies = new("1111"),
                    Warehouses = new("1111"),
                    Users = new("1111")
                }
            }
        };

        public PermissionOptions Components { get; set; }
        public PermissionOptions ComponentDetails { get; set; }
        public PermissionOptions ComponentStorages { get; set; }
        public PermissionOptions ComponentTypes { get; set; }
        public PermissionOptions Configurations { get; set; }
        public PermissionOptions DetailTypes { get; set; }
        public PermissionOptions Orders { get; set; }
        public PermissionOptions OrderComponents { get; set; }
        public PermissionOptions Suppliers { get; set; }
        public PermissionOptions Supplies { get; set; }
        public PermissionOptions Warehouses { get; set; }
        public PermissionOptions Users { get; set; }
    }
}
