#include "base_device.hpp"
#include "temperature_sensor.hpp"
#include "motion_sensor.hpp"
#include "string_utils.hpp"
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
    std::cout << "     ЛАБОРАТОРНАЯ РАБОТА № 4: НАСЛЕДОВАНИЕ И ПОЛИМОРФИЗМ (C++)    " << std::endl;
    std::cout << "==================================================================" << std::endl;

    // =========================================================================
    // 1. ПОРЯДОК ВЫЗОВА КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ
    // =========================================================================
    std::cout << "\n=== 1. ПОРЯДОК ВЫЗОВА КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ ===" << std::endl;
    {
        std::cout << "\n-- Создание объекта TemperatureSensor в блоке --" << std::endl;
        auto kitchen = std::make_shared<Room>("Кухня");
        TemperatureSensor tempSensor("Термометр-Кухня", kitchen, 24.5, "SN-TMP-101");
        std::cout << "-- Выход из блока (разрушение объекта) --" << std::endl;
    }
    std::cout << "-> Вывод доказывает: конструкторы вызываются от Базы к Наследнику,\n"
              << "   а деструкторы — в обратном порядке: от Наследника к Базе.\n";

    // =========================================================================
    // 2. ВИРТУАЛЬНЫЙ ДЕСТРУКТОР
    // =========================================================================
    std::cout << "\n=== 2. ВИРТУАЛЬНЫЙ ДЕСТРУКТОР ===" << std::endl;
    {
        std::cout << "-- Создание MotionSensor через указатель на BaseDevice --" << std::endl;
        auto hall = std::make_shared<Room>("Прихожая");
        std::unique_ptr<BaseDevice> polyDevice = std::make_unique<MotionSensor>("ДатчикДвижения-Прихожая", hall, 8);

        std::cout << "\n-- Вызов reset() (уничтожение через указатель на базовый класс) --" << std::endl;
        polyDevice.reset();
        std::cout << "-> Вывод доказывает: благодаря virtual ~BaseDevice() сначала сработал\n"
                  << "   деструктор ~MotionSensor(), а затем ~BaseDevice(). Без virtual деструктор\n"
                  << "   наследника не вызвался бы, что привело бы к утечке и UB!\n";
    }

    // =========================================================================
    // 3. ПОВЕРХНОСТНАЯ И ГЛУБОКАЯ КОПИЯ
    // =========================================================================
    std::cout << "\n=== 3. ПОВЕРХНОСТНАЯ И ГЛУБОКАЯ КОПИЯ ===" << std::endl;
    {
        auto livingRoom = std::make_shared<Room>("Гостиная");
        TemperatureSensor original("Датчик-Оригинал", livingRoom, 22.0, "SN-ORIG-01");

        std::cout << "\n-- Создание глубокой копии через конструктор копирования --" << std::endl;
        TemperatureSensor deepCopy = original; // Создает собственный Room

        std::cout << "\nСостояние ДО изменения:" << std::endl;
        std::cout << "  Оригинал: " << original.Describe() << std::endl;
        std::cout << "  Копия:    " << deepCopy.Describe() << std::endl;

        std::cout << "\nИзменяем комнату у копии на 'Спальня':" << std::endl;
        deepCopy.RenameRoom("Спальня");

        std::cout << "\nСостояние ПОСЛЕ изменения комнаты у копии:" << std::endl;
        std::cout << "  Оригинал: " << original.Describe() << std::endl;
        std::cout << "  Копия:    " << deepCopy.Describe() << std::endl;
        std::cout << "-> Исходный объект НЕ изменился! Это подтверждает глубокую копию (deep copy),\n"
                  << "   так как копия владеет собственным независимым объектом Room.\n";
    }

    // =========================================================================
    // 4. КЛОНИРОВАНИЕ ЧЕРЕЗ БАЗОВЫЙ КЛАСС (Clone)
    // =========================================================================
    std::cout << "\n=== 4. КЛОНИРОВАНИЕ ЧЕРЕЗ БАЗОВЫЙ КЛАСС (Clone()) ===" << std::endl;
    {
        auto corridor = std::make_shared<Room>("Коридор");
        std::unique_ptr<BaseDevice> item = std::make_unique<MotionSensor>("Датчик-Коридор", corridor, 9);

        std::cout << "\nКлонируем объект через указатель BaseDevice->Clone():" << std::endl;
        std::unique_ptr<BaseDevice> clonedItem = item->Clone();

        std::cout << "  Оригинал: " << item->Describe() << std::endl;
        std::cout << "  Клон:     " << clonedItem->Describe() << std::endl;
        std::cout << "-> Метод Clone() вернул правильный наследник MotionSensor без срезки (slicing)!\n";
    }

    // =========================================================================
    // 5. ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ (override) И final
    // =========================================================================
    std::cout << "\n=== 5. ПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ (override) И final ===" << std::endl;
    {
        auto balcony = std::make_shared<Room>("Балкон");
        TemperatureSensor temp("Термометр-Балкон", balcony, -12.3, "SN-BALK-01");
        MotionSensor motion("ДатчикДвижения-Балкон", balcony, 3);

        std::cout << "\n1) Переопределение С вызовом базового класса (TemperatureSensor):" << std::endl;
        std::cout << "   " << temp.Describe() << std::endl;

        std::cout << "\n2) Переопределение БЕЗ вызова базового класса (MotionSensor, final):" << std::endl;
        std::cout << "   " << motion.Describe() << std::endl;
        std::cout << "-> Класс MotionSensor помечен как final (запрет дальнейшего наследования).\n";
    }

    // =========================================================================
    // 6. ИСПОЛЬЗОВАНИЕ УКАЗАТЕЛЯ this
    // =========================================================================
    std::cout << "\n=== 6. ИСПОЛЬЗОВАНИЕ УКАЗАТЕЛЯ this ===" << std::endl;
    {
        auto office = std::make_shared<Room>("Кабинет");
        TemperatureSensor sensorA("Термометр-Кабинет", office, 21.0, "SN-OFFICE-01");

        std::cout << "\nа) Проверка самоприсваивания через this (sensorA = sensorA):" << std::endl;
        sensorA = sensorA;

        std::cout << "\nб) Возврат *this для поддержки цепочки присваиваний:" << std::endl;
        TemperatureSensor sensorB;
        TemperatureSensor sensorC;
        sensorC = sensorB = sensorA;
        std::cout << "   sensorC после цепочки: " << sensorC.Describe() << std::endl;

        std::cout << "\nв) Передача *this другому объекту (Room::Report(*this)):" << std::endl;
        Room garage("Гараж");
        sensorA.AttachToRoom(garage);
    }

    // =========================================================================
    // 7. СТАТИЧЕСКИЕ ЧЛЕНЫ КЛАССА
    // =========================================================================
    std::cout << "\n=== 7. СТАТИЧЕСКИЕ ЧЛЕНЫ КЛАССА ===" << std::endl;
    {
        std::cout << "Текущий счётчик созданных устройств: BaseDevice::GetTotalDevices() = "
                  << BaseDevice::GetTotalDevices() << std::endl;
        std::cout << "Генерация следующего ID: BaseDevice::NextId() = "
                  << BaseDevice::NextId() << std::endl;
    }

    // =========================================================================
    // 8. РАБОТА СО СТРОКАМИ std::string
    // =========================================================================
    std::cout << "\n=== 8. РАБОТА СО СТРОКАМИ std::string ===" << std::endl;
    StringUtils::DemonstrateStringOperations();

    // =========================================================================
    // 9. ПОЛИМОРФНЫЙ МАССИВ ДАТЧИКОВ (unique_ptr<BaseDevice>[])
    // =========================================================================
    std::cout << "\n=== 9. ПОЛИМОРФНЫЙ МАССИВ std::unique_ptr<BaseDevice> ===" << std::endl;
    {
        auto wholeHouse = std::make_shared<Room>("Весь дом");

        std::vector<std::unique_ptr<BaseDevice>> devices;
        devices.push_back(std::make_unique<TemperatureSensor>("Входной термометр", wholeHouse, 18.0, "SN-T-01"));
        devices.push_back(std::make_unique<MotionSensor>("Входной радар", wholeHouse, 10));
        devices.push_back(std::make_unique<TemperatureSensor>("Датчик в гостиной", wholeHouse, 23.5, "SN-T-02"));

        std::cout << "\nОбход полиморфного массива через указатель на базовый класс:" << std::endl;
        for (const auto& dev : devices) {
            std::cout << "  • " << dev->Describe() 
                      << " [Интервал опроса: " << dev->GetPollInterval() << " сек.]" << std::endl;
        }

        std::cout << "\n-- Очистка массива (автоматическое полиморфное удаление) --" << std::endl;
    }

    std::cout << "\n==================================================================" << std::endl;
    std::cout << "                   ПРОГРАММА УСПЕШНО ЗАВЕРШЕНА                    " << std::endl;
    std::cout << "==================================================================" << std::endl;

    return 0;
}
