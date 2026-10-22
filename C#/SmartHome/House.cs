namespace SmartHome;

/// <summary>
/// Умный дом.
/// Контроллер — композиция (создаётся внутри, живёт вместе с домом).
/// Датчик — агрегация (передаётся извне, живёт независимо).
/// </summary>
public class House
{
    private readonly string _address;
    private readonly Controller _controller;   // композиция
    private Sensor? _linkedSensor;             // агрегация

    public House(string address, string controllerFirmware)
    {
        _address = address;
        _controller = new Controller(controllerFirmware);   // композиция — создаём сами
        _linkedSensor = null;
        Console.WriteLine($"[Конструктор] Дом по адресу '{_address}' построен.");
    }

    ~House()
    {
        Console.WriteLine($"[Деструктор] Дом по адресу '{_address}' сносится.");
    }

    /// <summary>Адрес дома.</summary>
    public string Address => _address;

    /// <summary>Привязать внешний датчик (агрегация).</summary>
    public void BindSensor(Sensor? sensor)
    {
        _linkedSensor = sensor;
        if (sensor != null)
            Console.WriteLine($"  Датчик '{sensor.Title}' привязан к дому '{_address}'.");
        else
            Console.WriteLine($"  Датчик отвязан от дома '{_address}'.");
    }

    /// <summary>Обновить климат: считать данные с датчика и обработать.</summary>
    public void UpdateClimate()
    {
        Console.WriteLine($"  Дом '{_address}': обновление климата...");

        if (_linkedSensor == null)
        {
            Console.WriteLine("  Ошибка: датчик не привязан!");
            return;
        }

        if (!_linkedSensor.IsOnline)
        {
            Console.WriteLine($"  Ошибка: датчик '{_linkedSensor.Title}' офлайн!");
            return;
        }

        float value = _linkedSensor.ReadValue();
        _controller.ProcessData(value);
    }

    public override string ToString() =>
        $"Дом [адрес={_address}, контроллер={_controller}, " +
        $"датчик={(_linkedSensor != null ? _linkedSensor.ToString() : "нет")}]";
}
