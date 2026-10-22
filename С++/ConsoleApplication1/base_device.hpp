#ifndef BASE_DEVICE_HPP
#define BASE_DEVICE_HPP

#include "room.hpp"
#include <string>
#include <string_view>
#include <memory>
#include <iostream>

namespace smarthome {

/// <summary>
/// Абстрактный базовый класс устройства умного дома (по маске Base*).
/// </summary>
class BaseDevice {
private:
    // Статическое поле: счётчик всех созданных устройств в системе
    inline static int s_deviceCounter{ 0 };

    int m_id;
    std::string m_name;
    std::shared_ptr<Room> m_room;

protected:
    // Модификатор protected: метод нужен наследникам для сборки своего описания,
    // но закрыт от внешнего использования (не public и не private).
    [[nodiscard]] std::string Header() const;

public:
    // Статические методы
    static int NextId() {
        return ++s_deviceCounter;
    }

    static int GetTotalDevices() {
        return s_deviceCounter;
    }

    // 1. Конструктор по умолчанию
    BaseDevice();

    // 2. Конструктор с параметрами
    BaseDevice(std::string_view name, std::shared_ptr<Room> room);

    // 3. Конструктор глубокого копирования (создаёт свой экземпляр Room)
    BaseDevice(const BaseDevice& other);

    // 4. Конструктор перемещения
    BaseDevice(BaseDevice&& other) noexcept;

    // 5. Операторы присваивания (с проверкой самоприсваивания через this)
    BaseDevice& operator=(const BaseDevice& other);
    BaseDevice& operator=(BaseDevice&& other) noexcept;

    // 6. Виртуальный деструктор (обязателен для полиморфного удаления!)
    virtual ~BaseDevice();

    // Чисто виртуальный метод (= 0) — интервал опроса датчика в секундах
    [[nodiscard]] virtual int GetPollInterval() const = 0;

    // Виртуальный метод клонирования (полиморфная глубокая копия)
    [[nodiscard]] virtual std::unique_ptr<BaseDevice> Clone() const = 0;

    // Виртуальный метод с базовой реализацией
    [[nodiscard]] virtual std::string Describe() const;

    // Демонстрация this: передача текущего объекта другому объекту
    void AttachToRoom(Room& room) const;

    // Геттеры и сеттеры
    [[nodiscard]] int GetId() const { return m_id; }
    [[nodiscard]] std::string_view GetName() const { return m_name; }
    [[nodiscard]] std::shared_ptr<Room> GetRoom() const { return m_room; }
    void RenameRoom(std::string_view newName);
};

} // namespace smarthome

#endif // BASE_DEVICE_HPP
