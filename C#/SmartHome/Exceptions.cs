#nullable enable
using System;

namespace SmartHome;

/// <summary>
/// Исключение предметной области: устройство недоступно или отключено от сети.
/// </summary>
public class DeviceOfflineException : Exception
{
    public string DeviceName { get; }

    public DeviceOfflineException(string deviceName, string message)
        : base($"[Сбой сети]: Устройство '{deviceName}' — {message}")
    {
        DeviceName = deviceName;
    }
}

/// <summary>
/// Исключение предметной области: некорректный параметр конфигурации.
/// </summary>
public class InvalidParameterException : ArgumentException
{
    public string ParameterName { get; }

    public InvalidParameterException(string paramName, string message)
        : base($"[Ошибка валидации]: Параметр '{paramName}' — {message}")
    {
        ParameterName = paramName;
    }
}
