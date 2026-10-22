using System.Runtime.CompilerServices;
using SmartHome;

Console.OutputEncoding = System.Text.Encoding.UTF8;

// ===================================================================
Console.WriteLine("=== 1. КОМПОЗИЦИЯ, АГРЕГАЦИЯ И ПРОВЕРКА ПРАВИЛ ===\n");
// ===================================================================

// Создаём датчик (живёт независимо от дома)
var sensor = new Sensor("Термометр-01", 22.5f);
Console.WriteLine($"  {sensor}\n");

// Создаём дом — контроллер создаётся внутри (КОМПОЗИЦИЯ)
var house = new House("ул. Пушкина, д. 10", "3.1.4");
Console.WriteLine();

// Привязываем датчик к дому (АГРЕГАЦИЯ)
house.BindSensor(sensor);
Console.WriteLine();

// Нормальная работа
house.UpdateClimate();
Console.WriteLine();

// Отключаем датчик — проверка правил
sensor.IsOnline = false;
house.UpdateClimate();
Console.WriteLine();

// «Уничтожаем» дом — убираем ссылку
house = null!;
Console.WriteLine("Дом удалён (ссылка обнулена).");
Console.WriteLine($"Датчик всё ещё существует: {sensor}");
Console.WriteLine("  → Это доказывает агрегацию: датчик живёт независимо от дома.\n");

// ===================================================================
Console.WriteLine("=== 2. ССЫЛКИ И КОПИИ ===\n");
// ===================================================================

// --- 2a. Ссылочный тип (class) ---
Console.WriteLine("--- Ссылочный тип (class Sensor) ---");
var sensorA = new Sensor("Влажность-01", 55.0f);
var sensorB = sensorA;   // обе переменные ссылаются на ОДИН объект

Console.WriteLine($"  sensorA: {sensorA}");
Console.WriteLine($"  sensorB: {sensorB}");

sensorB.SetValue(99.9f);
Console.WriteLine("\n  Изменили значение через sensorB на 99.9:");
Console.WriteLine($"  sensorA: {sensorA}");
Console.WriteLine($"  sensorB: {sensorB}");
Console.WriteLine("  → Оба изменились, потому что class — ссылочный тип.\n");

// --- 2b. Значимый тип (struct) ---
Console.WriteLine("--- Значимый тип (struct Money) ---");
var original = new Money { Rubles = 100, Kopecks = 50 };
var copy = original;   // создаётся КОПИЯ

Console.WriteLine($"  Оригинал: {original}");
Console.WriteLine($"  Копия:    {copy}");

copy.Rubles = 999;
copy.Kopecks = 0;
Console.WriteLine("\n  Изменили копию на 999 руб. 0 коп.:");
Console.WriteLine($"  Оригинал: {original}");
Console.WriteLine($"  Копия:    {copy}");
Console.WriteLine("  → Оригинал не изменился, потому что struct — значимый тип.");
Console.WriteLine("    При присваивании struct копируются все поля (побитовая копия).\n");

// ===================================================================
Console.WriteLine("=== 3. ОСВОБОЖДЕНИЕ РЕСУРСА (IDisposable + using) ===\n");
// ===================================================================

using (var log = new IssueLog("Аварии отопления"))
{
    log.Write("Котёл перегрелся в 14:30");
    log.Write("Давление упало ниже нормы");
    Console.WriteLine("  (выходим из блока using — Dispose вызовется автоматически)");
}

Console.WriteLine("  → Dispose() вызван автоматически при выходе из блока using.");
Console.WriteLine("    Это аналог RAII / деструктора в C++ для управления ресурсами.\n");

// ===================================================================
Console.WriteLine("=== 4. СБОРЩИК МУСОРА ===\n");
// ===================================================================

var weakRef = CreateTemporary();

Console.WriteLine("  Объект создан во вспомогательном методе и вышел из области видимости.");
Console.WriteLine("  Вызываем GC.Collect() + GC.WaitForPendingFinalizers()...\n");

GC.Collect();
GC.WaitForPendingFinalizers();
GC.Collect();

if (weakRef.TryGetTarget(out var alive))
{
    Console.WriteLine($"  Объект ещё жив: {alive}");
}
else
{
    Console.WriteLine("  Объект был собран сборщиком мусора (WeakReference.TryGetTarget → false).");
}

Console.WriteLine();
Console.WriteLine("  Сравнение с C++:");
Console.WriteLine("    • В C++ деструктор вызывается детерминированно:");
Console.WriteLine("      – для стековых объектов — при выходе из области видимости;");
Console.WriteLine("      – для кучи — при вызове delete.");
Console.WriteLine("    • В C# (CLR) точный момент уничтожения объекта НЕ определён.");
Console.WriteLine("      Сборщик мусора сам решает, когда освободить память.");
Console.WriteLine("      Финализатор (~Sensor) может быть вызван значительно позже");
Console.WriteLine("      или не вызван вовсе при завершении программы.");
Console.WriteLine("    • Для детерминированного освобождения ресурсов в C# используют");
Console.WriteLine("      интерфейс IDisposable + конструкцию using (см. раздел 3).");

/// <summary>
/// Создаёт временный Sensor и возвращает слабую ссылку на него.
/// Атрибут NoInlining гарантирует, что локальная переменная
/// не останется на стеке после возврата.
/// </summary>
[MethodImpl(MethodImplOptions.NoInlining)]
static WeakReference<Sensor> CreateTemporary()
{
    var temp = new Sensor("Временный-GC", 0.0f);
    return new WeakReference<Sensor>(temp);
}
