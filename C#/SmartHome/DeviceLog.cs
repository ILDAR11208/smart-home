#nullable enable
using System;

namespace SmartHome;

public class DeviceLog : IDisposable
{
    private readonly string _title;

    public DeviceLog(string title)
    {
        _title = title;
        Console.WriteLine($"  [+] Журнал '{_title}' открыт.");
    }

    public void Log(string message)
    {
        Console.WriteLine($"    [{_title}] {message}");
    }

    public void Dispose()
    {
        Console.WriteLine($"  [-] Журнал '{_title}' закрыт и ресурсы освобождены.");
    }
}
