using API.Stuff;
using Microsoft.EntityFrameworkCore;
using System.Security.Cryptography.Pkcs;

namespace API.Data
{
    public class DataContext : DbContext
    {
        public DataContext(DbContextOptions<DataContext> options) : base(options)
        {

        }

        public DbSet<User> Users { get; set; }
        public DbSet<UserColors> userColors { get; set; }
    }
}
