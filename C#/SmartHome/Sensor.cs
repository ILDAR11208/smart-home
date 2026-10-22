namespace SmartHome;

/// <summary>
/// Датчик умного дома (агрегируемый объект).
/// </summary>
public class Sensor
{
    private readonly string _name;
    private float _currentValue;
    private bool _isOnline;

    public Sensor(string name, float initialValue)
    {
        _name = name;
        _currentValue = initialValue;
        _isOnline = true;
        Console.WriteLine($"[Конструктор] Датчик '{_name}' создан.");
    }

    /// <summary>
    /// Финализатор — аналог деструктора C++.
    /// Вызывается сборщиком мусора, момент вызова не определён.
    /// </summary>
    ~Sensor()
    {
        Console.WriteLine($"[Деструктор] Датчик '{_name}' уничтожен.");
    }

    /// <summary>Название датчика.</summary>
    public string Title => _name;

    /// <summary>Статус подключения.</summary>
    public bool IsOnline
    {
        get => _isOnline;
        set
        {
            _isOnline = value;
            Console.WriteLine(_isOnline
                ? $"  Датчик '{_name}' подключён."
                : $"  Датчик '{_name}' отключён.");
        }
    }

    /// <summary>Считать текущее значение с датчика.</summary>
    public float ReadValue()
    {
        Console.WriteLine($"  Датчик '{_name}': текущее значение = {_currentValue}");
        return _currentValue;
    }

    /// <summary>Установить значение (для демонстрации).</summary>
    public void SetValue(float value) => _currentValue = value;

    public override string ToString() =>
        $"Датчик '{_name}' [значение={_currentValue}, " +
        $"{(_isOnline ? "онлайн" : "офлайн")}]";
}
