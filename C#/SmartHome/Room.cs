#nullable enable
using System;

namespace SmartHome;

public class Room
{
    public string Name { get; set; }

    public Room(string name)
    {
        Name = name;
        Console.WriteLine($"  [Room] Создана комната: {Name}");
    }

    public Room(Room other)
    {
        Name = other.Name;
        Console.WriteLine($"  [Room] Скопирована комната: {Name}");
    }

    public void Report(BaseDevice device)
    {
        Console.WriteLine($"  [Room.Report] В комнате '{Name}' зарегистрировано устройство: {device.Name} (ID={device.Id})");
    }

    public override string ToString() => Name;
}
