#include "sensor.hpp"
#include "controller.hpp"
#include "house.hpp"
#include <iostream>
#include <memory>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace smarthome;

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#else
    std::setlocale(LC_ALL, "Russian");
#endif

    // ================================================================
    //  1. std::unique_ptr — ЕДИНСТВЕННЫЙ ВЛАДЕЛЕЦ
    // ================================================================
    std::cout << "=== 1. std::unique_ptr — ЕДИНСТВЕННЫЙ ВЛАДЕЛЕЦ ===" << std::endl;
    std::cout << std::endl;

    {
        std::cout << "-- Создаём unique_ptr<Sensor> внутри блока --" << std::endl;
        std::unique_ptr<Sensor> sensor = std::make_unique<Sensor>("Температура (unique)", 22.5f);
        std::cout << "Имя датчика: " << sensor->GetName() << std::endl;
        std::cout << "Значение: " << sensor->ReadValue() << std::endl;
        std::cout << "-- Выходим из блока — деструктор вызовется автоматически --" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "-- Передача владения через std::move --" << std::endl;
    std::unique_ptr<Sensor> owner1 = std::make_unique<Sensor>("Влажность (move)", 60.0f);
    std::cout << "owner1 указывает на: " << owner1->GetName() << std::endl;

    std::unique_ptr<Sensor> owner2 = std::move(owner1);
    std::cout << "После std::move:" << std::endl;

    if (!owner1) {
        std::cout << "  owner1 == nullptr (пустой, владение передано)" << std::endl;
    }
    std::cout << "  owner2 указывает на: " << owner2->GetName() << std::endl;

    owner2.reset(); // явное освобождение
    std::cout << std::endl;

    // ================================================================
    //  2. std::shared_ptr — РАЗДЕЛЯЕМОЕ ВЛАДЕНИЕ
    // ================================================================
    std::cout << "=== 2. std::shared_ptr — РАЗДЕЛЯЕМОЕ ВЛАДЕНИЕ ===" << std::endl;
    std::cout << std::endl;

    std::shared_ptr<Sensor> shared1 = std::make_shared<Sensor>("Давление (shared)", 101.3f);
    std::cout << "Создан shared1. use_count = " << shared1.use_count() << std::endl;

    std::shared_ptr<Sensor> shared2 = shared1;
    std::cout << "Скопирован в shared2. use_count = " << shared1.use_count() << std::endl;

    {
        std::shared_ptr<Sensor> shared3 = shared1;
        std::cout << "Скопирован в shared3 (внутри блока). use_count = "
                  << shared1.use_count() << std::endl;
        std::cout << "-- Выходим из внутреннего блока --" << std::endl;
    }
    std::cout << "shared3 уничтожен. use_count = " << shared1.use_count() << std::endl;

    shared1.reset();
    std::cout << "shared1 сброшен (reset). use_count у shared2 = "
              << shared2.use_count() << std::endl;

    std::cout << "Сбрасываем последний владелец (shared2)..." << std::endl;
    shared2.reset();
    std::cout << "(Деструктор датчика должен был вызваться выше)" << std::endl;
    std::cout << std::endl;

    // ================================================================
    //  3. std::weak_ptr — НАБЛЮДАТЕЛЬ
    // ================================================================
    std::cout << "=== 3. std::weak_ptr — НАБЛЮДАТЕЛЬ ===" << std::endl;
    std::cout << std::endl;

    std::shared_ptr<Sensor> observed = std::make_shared<Sensor>("Газ (weak)", 0.03f);
    std::weak_ptr<Sensor> weakRef = observed;

    std::cout << "weak_ptr создан. expired = "
              << (weakRef.expired() ? "да" : "нет") << std::endl;

    if (auto locked = weakRef.lock()) {
        std::cout << "lock() успешен: датчик '" << locked->GetName()
                  << "', значение = " << locked->ReadValue() << std::endl;
    }

    std::cout << "Сбрасываем shared_ptr (последний владелец)..." << std::endl;
    observed.reset();

    std::cout << "weak_ptr.expired = "
              << (weakRef.expired() ? "да" : "нет") << std::endl;

    if (auto locked = weakRef.lock()) {
        std::cout << "lock() успешен: " << locked->GetName() << std::endl;
    } else {
        std::cout << "lock() вернул nullptr — Объект уничтожен." << std::endl;
    }
    std::cout << std::endl;

    // ================================================================
    //  4. КОМПОЗИЦИЯ, АГРЕГАЦИЯ И ПРОВЕРКА ПРАВИЛА
    // ================================================================
    std::cout << "=== 4. КОМПОЗИЦИЯ, АГРЕГАЦИЯ И ПРОВЕРКА ПРАВИЛА ===" << std::endl;
    std::cout << std::endl;

    auto outdoorSensor = std::make_shared<Sensor>("Уличный датчик", -5.0f);

    {
        std::cout << "-- Создаём дом (контроллер — композиция по значению) --" << std::endl;
        House house("ул. Пушкина, д. 10", "v3.2.1");

        house.BindSensor(outdoorSensor);

        std::cout << std::endl;
        std::cout << ">> Обновление климата (датчик онлайн):" << std::endl;
        house.UpdateClimate();

        std::cout << std::endl;
        std::cout << ">> Отключаем датчик:" << std::endl;
        outdoorSensor->SetConnectionStatus(false);
        house.UpdateClimate();

        std::cout << std::endl;
        std::cout << ">> Снова подключаем датчик:" << std::endl;
        outdoorSensor->SetConnectionStatus(true);
        house.UpdateClimate();

        std::cout << std::endl;
        std::cout << "-- Выходим из блока — дом уничтожается --" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Агрегация: дом уничтожен, но датчик '" << outdoorSensor->GetName()
              << "' всё ещё существует (shared_ptr жив). use_count = "
              << outdoorSensor.use_count() << std::endl;
    std::cout << std::endl;

    // Демонстрация: weak_ptr после уничтожения датчика
    std::cout << "-- Демонстрация: дом пытается использовать уничтоженный датчик --" << std::endl;
    {
        House house2("пр. Ленина, д. 5", "v4.0.0");
        house2.BindSensor(outdoorSensor);

        std::cout << "Уничтожаем датчик (reset shared_ptr)..." << std::endl;
        outdoorSensor.reset();

        std::cout << std::endl;
        house2.UpdateClimate(); // lock() вернёт nullptr

        std::cout << std::endl;
        std::cout << "-- Дом уничтожается --" << std::endl;
    }
    std::cout << std::endl;

    // ================================================================
    //  5. МАССИВЫ С УМНЫМИ УКАЗАТЕЛЯМИ
    // ================================================================
    std::cout << "=== 5. МАССИВЫ С УМНЫМИ УКАЗАТЕЛЯМИ ===" << std::endl;
    std::cout << std::endl;

    std::cout << "-- unique_ptr<Sensor[]> — динамический массив (make_unique<Sensor[]>) --"
              << std::endl;
    {
        std::unique_ptr<Sensor[]> row = std::make_unique<Sensor[]>(3);
        std::cout << "Создано 3 датчика в массиве (конструктор по умолчанию)." << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "  row[" << i << "]: имя = '" << row[i].GetName()
                      << "', значение = " << row[i].ReadValue() << std::endl;
        }
        std::cout << "-- Выходим из блока — массив очищается автоматически --" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "-- Массив unique_ptr<Sensor> (статический массив указателей) --" << std::endl;
    {
        std::unique_ptr<Sensor> shelf[3];
        shelf[0] = std::make_unique<Sensor>("Полка-1", 10.0f);
        shelf[1] = std::make_unique<Sensor>("Полка-2", 20.0f);
        shelf[2] = std::make_unique<Sensor>("Полка-3", 30.0f);

        for (int i = 0; i < 3; ++i) {
            std::cout << "  shelf[" << i << "]: '" << shelf[i]->GetName()
                      << "' = " << shelf[i]->ReadValue() << std::endl;
        }
        std::cout << "-- Выходим из блока — все элементы очищаются автоматически --" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "=== Программа завершена. Утечек памяти нет! ===" << std::endl;

    return 0;
}
