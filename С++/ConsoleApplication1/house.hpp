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
        Controller m_controller;      //  ќћѕќ«»÷»я: „асть целого (по значению)
        Sensor* m_linkedSensor;       // ј√–≈√ј÷»я: —сылка на внешний объект (через указатель)

    public:
        House(std::string_view address, std::string_view controllerFirmware);
        ~House();

        // —одержательные методы
        void BindSensor(Sensor* sensor);
        void UpdateClimate();
    };

} // namespace smarthome#pragma once
