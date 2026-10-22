#nullable enable
using System;

namespace SmartHome;

/// <summary>
/// Датчик движения.
/// sealed — запрет дальнейшего наследования (аналог final в C++ / Java).
/// </summary>
public sealed class MotionSensor : BaseDevice
{
    public bool MotionDetected { get; set; }
    public int Sensitivity { get; }

    public MotionSensor(string name, Room room, int sensitivity)
        : base(name, room)
    {
        Sensitivity = sensitivity;
        MotionDetected = false;
        Console.WriteLine($"[MotionSensor] Конструктор датчика движения '{Name}', чувств={Sensitivity}");
    }

    public override int PollInterval => 5;

    // Переопределение БЕЗ вызова метода базового класса (полная замена поведения)
    // Использует protected-метод Header()
    public override string Describe()
    {
        string status = MotionDetected ? "ТРЕВОГА (движение обнаружено!)" : "Спокойно (нет движения)";
        return $"Датчик движения: {Header()} -> [Статус: {status}, Чувствительность: {Sensitivity}/10]";
    }

    public MotionSensor ShallowCopy()
    {
        var copy = (MotionSensor)MemberwiseClone();
        copy.Id = NextId();
        return copy;
    }

    public MotionSensor DeepCopy()
    {
        var copy = (MotionSensor)MemberwiseClone();
        copy.Id = NextId();
        copy.Room = new Room(Room.Name);
        return copy;
    }
}
