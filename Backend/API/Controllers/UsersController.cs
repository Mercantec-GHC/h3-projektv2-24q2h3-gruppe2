using API.Data;
using API.Stuff;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class UsersController : ControllerBase
    {
        private readonly DataContext _context;

        public UsersController(DataContext context)
        {
            _context = context;
        }

        [HttpGet]
        public async Task<ActionResult<List<User>>> GetAllUsers()
        {
            var users = await _context.Users.ToListAsync();
            
            return Ok(users);
        }
    
        [HttpGet("{id}")]
        public async Task<ActionResult<User>> GetUser(int id)
        {
            var user = await _context.Users.FindAsync(id);
            if (user is null)
                return BadRequest("User not found");

            return Ok(user);
        }
        [HttpPost]
        public async Task<ActionResult<List<User>>> AddUser(User user)
        {
            _context.Users.Add(user);
            await _context.SaveChangesAsync();

            return Ok(await _context.Users.ToListAsync());
        }
        
        [HttpPut]
        public async Task<ActionResult<List<User>>> UpdateUser(User updatedUser)
        {
            var dbUser = await _context.Users.FindAsync(updatedUser.Id);
            if (dbUser is null)
                return BadRequest("User not found");

            dbUser.Name = updatedUser.Name;
            dbUser.Password = updatedUser.Password;

            await _context.SaveChangesAsync();


            return Ok(await _context.Users.ToListAsync());
        }
    }
}
