namespace API.Stuff
{
    public class UserColors
    {
        public string Scans { get; set; }
        public int Id { get; set; }
        public string R { get; set; }
        public string G { get; set; }
        public string B { get; set; }
        public int UserId { get; set; }
    }
    public class AddColorRequest
    {
        public string R { get; set; }
    }
}
