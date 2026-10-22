#nullable enable
using System;

namespace SmartHome;

public class TemperatureSensor : BaseDevice
{
    public double Temperature { get; set; }
    public string SerialNumber { get; }

    // Конструктор с параметрами: вызов базового конструктора через : base(...)
    public TemperatureSensor(string name, Room room, double temp, string serial)
        : base(name, room)
    {
        Temperature = temp;
        SerialNumber = serial;
        Console.WriteLine($"[TemperatureSensor] Конструктор датчика '{Name}', S/N={SerialNumber}");
    }

    // Демонстрация this: вызов другого конструктора этого же класса
    public TemperatureSensor(string name, Room room)
        : this(name, room, 20.0, "SN-DEFAULT")
    {
    }

    public override int PollInterval => 30;

    // Переопределение с ВЫЗОВОМ метода базового класса: base.Describe()
    public override string Describe() =>
        $"{base.Describe()} -> [Температура: {Temperature:F1} °C, S/N: {SerialNumber}]";

    // Поверхностная копия через MemberwiseClone (делят общую комнату Room)
    public TemperatureSensor ShallowCopy()
    {
        var copy = (TemperatureSensor)MemberwiseClone();
        copy.Id = NextId();
        return copy;
    }

    // Глубокая копия (создаёт собственный экземпляр Room)
    public TemperatureSensor DeepCopy()
    {
        var copy = (TemperatureSensor)MemberwiseClone();
        copy.Id = NextId();
        copy.Room = new Room(Room.Name); // Новый независимый объект
        return copy;
    }

    // Сравнение объектов по содержимому (Equals и GetHashCode)
    public override bool Equals(object? obj)
    {
        if (obj is TemperatureSensor other)
        {
            return SerialNumber == other.SerialNumber;
        }
        return false;
    }

    public override int GetHashCode() => SerialNumber.GetHashCode();
}
