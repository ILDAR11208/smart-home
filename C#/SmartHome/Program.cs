#nullable enable
using System;
using static System.Math; // Разумное использование using: статические члены без имени класса
using DeviceList = System.Collections.Generic.List<SmartHome.BaseDevice>; // Псевдоним длинного типа
using SmartHome;

Console.OutputEncoding = System.Text.Encoding.UTF8;

Console.WriteLine("==================================================================");
Console.WriteLine("     ЛАБОРАТОРНАЯ РАБОТА № 4: НАСЛЕДОВАНИЕ И ПОЛИМОРФИЗМ (C#)     ");
Console.WriteLine("==================================================================\n");

// =========================================================================
// 1. ИЕРАРХИЯ КЛАССОВ И ВЫЗОВ КОНСТРУКТОРОВ
// =========================================================================
Console.WriteLine("=== 1. ИЕРАРХИЯ КЛАССОВ И ВЫЗОВ КОНСТРУКТОРОВ БАЗЫ ===");
var kitchen = new Room("Кухня");
var tempSensor = new TemperatureSensor("Термометр-Кухня", kitchen, 23.5, "SN-TMP-101");
Console.WriteLine($"-> Создан объект: {tempSensor}");
Console.WriteLine("   (В конструкторе вызван base(name, room) для базовой части)\n");

// =========================================================================
// 2. ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ (override) И sealed
// =========================================================================
Console.WriteLine("=== 2. ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ (С ВЫЗОВОМ БАЗЫ И БЕЗ) ===");
var balcony = new Room("Балкон");
var tempBalcony = new TemperatureSensor("Термометр-Балкон", balcony, -8.0, "SN-TMP-202");
var motionBalcony = new MotionSensor("Радар-Балкон", balcony, 4);

Console.WriteLine("\n1) Переопределение С вызовом базового класса (base.Describe()):");
Console.WriteLine($"   {tempBalcony.Describe()}");

Console.WriteLine("\n2) Переопределение БЕЗ вызова базового класса (полная замена):");
Console.WriteLine($"   {motionBalcony.Describe()}");
Console.WriteLine("   (Класс MotionSensor объявлен как sealed — запрет дальнейшего наследования)\n");

// =========================================================================
// 3. ПОВЕРХНОСТНАЯ И ГЛУБОКАЯ КОПИЯ
// =========================================================================
Console.WriteLine("=== 3. ПОВЕРХНОСТНАЯ И ГЛУБОКАЯ КОПИЯ ===");

// 3а. Поверхностная копия (MemberwiseClone)
Console.WriteLine("\n--- 3а. Поверхностная копия (ShallowCopy / MemberwiseClone) ---");
var roomLiving = new Room("Гостиная");
var sensorOrig = new TemperatureSensor("Оригинал-Датчик", roomLiving, 21.0, "SN-ORIG-01");
var shallowCopy = sensorOrig.ShallowCopy();

Console.WriteLine($"ДО изменения:      Оригинал={sensorOrig.Room.Name}, Копия={shallowCopy.Room.Name}");
shallowCopy.RenameRoom("Столовая"); // Меняем комнату у копии
Console.WriteLine($"ПОСЛЕ изменения:   Оригинал={sensorOrig.Room.Name}, Копия={shallowCopy.Room.Name}");
Console.WriteLine("-> Обе переменные ссылаются на ОДИН И ТОТ ЖЕ объект Room! Это поверхностная копия.");

// 3б. Глубокая копия
Console.WriteLine("\n--- 3б. Глубокая копия (DeepCopy) ---");
var deepCopy = sensorOrig.DeepCopy();
Console.WriteLine($"ДО изменения:      Оригинал={sensorOrig.Room.Name}, ГлубокаяКопия={deepCopy.Room.Name}");
deepCopy.RenameRoom("Спальня"); // Меняем комнату у глубокой копии
Console.WriteLine($"ПОСЛЕ изменения:   Оригинал={sensorOrig.Room.Name}, ГлубокаяКопия={deepCopy.Room.Name}");
Console.WriteLine("-> Оригинал НЕ изменился! У копии собственный экземпляр Room. Это глубокая копия.\n");

// =========================================================================
// 4. СРАВНЕНИЕ ПО СОДЕРЖИМОМУ (Equals и GetHashCode)
// =========================================================================
Console.WriteLine("=== 4. СРАВНЕНИЕ ПО СОДЕРЖИМОМУ (Equals и GetHashCode) ===");
var s1 = new TemperatureSensor("Датчик А", new Room("Зал"), 20.0, "SN-777");
var s2 = new TemperatureSensor("Датчик Б (другое имя и комната)", new Room("Склад"), 25.0, "SN-777");
var s3 = new TemperatureSensor("Датчик В", new Room("Зал"), 20.0, "SN-888");

Console.WriteLine($"  s1 == s2 (по ссылкам): {ReferenceEquals(s1, s2)} (разные объекты)");
Console.WriteLine($"  s1.Equals(s2) (по серийному номеру): {s1.Equals(s2)} (совпадает S/N)");
Console.WriteLine($"  s1.Equals(s3) (по серийному номеру): {s1.Equals(s3)} (разные S/N)");
Console.WriteLine($"  Хеш-коды: s1={s1.GetHashCode()}, s2={s2.GetHashCode()}, s3={s3.GetHashCode()}\n");

// =========================================================================
// 5. ИСПОЛЬЗОВАНИЕ this И СТАТИЧЕСКИЕ ЧЛЕНЫ
// =========================================================================
Console.WriteLine("=== 5. ИСПОЛЬЗОВАНИЕ this И СТАТИЧЕСКИЕ ЧЛЕНЫ ===");
// Вызов другого конструктора через : this(...)
var defaultSensor = new TemperatureSensor("Датчик-Авто", new Room("Коридор"));
Console.WriteLine($"  Конструктор по умолчанию через this: {defaultSensor}");

// Передача this в другой метод
var garage = new Room("Гараж");
defaultSensor.AttachToRoom(garage);

// Статические члены
Console.WriteLine($"  Всего создано устройств (BaseDevice.TotalDevices): {BaseDevice.TotalDevices}");
Console.WriteLine($"  Следующий номер (BaseDevice.NextId()): {BaseDevice.NextId()}\n");

// =========================================================================
// 6. РАЗУМНОЕ ИСПОЛЬЗОВАНИЕ using
// =========================================================================
Console.WriteLine("=== 6. РАЗУМНОЕ ИСПОЛЬЗОВАНИЕ using ===");
// using static (использован в начале файла: using static System.Math)
double roundedTemp = Round(23.456, 1); // Math.Round без имени класса
Console.WriteLine($"  using static: Round(23.456, 1) = {roundedTemp}");

// using var (автоматический вызов Dispose в конце области видимости)
{
    using var log = new DeviceLog("Системный аудит");
    log.Log("Зафиксировано превышение температуры на 1.5 градуса.");
    log.Log("Команда климат-контроля отправлена.");
}

// =========================================================================
// 7. ПОЛИМОРФНЫЙ СПИСОК (псевдоним DeviceList)
// =========================================================================
Console.WriteLine("\n=== 7. ПОЛИМОРФНЫЙ СПИСОК (DeviceList) ===");
var house = new Room("Коттедж");
var devices = new DeviceList
{
    new TemperatureSensor("Термометр холла", house, 21.5, "SN-H-01"),
    new MotionSensor("Датчик движения холла", house, 7),
    new TemperatureSensor("Термометр кухни", house, 24.0, "SN-K-02")
};

Console.WriteLine("Обход устройств через абстрактный базовый класс BaseDevice:");
foreach (var device in devices)
{
    Console.WriteLine($"  • {device.Describe()} [Интервал опроса: {device.PollInterval} сек.]");
}

Console.WriteLine("\n==================================================================");
Console.WriteLine("                   ПРОГРАММА УСПЕШНО ЗАВЕРШЕНА                    ");
Console.WriteLine("==================================================================");
