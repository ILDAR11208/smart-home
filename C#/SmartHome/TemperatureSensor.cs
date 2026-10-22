#nullable enable
using System;

namespace SmartHome;

/// <summary>
/// Термометр.
/// Множественное наследование: BaseDevice + IControllable + IComparable.
/// </summary>
public class TemperatureSensor : BaseDevice, IControllable, IComparable<TemperatureSensor>
{
    private double _temperature;
    public string SerialNumber { get; }
    public bool IsActive { get; private set; } = true;

    public double Temperature
    {
        get => _temperature;
        set
        {
            if (value < -50.0 || value > 100.0)
            {
                throw new InvalidParameterException("температура", $"значение {value:F1} C выходит за пределы [-50, +100] C!");
            }
            _temperature = value;
        }
    }

    public TemperatureSensor(string name, Room room, double temp, string serial)
        : base(name, room)
    {
        SerialNumber = serial;
        Temperature = temp;
    }

    public override int PollInterval => 30;

    // Раннее связывание: ключевое слово new скрывает невиртуальный метод базы
    public new string GetDeviceType() => "Прецизионный термометр";

    // Позднее связывание: переопределение виртуального метода
    public override string Describe() =>
        $"{base.Describe()} -> [Температура: {Temperature:F1} °C, S/N: {SerialNumber}]";

    // Реализация контракта IControllable
    public void TurnOn()
    {
        IsActive = true;
        Console.WriteLine($"  [IControllable] Термометр '{Name}' включён.");
    }

    public void TurnOff()
    {
        IsActive = false;
        Console.WriteLine($"  [IControllable] Термометр '{Name}' выключен.");
    }

    public void ExecuteCommand(string command)
    {
        Console.WriteLine($"  [IControllable] Термометр '{Name}' выполнил команду: {command}");
    }

    // 5. Стандартный интерфейс IComparable<T>: сортировка термометров по температуре
    public int CompareTo(TemperatureSensor? other)
    {
        if (other is null) return 1;
        return Temperature.CompareTo(other.Temperature);
    }
}
