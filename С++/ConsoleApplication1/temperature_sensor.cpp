#include "temperature_sensor.hpp"

namespace smarthome {

TemperatureSensor::TemperatureSensor()
    : BaseDevice()
    , m_temperature(22.0)
    , m_serialNumber("SN-TMP-DEFAULT")
    , m_isActive(true) {
}

TemperatureSensor::TemperatureSensor(std::string_view name, std::shared_ptr<Room> room, double temp, std::string_view serial)
    : BaseDevice(name, std::move(room))
    , m_temperature(temp)
    , m_serialNumber(serial)
    , m_isActive(true) {
    if (temp < -50.0 || temp > 100.0) {
        throw InvalidParameterException("температура", "выходит за допустимый диапазон от -50 до +100 C!");
    }
}

TemperatureSensor::TemperatureSensor(const TemperatureSensor& other)
    : BaseDevice(other)
    , m_temperature(other.m_temperature)
    , m_serialNumber(other.m_serialNumber)
    , m_isActive(other.m_isActive) {
}

TemperatureSensor::TemperatureSensor(TemperatureSensor&& other) noexcept
    : BaseDevice(std::move(other))
    , m_temperature(other.m_temperature)
    , m_serialNumber(std::move(other.m_serialNumber))
    , m_isActive(other.m_isActive) {
}

TemperatureSensor& TemperatureSensor::operator=(const TemperatureSensor& other) {
    if (this == &other) {
        return *this;
    }
    BaseDevice::operator=(other);
    m_temperature = other.m_temperature;
    m_serialNumber = other.m_serialNumber;
    m_isActive = other.m_isActive;
    return *this;
}

TemperatureSensor& TemperatureSensor::operator=(TemperatureSensor&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    BaseDevice::operator=(std::move(other));
    m_temperature = other.m_temperature;
    m_serialNumber = std::move(other.m_serialNumber);
    m_isActive = other.m_isActive;
    return *this;
}

std::string TemperatureSensor::Describe() const {
    return BaseDevice::Describe() + " -> [Температура: " + std::to_string(m_temperature)
           + " C, S/N: " + m_serialNumber + "]";
}

std::unique_ptr<BaseDevice> TemperatureSensor::Clone() const {
    return std::make_unique<TemperatureSensor>(*this);
}

void TemperatureSensor::TurnOn() {
    m_isActive = true;
    std::cout << "  [IControllable] Термометр '" << GetName() << "' включён." << std::endl;
}

void TemperatureSensor::TurnOff() {
    m_isActive = false;
    std::cout << "  [IControllable] Термометр '" << GetName() << "' выключен (энергосбережение)." << std::endl;
}

bool TemperatureSensor::IsActive() const {
    return m_isActive;
}

void TemperatureSensor::ExecuteCommand(std::string_view command) {
    std::cout << "  [IControllable] Термометр '" << GetName() << "' выполнил команду: " << command << std::endl;
}

void TemperatureSensor::SetTemperature(double temp) {
    // Проверка правила предметной области: температура датчика должна быть в диапазоне [-50, +100]
    if (temp < -50.0 || temp > 100.0) {
        throw InvalidParameterException("температура (" + std::to_string(temp) + ")", 
                                        "выходит за допустимый диапазон от -50 до +100 C!");
    }
    m_temperature = temp;
}

} // namespace smarthome
