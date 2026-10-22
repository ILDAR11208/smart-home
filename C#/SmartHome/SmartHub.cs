#nullable enable
using System;

namespace SmartHome;

/// <summary>
/// Главный контроллер умного дома (SmartHub).
/// Демонстрирует:
/// 1. Конфигурирование поведения через объект поведения (стратегию ISecurityPolicy).
/// 2. Работу через контракт IControllable без знания классов.
/// 3. Проверку типов во время выполнения через is и as.
/// </summary>
public class SmartHub
{
    public string Name { get; }
    private ISecurityPolicy _policy; // Объект поведения

    // Статическое конфигурирование
    public SmartHub(string name, ISecurityPolicy policy)
    {
        Name = name;
        _policy = policy;
        Console.WriteLine($"[SmartHub] Хаб '{Name}' запущен. Активная политика: {_policy.PolicyName}");
    }

    // Динамическое конфигурирование: смена поведения во время работы
    public void SetPolicy(ISecurityPolicy newPolicy)
    {
        Console.WriteLine($"\n[SmartHub] Смена политики: '{_policy.PolicyName}' -> '{newPolicy.PolicyName}'");
        _policy = newPolicy;
    }

    public void RaiseAlarm(string deviceName, int severity)
    {
        Console.WriteLine($"[SmartHub] Событие тревоги! Передача объекту политики...");
        _policy.OnAlarm(deviceName, severity);
    }

    // 2. Использование интерфейса
    public void SendEmergencyCommand(IControllable device, string command)
    {
        Console.WriteLine("  [SmartHub -> IControllable] Отправка команды через интерфейс...");
        device.ExecuteCommand(command);
    }

    // 4. Проверка типа через is и as
    public void TryToggleDevice(BaseDevice device)
    {
        Console.WriteLine($"  Проверка поддержки управления для '{device.Name}'...");

        // Проверка через ключевое слово is
        if (device is IControllable controllable)
        {
            Console.WriteLine("  -> Проверка (is IControllable): True! Устройство поддерживает управление.");
            if (controllable.IsActive)
            {
                controllable.TurnOff();
            }
            else
            {
                controllable.TurnOn();
            }
        }
        else
        {
            // Проверка через as
            var maybe = device as IControllable;
            Console.WriteLine($"  -> Проверка (device as IControllable): {(maybe is null ? "null" : "OK")}. Устройство является пассивным.");
        }
    }
}
