#nullable enable
using System;
using SmartHome;

Console.OutputEncoding = System.Text.Encoding.UTF8;

Console.WriteLine("==================================================================");
Console.WriteLine("       ЛАБОРАТОРНАЯ РАБОТА № 5: ПОЛИМОРФИЗМ И ИНТЕРФЕЙСЫ (C#)     ");
Console.WriteLine("==================================================================\n");

var livingRoom = new Room("Гостиная");
var bedroom = new Room("Спальня");

// =========================================================================
// 1. ИНТЕРФЕЙС И МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ
// =========================================================================
Console.WriteLine("=== 1. ИНТЕРФЕЙС И МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ===");
Console.WriteLine("Класс TemperatureSensor наследуется от BaseDevice и реализует IControllable, IComparable.");
Console.WriteLine("Класс MotionSensor наследуется от BaseDevice и реализует IControllable.\n");

var tempSensor = new TemperatureSensor("Термометр-Зал", livingRoom, 23.5, "SN-T-101");
var motionSensor = new MotionSensor("Радар-Зал", livingRoom, 6);

// =========================================================================
// 2. ИСПОЛЬЗОВАНИЕ ИНТЕРФЕЙСА (КОНТРАКТ)
// =========================================================================
Console.WriteLine("=== 2. ИСПОЛЬЗОВАНИЕ ИНТЕРФЕЙСА (РАБОТА ЧЕРЕЗ КОНТРАКТ) ===");
var hub = new SmartHub("Контроллер-Сервер", new StandardSecurityPolicy());

hub.SendEmergencyCommand(tempSensor, "CALIBRATE_ZERO");
hub.SendEmergencyCommand(motionSensor, "SET_GUARD_MODE");

// =========================================================================
// 3. РАННЕЕ И ПОЗДНЕЕ СВЯЗЫВАНИЕ (new vs override)
// =========================================================================
Console.WriteLine("\n=== 3. РАННЕЕ И ПОЗДНЕЕ СВЯЗЫВАНИЕ (new vs override) ===");
BaseDevice polyDevice = new MotionSensor("Охранный-Радар", bedroom, 8);

// Раннее связывание (метод скрыт словом new):
Console.WriteLine("Вызов через переменную базового типа BaseDevice:");
Console.WriteLine($"  1) Невиртуальный метод (new): \"{polyDevice.GetDeviceType()}\"");
Console.WriteLine("     -> Выбрана версия BaseDevice, так как выбор сделан на этапе компиляции (раннее связывание)!");

// Позднее связывание (override):
Console.WriteLine($"  2) Виртуальный метод (override): \"{polyDevice.Describe()}\"");
Console.WriteLine("     -> Выбрана версия MotionSensor по фактическому типу объекта во время работы (позднее связывание)!\n");

// =========================================================================
// 4. ПРОВЕРКА ТИПА (is и as)
// =========================================================================
Console.WriteLine("=== 4. ПРОВЕРКА ТИПА (is и as) ===");
var display = new PassiveDisplay("Инфо-Табло-01", livingRoom, "Температура: +23.5 C");

Console.WriteLine("Попытка переключить устройство с поддержкой IControllable:");
hub.TryToggleDevice(polyDevice);

Console.WriteLine("\nПопытка переключить пассивное табло:");
hub.TryToggleDevice(display);

// =========================================================================
// 5. КОНФИГУРИРОВАНИЕ ОБЪЕКТА (ОБЪЕКТ ПОВЕДЕНИЯ)
// =========================================================================
Console.WriteLine("\n=== 5. КОНФИГУРИРОВАНИЕ ОБЪЕКТА (ОБЪЕКТ ПОВЕДЕНИЯ) ===");
Console.WriteLine("-- 5.1. Статическое конфигурирование (задано при создании) --");
hub.RaiseAlarm("Входная дверь", 2);

Console.WriteLine("\n-- 5.2. Динамическое конфигурирование (смена во время работы) --");
hub.SetPolicy(new StrictSecurityPolicy());
hub.RaiseAlarm("Окно спальни", 5);

hub.SetPolicy(new SilentSecurityPolicy());
hub.RaiseAlarm("Движение во дворе", 1);
Console.WriteLine("-> Поведение хаба меняется за счет подстановки разных объектов поведения!\n");

// =========================================================================
// 6. СТАНДАРТНЫЙ ИНТЕРФЕЙС IComparable<T>
// =========================================================================
Console.WriteLine("=== 6. СТАНДАРТНЫЙ ИНТЕРФЕЙС IComparable<T> (СОРТИРОВКА) ===");
var sensors = new TemperatureSensor[]
{
    new TemperatureSensor("Термометр-Балкон", livingRoom, -5.5, "SN-03"),
    new TemperatureSensor("Термометр-Гостиная", livingRoom, 24.0, "SN-01"),
    new TemperatureSensor("Термометр-Серверная", livingRoom, 18.2, "SN-02")
};

Console.WriteLine("Список датчиков ДО сортировки:");
foreach (var s in sensors) Console.WriteLine($"  {s.Name}: {s.Temperature:F1} C");

Array.Sort(sensors); // Сортировка использует IComparable<TemperatureSensor>

Console.WriteLine("\nСписок датчиков ПОСЛЕ сортировки (Array.Sort по возрастанию температуры):");
foreach (var s in sensors) Console.WriteLine($"  {s.Name}: {s.Temperature:F1} C");

// =========================================================================
// 7. ИСКЛЮЧЕНИЯ ПРЕДМЕТНОЙ ОБЛАСТИ И БЛОК finally
// =========================================================================
Console.WriteLine("\n=== 7. ИСКЛЮЧЕНИЯ ПРЕДМЕТНОЙ ОБЛАСТИ (try / catch / finally) ===");

// 7а. Исключение DeviceOfflineException
Console.WriteLine("\n--- 7а. Ошибка сети (DeviceOfflineException) ---");
try
{
    tempSensor.IsOnline = false; // Отключаем
    Console.WriteLine("Опрашиваем отключенный датчик через Ping()...");
    tempSensor.Ping();
}
catch (DeviceOfflineException ex)
{
    Console.WriteLine($"  [CATCH СЕТИ]: Перехвачено исключение для '{ex.DeviceName}'!");
    Console.WriteLine($"  Сообщение: {ex.Message}");
}
finally
{
    Console.WriteLine("  [FINALLY]: Блок завершения выполнен (гарантированное освобождение ресурсов при любом исходе).");
}

// 7б. Исключение InvalidParameterException
Console.WriteLine("\n--- 7б. Ошибка валидации (InvalidParameterException) ---");
try
{
    Console.WriteLine("Попытка установить температуру 150 C (выше нормы)...");
    tempSensor.Temperature = 150.0;
}
catch (InvalidParameterException ex)
{
    Console.WriteLine($"  [CATCH ПАРАМЕТРА]: Перехвачена ошибка валидации '{ex.ParameterName}'!");
    Console.WriteLine($"  Сообщение: {ex.Message}");
}
finally
{
    Console.WriteLine("  [FINALLY]: Проверка параметров завершена.");
}

Console.WriteLine("\n==================================================================");
Console.WriteLine("                   ПРОГРАММА УСПЕШНО ЗАВЕРШЕНА                    ");
Console.WriteLine("==================================================================");
