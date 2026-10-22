namespace SmartHome;

/// <summary>
/// Контроллер умного дома (композиция — создаётся внутри House).
/// </summary>
public class Controller
{
    private readonly string _firmwareVersion;
    private bool _hasActiveErrors;

    public Controller(string firmware)
    {
        _firmwareVersion = firmware;
        _hasActiveErrors = false;
        Console.WriteLine($"[Конструктор] Контроллер (версия {_firmwareVersion}) установлен.");
    }

    ~Controller()
    {
        Console.WriteLine("[Деструктор] Контроллер демонтирован и уничтожен.");
    }

    /// <summary>Версия прошивки.</summary>
    public string FirmwareVersion => _firmwareVersion;

    /// <summary>Есть ли активные ошибки.</summary>
    public bool HasErrors => _hasActiveErrors;

    /// <summary>Запуск диагностики.</summary>
    public void RunDiagnostics()
    {
        Console.WriteLine($"  Контроллер (v{_firmwareVersion}): диагностика пройдена, ошибок нет.");
        _hasActiveErrors = false;
    }

    /// <summary>Обработка данных с датчика.</summary>
    public void ProcessData(float sensorValue)
    {
        if (sensorValue < 0)
        {
            Console.WriteLine($"  Контроллер: значение {sensorValue} — включён режим обогрева.");
        }
        else
        {
            Console.WriteLine($"  Контроллер: значение {sensorValue} — режим ожидания.");
        }
    }

    public override string ToString() =>
        $"Контроллер [прошивка={_firmwareVersion}, ошибки={(_hasActiveErrors ? "да" : "нет")}]";
}
