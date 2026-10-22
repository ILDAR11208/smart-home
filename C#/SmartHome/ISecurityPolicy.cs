#nullable enable
using System;

namespace SmartHome;

/// <summary>
/// Интерфейс объекта поведения: стратегия реагирования на тревогу.
/// </summary>
public interface ISecurityPolicy
{
    string PolicyName { get; }
    void OnAlarm(string deviceName, int severity);
}

public class StandardSecurityPolicy : ISecurityPolicy
{
    public string PolicyName => "Стандартный режим (Дневной)";

    public void OnAlarm(string deviceName, int severity)
    {
        Console.WriteLine($"  [StandardSecurity] Предупреждение от '{deviceName}' (уровень {severity}): включен свет, подан мягкий сигнал.");
    }
}

public class StrictSecurityPolicy : ISecurityPolicy
{
    public string PolicyName => "Усиленный режим (Охрана периметра)";

    public void OnAlarm(string deviceName, int severity)
    {
        Console.WriteLine($"  [StrictSecurity] ВНИМАНИЕ! ТРЕВОГА от '{deviceName}' (уровень {severity}): замки заблокированы, включена сирена!");
    }
}

public class SilentSecurityPolicy : ISecurityPolicy
{
    public string PolicyName => "Ночной тихий режим (Push-уведомления)";

    public void OnAlarm(string deviceName, int severity)
    {
        Console.WriteLine($"  [SilentSecurity] Беззвучный режим: push-уведомление от '{deviceName}' отправлено на смартфон владельца.");
    }
}
