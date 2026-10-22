#nullable enable
using System;

namespace SmartHome;

/// <summary>
/// Абстрактный базовый класс устройства умного дома.
/// </summary>
public abstract class BaseDevice
{
    private static int _deviceCounter = 0;

    public int Id { get; protected set; }
    public string Name { get; protected set; }
    public Room Room { get; set; }

    public static int NextId() => ++_deviceCounter;
    public static int TotalDevices => _deviceCounter;

    // Модификатор protected: метод нужен наследникам, но закрыт снаружи
    protected string Header() => $"[ID {Id}] {Name} (Комната: {Room.Name})";

    protected BaseDevice(string name, Room room)
    {
        Id = NextId();
        Name = name;
        Room = room;
        Console.WriteLine($"[BaseDevice] Конструктор базы '{Name}' ID={Id}");
    }

    // Чисто виртуальный метод / свойство
    public abstract int PollInterval { get; }

    // Виртуальный метод с реализацией по умолчанию
    public virtual string Describe() => $"{Header()}, опрос каждые {PollInterval} сек.";

    // Демонстрация this: передача текущего объекта другому объекту
    public void AttachToRoom(Room room)
    {
        room.Report(this); // передача this
    }

    public void RenameRoom(string newName)
    {
        Room.Name = newName;
    }

    public override string ToString() => Describe();
}
