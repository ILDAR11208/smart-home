#nullable enable
using System;

namespace SmartHome;

/// <summary>
/// Датчик движения (sealed).
/// Множественное наследование: BaseDevice + IControllable.
/// </summary>
public sealed class MotionSensor : BaseDevice, IControllable
{
    private int _sensitivity = 5;

    public bool MotionDetected { get; set; }
    public bool IsActive { get; private set; } = true;

    public int Sensitivity
    {
        get => _sensitivity;
        set
        {
            if (value < 1 || value > 10)
            {
                throw new InvalidParameterException("чувствительность", $"значение {value} недопустимо (норма от 1 до 10)!");
            }
            _sensitivity = value;
        }
    }

    public MotionSensor(string name, Room room, int sensitivity)
        : base(name, room)
    {
        Sensitivity = sensitivity;
    }

    public override int PollInterval => 5;

    public new string GetDeviceType() => "Охранный радар движения";

    public override string Describe()
    {
        string status = MotionDetected ? "ДВИЖЕНИЕ!" : "Спокойно";
        string armed = IsActive ? "На охране" : "Снят";
        return $"Радар движения: {Header()} -> [Режим: {armed}, Статус: {status}, Чувствительность: {Sensitivity}/10]";
    }

    public void TurnOn()
    {
        IsActive = true;
        Console.WriteLine($"  [IControllable] Радар '{Name}' поставлен на охрану.");
    }

    public void TurnOff()
    {
        IsActive = false;
        Console.WriteLine($"  [IControllable] Радар '{Name}' снят с охраны.");
    }

    public void ExecuteCommand(string command)
    {
        Console.WriteLine($"  [IControllable] Радар '{Name}' выполнил команду охраны: {command}");
    }
}
