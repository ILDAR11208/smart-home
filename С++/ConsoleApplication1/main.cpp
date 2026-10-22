#include "base_device.hpp"
#include "temperature_sensor.hpp"
#include "motion_sensor.hpp"
#include "passive_display.hpp"
#include "smart_hub.hpp"
#include "isecurity_policy.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <memory>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace smarthome;

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    std::cout << "==================================================================" << std::endl;
    std::cout << "       ЛАБОРАТОРНАЯ РАБОТА № 5: ПОЛИМОРФИЗМ И ИНТЕРФЕЙСЫ (C++)    " << std::endl;
    std::cout << "==================================================================" << std::endl;

    auto livingRoom = std::make_shared<Room>("Гостиная");
    auto bedroom = std::make_shared<Room>("Спальня");

    // =========================================================================
    // 1. ИНТЕРФЕЙС И МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ
    // =========================================================================
    std::cout << "\n=== 1. ИНТЕРФЕЙС И МНОЖЕСТВЕННОЕ НАСЛЕДОВАНИЕ ===" << std::endl;
    std::cout << "Классы TemperatureSensor и MotionSensor наследуются одновременно от:\n"
              << "  1) Абстрактного класса BaseDevice (наследуют состояние и базовые поля)\n"
              << "  2) Интерфейса IControllable (обязуются выполнить контракт удаленного управления)\n\n";

    TemperatureSensor tempDev("Термометр-1", livingRoom, 22.5, "SN-T-501");
    MotionSensor motionDev("Радар-1", livingRoom, 7);

    // =========================================================================
    // 2. ИСПОЛЬЗОВАНИЕ ИНТЕРФЕЙСА (КОНТРАКТ БЕЗ ЗНАНИЯ КОНКРЕТНЫХ КЛАССОВ)
    // =========================================================================
    std::cout << "\n=== 2. ИСПОЛЬЗОВАНИЕ ИНТЕРФЕЙСА (РАБОТА ЧЕРЕЗ КОНТРАКТ) ===" << std::endl;
    // Создаем хаб с начальной стандартной политикой (статическое конфигурирование)
    SmartHub hub("Центральный контроллер", std::make_unique<StandardSecurityPolicy>());

    // Функция хаба принимает IControllable& — она ничего не знает о датчиках!
    std::cout << "\nУправление термометром через интерфейс IControllable:" << std::endl;
    hub.SendEmergencyCommand(tempDev, "CALIBRATE");

    std::cout << "\nУправление радаром движения через интерфейс IControllable:" << std::endl;
    hub.SendEmergencyCommand(motionDev, "SET_ZONE_ALARM");

    // =========================================================================
    // 3. РАННЕЕ И ПОЗДНЕЕ СВЯЗЫВАНИЕ
    // =========================================================================
    std::cout << "\n=== 3. РАННЕЕ И ПОЗДНЕЕ СВЯЗЫВАНИЕ ===" << std::endl;
    std::unique_ptr<BaseDevice> polyDevice = std::make_unique<MotionSensor>("Охранный-Радар", bedroom, 8);

    std::cout << "Вызов через указатель на базовый класс (std::unique_ptr<BaseDevice>):\n";
    
    // Раннее связывание: невиртуальный метод выбирается во время компиляции по типу указателя BaseDevice*
    std::cout << "  1) Невиртуальный метод GetDeviceType():\n"
              << "     -> Результат: \"" << polyDevice->GetDeviceType() << "\" (выбрана версия BaseDevice!)\n";

    // Позднее связывание: виртуальный метод выбирается во время выполнения через vtable по типу объекта MotionSensor
    std::cout << "  2) Виртуальный метод Describe():\n"
              << "     -> Результат: \"" << polyDevice->Describe() << "\" (выбрана версия MotionSensor!)\n";

    // =========================================================================
    // 4. ПРОВЕРКА ТИПА ВО ВРЕМЯ ВЫПОЛНЕНИЯ (dynamic_cast)
    // =========================================================================
    std::cout << "\n=== 4. ПРОВЕРКА ТИПА ВО ВРЕМЯ ВЫПОЛНЕНИЯ (dynamic_cast) ===" << std::endl;
    PassiveDisplay display("Инфо-Табло-01", livingRoom, "Температура: 22.5 C");

    std::cout << "Попытка переключить состояние управляемого датчика:" << std::endl;
    hub.TryToggleDevice(*polyDevice);

    std::cout << "\nПопытка переключить состояние пассивного дисплея:" << std::endl;
    hub.TryToggleDevice(display);

    // =========================================================================
    // 5. КОНФИГУРИРОВАНИЕ ОБЪЕКТА (ОБЪЕКТ ПОВЕДЕНИЯ / СТРАТЕГИЯ)
    // =========================================================================
    std::cout << "\n=== 5. КОНФИГУРИРОВАНИЕ ОБЪЕКТА (ОБЪЕКТ ПОВЕДЕНИЯ) ===" << std::endl;
    std::cout << "-- 5.1. Статическое конфигурирование (политика была задана в конструкторе) --" << std::endl;
    hub.RaiseAlarm("Входная дверь", 2);

    std::cout << "\n-- 5.2. Динамическое конфигурирование (смена политики во время работы программы) --" << std::endl;
    // Смена на усиленный режим
    hub.SetSecurityPolicy(std::make_unique<StrictSecurityPolicy>());
    hub.RaiseAlarm("Окно спальни", 5);

    // Смена на ночной беззвучный режим
    hub.SetSecurityPolicy(std::make_unique<SilentSecurityPolicy>());
    hub.RaiseAlarm("Движение во дворе", 1);
    std::cout << "-> Поведение хаба полностью изменилось благодаря подстановке разных объектов поведения!\n";

    // =========================================================================
    // 6. ИСКЛЮЧЕНИЯ ПРЕДМЕТНОЙ ОБЛАСТИ (try / catch / throw)
    // =========================================================================
    std::cout << "\n=== 6. ИСКЛЮЧЕНИЯ ПРЕДМЕТНОЙ ОБЛАСТИ (try, catch, throw) ===" << std::endl;

    // Сценарий 6а: Успешная работа и корректные параметры
    std::cout << "\n--- Сценарий 6а: Штатная работа без ошибок ---" << std::endl;
    try {
        tempDev.SetOnline(true);
        tempDev.Ping(); // Успешный пинг
        tempDev.SetTemperature(24.0); // Корректная температура
        std::cout << "  Успешно: " << tempDev.Describe() << std::endl;
    }
    catch (const DeviceOfflineException& ex) {
        std::cout << "  [ПЕРЕХВАЧЕНО ОФЛАЙН]: " << ex.what() << std::endl;
    }
    catch (const InvalidParameterException& ex) {
        std::cout << "  [ПЕРЕХВАЧЕНА ОШИБКА ПАРАМЕТРА]: " << ex.what() << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << "  [ОБЩАЯ ОШИБКА]: " << ex.what() << std::endl;
    }

    // Сценарий 6б: Нарушение правила — устройство отключено (DeviceOfflineException)
    std::cout << "\n--- Сценарий 6б: Отказ устройства (DeviceOfflineException) ---" << std::endl;
    try {
        std::cout << "Имитируем обрыв связи: переводим датчик в офлайн..." << std::endl;
        tempDev.SetOnline(false);
        tempDev.Ping(); // Вызовет throw DeviceOfflineException
        std::cout << "Эта строка НЕ выполнится из-за исключения!" << std::endl;
    }
    catch (const DeviceOfflineException& ex) { // Частный тип первым!
        std::cout << "  [CATCH СЕТИ]: Устройство '" << ex.GetDeviceName() 
                  << "' не ответило! Причина: " << ex.what() << std::endl;
        std::cout << "  Действие: Система перевела зону в аварийный режим, продолжая работу." << std::endl;
    }
    catch (const std::exception& ex) { // Общий тип последним!
        std::cout << "  [ОБЩИЙ CATCH]: " << ex.what() << std::endl;
    }

    // Сценарий 6в: Нарушение правила — некорректная чувствительность (InvalidParameterException)
    std::cout << "\n--- Сценарий 6в: Ошибка валидации параметров (InvalidParameterException) ---" << std::endl;
    try {
        std::cout << "Попытка установить недопустимую чувствительность радара (значение 99 при норме 1-10)..." << std::endl;
        motionDev.SetSensitivity(99); // Вызовет throw InvalidParameterException
    }
    catch (const InvalidParameterException& ex) {
        std::cout << "  [CATCH ВАЛИДАЦИИ]: Ошибка в параметре '" << ex.GetParameterName() 
                  << "'. Подробности: " << ex.what() << std::endl;
        std::cout << "  Действие: Параметр сброшен к безопасному значению по умолчанию." << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << "  [ОБЩИЙ CATCH]: " << ex.what() << std::endl;
    }

    std::cout << "\n==================================================================" << std::endl;
    std::cout << "                   ПРОГРАММА УСПЕШНО ЗАВЕРШЕНА                    " << std::endl;
    std::cout << "==================================================================" << std::endl;

    return 0;
}
