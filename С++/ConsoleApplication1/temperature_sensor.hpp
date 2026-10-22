#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

#include "base_device.hpp"

namespace smarthome {

/// <summary>
/// Датчик температуры (наследник BaseDevice).
/// </summary>
class TemperatureSensor : public BaseDevice {
private:
    double m_temperature;
    std::string m_serialNumber;

public:
    // Конструктор по умолчанию
    TemperatureSensor();

    // Конструктор с параметрами (вызывает конструктор базы в списке инициализации)
    TemperatureSensor(std::string_view name, std::shared_ptr<Room> room, double temp, std::string_view serial);

    // Конструктор копирования
    TemperatureSensor(const TemperatureSensor& other);

    // Конструктор перемещения
    TemperatureSensor(TemperatureSensor&& other) noexcept;

    // Операторы присваивания
    TemperatureSensor& operator=(const TemperatureSensor& other);
    TemperatureSensor& operator=(TemperatureSensor&& other) noexcept;

    // Деструктор
    ~TemperatureSensor() override;

    // Реализация чисто виртуального метода базы
    [[nodiscard]] int GetPollInterval() const override {
        return 30; // Опрос температуры раз в 30 секунд
    }

    // Переопределение метода с ВЫЗОВОМ метода базового класса
    [[nodiscard]] std::string Describe() const override;

    // Виртуальный метод клонирования (глубокая полиморфная копия)
    [[nodiscard]] std::unique_ptr<BaseDevice> Clone() const override;

    [[nodiscard]] double GetTemperature() const { return m_temperature; }
    void SetTemperature(double temp) { m_temperature = temp; }
    [[nodiscard]] std::string_view GetSerialNumber() const { return m_serialNumber; }
};

} // namespace smarthome

#endif // TEMPERATURE_SENSOR_HPP
