#include "sensor.hpp"
#include <iostream>

namespace smarthome {

Sensor::Sensor()
    : m_name("Без имени"), m_currentValue(0.0f), m_isOnline(false) {
}

Sensor::Sensor(std::string_view name, float initialValue)
    : m_name(name), m_currentValue(initialValue), m_isOnline(true) {
    std::cout << "[Конструктор] Датчик '" << m_name << "' создан." << std::endl;
}

Sensor::~Sensor() {
    std::cout << "[Деструктор] Датчик '" << m_name << "' уничтожен." << std::endl;
}

std::string_view Sensor::GetName() const {
    return m_name;
}

bool Sensor::IsOnline() const {
    return m_isOnline;
}

void Sensor::SetConnectionStatus(bool status) {
    m_isOnline = status;
    if (status) {
        std::cout << "Датчик '" << m_name << "' подключён." << std::endl;
    } else {
        std::cout << "Датчик '" << m_name << "' отключён." << std::endl;
    }
}

float Sensor::ReadValue() const {
    return m_currentValue;
}

} // namespace smarthome
