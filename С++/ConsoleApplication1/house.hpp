#ifndef HOUSE_HPP
#define HOUSE_HPP

#include "controller.hpp"
#include "sensor.hpp"
#include <memory>
#include <string>
#include <string_view>

namespace smarthome {

class House {
private:
    std::string m_address;
    Controller m_controller;              // Композиция — владение по значению
    std::weak_ptr<Sensor> m_linkedSensor; // Агрегация — наблюдатель (не владеет)

public:
    House(std::string_view address, std::string_view controllerFirmware);
    ~House();

    House(const House&) = delete;
    House& operator=(const House&) = delete;

    void BindSensor(const std::shared_ptr<Sensor>& sensor);
    void UpdateClimate();
};

} // namespace smarthome

#endif // HOUSE_HPP
