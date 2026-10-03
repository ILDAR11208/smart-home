// sensor.cpp
#include "sensor.hpp"
#include <iostream>

namespace smarthome
{

    Sensor::Sensor(std::string_view name, float initialValue)
        : m_name{ name }, m_currentValue{ initialValue }, m_isOnline{ true }
    {
        std::cout << "[Конструктор] Датчик '" << m_name << "' создан.\n";
    }

    Sensor::~Sensor()
    {
        std::cout << "[Деструктор] Датчик '" << m_name << "' уничтожен.\n";
    }

    std::string_view Sensor::GetName() const
    {
        return m_name;
    }

    bool Sensor::IsOnline() const
    {
        return m_isOnline;
    }

    void Sensor::SetConnectionStatus(bool status)
    {
        m_isOnline = status;
        std::cout << "Датчик '" << m_name << "' изменил статус на: "
            << (m_isOnline ? "Онлайн" : "Офлайн") << "\n";
    }

    float Sensor::ReadValue() const
    {
        return m_currentValue;
    }

} // namespace smarthome