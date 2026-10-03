// house.hpp
#pragma once

#include "controller.hpp"
#include "sensor.hpp"
#include <string>
#include <string_view>

namespace smarthome
{

    class House
    {
    private:
        std::string m_address;
        Controller m_controller;      // КОМПОЗИЦИЯ: Часть целого (по значению)
        Sensor* m_linkedSensor;       // АГРЕГАЦИЯ: Ссылка на внешний объект (через указатель)

    public:
        House(std::string_view address, std::string_view controllerFirmware);
        ~House();

        // Содержательные методы
        void BindSensor(Sensor* sensor);
        void UpdateClimate();
    };

} // namespace smarthome#pragma once
