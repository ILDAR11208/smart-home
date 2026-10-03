#include "house.hpp"
#include "sensor.hpp"
#include <iostream>
#include <clocale>

using namespace smarthome;

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "=== 1. ДЕМОНСТРАЦИЯ РАБОТЫ С ПАМЯТЬЮ ===\n";

    // Статическая инициализация
    Sensor staticSensor("Датчик в гостиной", 22.5f);

    // Динамическая инициализация объекта
    House* dynamicHouse = new House("Ул. Ленина, 10", "v1.0.4");

    // Операторы по указателю
    dynamicHouse->BindSensor(&staticSensor);
    dynamicHouse->UpdateClimate();
    delete dynamicHouse; // Очистка динамической памяти

    // Динамический массив объектов класса
    std::cout << "\n--- Динамический массив объектов ---\n";
    Sensor* sensorArray = new Sensor[2]{
        {"Кухня", 24.0f},
        {"Ванная", 26.0f}
    };
    delete[] sensorArray;

    // Массив динамических объектов (массив указателей)
    std::cout << "\n--- Массив динамических объектов ---\n";
    House* houseList[2];
    houseList[0] = new House("Ул. Мира, 1", "v2.0");
    houseList[1] = new House("Ул. Мира, 2", "v2.0");
    delete houseList[0];
    delete houseList[1];

    std::cout << "\n=== 2. ДЕМОНСТРАЦИЯ КОМПОЗИЦИИ, АГРЕГАЦИИ И ПРОВЕРКИ ПРАВИЛ ===\n";

    // Создаем объект для агрегации во внешнем блоке
    Sensor outdoorSensor("Уличный термометр", -15.0f);

    {
        std::cout << "\n[Внутренний блок] Создание дома...\n";
        // Дом автоматически создает Контроллер (Композиция)
        House myHouse("Ул. Пушкина, Дом Колотушкина", "v3.1-stable");

        // Передаем указатель на существующий объект (Агрегация)
        myHouse.BindSensor(&outdoorSensor);

        std::cout << "\n--- Корректное действие ---\n";
        myHouse.UpdateClimate();

        std::cout << "\n--- Попытка нарушить правило (Отказ датчика) ---\n";
        outdoorSensor.SetConnectionStatus(false); // Имитируем поломку (Сценарий 2)
        myHouse.UpdateClimate(); // Дом откажется менять климат

        std::cout << "\n[Внутренний блок] Выход из блока, уничтожение дома...\n";
    }

    // Доказательство работы агрегации
    std::cout << "\n[Внешний блок] Дом уничтожен. Проверяем состояние уличного датчика:\n";
    std::cout << "Датчик '" << outdoorSensor.GetName() << "' все еще существует и его статус: "
        << (outdoorSensor.IsOnline() ? "Онлайн" : "Офлайн") << "\n\n";

    return 0;
}