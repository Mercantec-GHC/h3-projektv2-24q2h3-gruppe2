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
    public class UserColorsController : ControllerBase
    {
        private readonly DataContext _context;

        public UserColorsController(DataContext context)
        {
            _context = context;
        }

        [HttpGet]
        public async Task<ActionResult<List<UserColors>>> GetAllUserColors()
        {
            var userColors = await _context.userColors.ToListAsync();

            return Ok(userColors);
        }
    }
}
