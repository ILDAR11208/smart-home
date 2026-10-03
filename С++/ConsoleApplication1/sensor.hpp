// sensor.hpp
#pragma once

#include <string>
#include <string_view>

namespace smarthome
{

    class Sensor
    {
    private:
        std::string m_name;
        float m_currentValue;
        bool m_isOnline;

    public:
        Sensor(std::string_view name, float initialValue);
        ~Sensor();

        [[nodiscard]] std::string_view GetName() const;
        [[nodiscard]] bool IsOnline() const;

        // Содержательные методы
        void SetConnectionStatus(bool status);
        [[nodiscard]] float ReadValue() const;
    };

} // namespace smarthome