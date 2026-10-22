#nullable enable
namespace SmartHome;

public class Room
{
    public string Name { get; set; }

    public Room(string name)
    {
        Name = name;
    }

    public override string ToString() => Name;
}
