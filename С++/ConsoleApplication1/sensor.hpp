#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>
#include <string_view>

namespace smarthome {

class Sensor {
private:
    std::string m_name;
    float m_currentValue;
    bool m_isOnline;

public:
    Sensor();
    Sensor(std::string_view name, float initialValue);
    ~Sensor();

    Sensor(const Sensor&) = delete;
    Sensor& operator=(const Sensor&) = delete;

    std::string_view GetName() const;
    bool IsOnline() const;
    void SetConnectionStatus(bool status);
    float ReadValue() const;
};

} // namespace smarthome

#endif // SENSOR_HPP
