namespace SmartHome;

/// <summary>
/// Журнал проблем — демонстрация паттерна IDisposable + using.
/// </summary>
public class IssueLog : IDisposable
{
    private readonly string _title;

    public IssueLog(string title)
    {
        _title = title;
        Console.WriteLine($"[+] журнал открыт: {_title}");
    }

    /// <summary>Записать строку в журнал.</summary>
    public void Write(string message)
    {
        Console.WriteLine($"  [{_title}] {message}");
    }

    /// <summary>Освобождение ресурса.</summary>
    public void Dispose()
    {
        Console.WriteLine($"[-] журнал закрыт: {_title}");
    }

    public override string ToString() => $"Журнал '{_title}'";
}
