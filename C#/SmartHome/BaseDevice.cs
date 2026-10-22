#nullable enable
using System;

namespace SmartHome;

/// <summary>
/// Абстрактный базовый класс устройства (по маске Base*).
/// </summary>
public abstract class BaseDevice
{
    private static int _deviceCounter = 0;

    public int Id { get; protected set; }
    public string Name { get; protected set; }
    public Room Room { get; set; }
    public bool IsOnline { get; set; } = true;

    public static int NextId() => ++_deviceCounter;

    protected BaseDevice(string name, Room room)
    {
        Id = NextId();
        Name = name;
        Room = room;
    }

    protected string Header() =>
        $"[ID {Id}] {Name} ({Room.Name}, {(IsOnline ? "Онлайн" : "ОФЛАЙН")})";

    // Раннее связывание: невиртуальный метод базового класса
    public string GetDeviceType() => "Базовое устройство умного дома";

    // Позднее связывание: виртуальный метод
    public virtual string Describe() => $"{Header()}, опрос каждые {PollInterval} сек.";

    public abstract int PollInterval { get; }

    // Проверка правила предметной области: устройство должно быть онлайн
    public void Ping()
    {
        if (!IsOnline)
        {
            throw new DeviceOfflineException(Name, "устройство не отвечает на пинг-запросы!");
        }
        Console.WriteLine($"  [Ping OK] Устройство '{Name}' успешно ответило.");
    }

    public override string ToString() => Describe();
}
