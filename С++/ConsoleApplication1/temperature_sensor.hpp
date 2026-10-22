#ifndef TEMPERATURE_SENSOR_HPP
#define TEMPERATURE_SENSOR_HPP

#include "base_device.hpp"
#include "icontrollable.hpp"

namespace smarthome {

/// <summary>
/// Датчик температуры.
/// Демонстрация множественного наследования:
/// Наследуется от абстрактного класса BaseDevice (состояние) и интерфейса IControllable (контракт управления).
/// </summary>
class TemperatureSensor : public BaseDevice, public IControllable {
private:
    double m_temperature;
    std::string m_serialNumber;
    bool m_isActive{ true };

public:
    TemperatureSensor();
    TemperatureSensor(std::string_view name, std::shared_ptr<Room> room, double temp, std::string_view serial);
    TemperatureSensor(const TemperatureSensor& other);
    TemperatureSensor(TemperatureSensor&& other) noexcept;
    TemperatureSensor& operator=(const TemperatureSensor& other);
    TemperatureSensor& operator=(TemperatureSensor&& other) noexcept;
    ~TemperatureSensor() noexcept override = default;

    // Раннее связывание: невиртуальный метод скрывает BaseDevice::GetDeviceType
    [[nodiscard]] std::string GetDeviceType() const {
        return "Прецизионный термометр";
    }

    // Позднее связывание: виртуальный метод переопределяет BaseDevice::Describe
    [[nodiscard]] std::string Describe() const override;

    [[nodiscard]] int GetPollInterval() const override { return 30; }
    [[nodiscard]] std::unique_ptr<BaseDevice> Clone() const override;

    // Реализация контракта интерфейса IControllable
    void TurnOn() override;
    void TurnOff() override;
    [[nodiscard]] bool IsActive() const override;
    void ExecuteCommand(std::string_view command) override;

    [[nodiscard]] double GetTemperature() const noexcept { return m_temperature; }
    
    // Валидация параметра: исключение при недопустимой температуре
    void SetTemperature(double temp);

    [[nodiscard]] std::string_view GetSerialNumber() const noexcept { return m_serialNumber; }
};

} // namespace smarthome

#endif // TEMPERATURE_SENSOR_HPP
