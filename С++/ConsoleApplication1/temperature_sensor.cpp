#include "temperature_sensor.hpp"

namespace smarthome {

TemperatureSensor::TemperatureSensor()
    : BaseDevice()
    , m_temperature(20.0)
    , m_serialNumber("SN-TMP-DEFAULT") {
    std::cout << "[TemperatureSensor::TemperatureSensor()] Создан датчик по умолчанию" << std::endl;
}

TemperatureSensor::TemperatureSensor(std::string_view name, std::shared_ptr<Room> room, double temp, std::string_view serial)
    : BaseDevice(name, std::move(room)) // Вызов конструктора базового класса в списке инициализации
    , m_temperature(temp)
    , m_serialNumber(serial) {
    std::cout << "[TemperatureSensor::TemperatureSensor(params)] Создан датчик '" << name 
              << "', темп=" << m_temperature << ", сер=" << m_serialNumber << std::endl;
}

TemperatureSensor::TemperatureSensor(const TemperatureSensor& other)
    : BaseDevice(other) // Глубокое копирование базовой части (включая Room)
    , m_temperature(other.m_temperature)
    , m_serialNumber(other.m_serialNumber) {
    std::cout << "[TemperatureSensor::TemperatureSensor(copy)] Копия датчика температуры" << std::endl;
}

TemperatureSensor::TemperatureSensor(TemperatureSensor&& other) noexcept
    : BaseDevice(std::move(other))
    , m_temperature(other.m_temperature)
    , m_serialNumber(std::move(other.m_serialNumber)) {
    other.m_temperature = 0.0;
    std::cout << "[TemperatureSensor::TemperatureSensor(move)] Перемещение датчика температуры" << std::endl;
}

TemperatureSensor& TemperatureSensor::operator=(const TemperatureSensor& other) {
    std::cout << "[TemperatureSensor::operator=] Присваивание датчика температуры" << std::endl;
    if (this == &other) {
        return *this;
    }
    BaseDevice::operator=(other); // Вызов оператора присваивания базового класса
    m_temperature = other.m_temperature;
    m_serialNumber = other.m_serialNumber;
    return *this;
}

TemperatureSensor& TemperatureSensor::operator=(TemperatureSensor&& other) noexcept {
    std::cout << "[TemperatureSensor::operator=(move)] Перемещающее присваивание" << std::endl;
    if (this == &other) {
        return *this;
    }
    BaseDevice::operator=(std::move(other));
    m_temperature = other.m_temperature;
    m_serialNumber = std::move(other.m_serialNumber);
    other.m_temperature = 0.0;
    return *this;
}

TemperatureSensor::~TemperatureSensor() {
    std::cout << "[~TemperatureSensor()] Уничтожен датчик температуры" << std::endl;
}

std::string TemperatureSensor::Describe() const {
    // ВЫЗОВ базового метода BaseDevice::Describe() и дополнение новыми данными
    return BaseDevice::Describe() + " -> [Температура: " + std::to_string(m_temperature) 
           + " C, S/N: " + m_serialNumber + "]";
}

std::unique_ptr<BaseDevice> TemperatureSensor::Clone() const {
    return std::make_unique<TemperatureSensor>(*this);
}

} // namespace smarthome
