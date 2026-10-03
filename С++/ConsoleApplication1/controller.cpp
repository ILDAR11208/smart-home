// controller.cpp
#include "controller.hpp"
#include <iostream>

namespace smarthome
{

    Controller::Controller(std::string_view firmware)
        : m_firmwareVersion{ firmware }, m_hasActiveErrors{ false }
    {
        std::cout << "[Конструктор] Контроллер (версия " << m_firmwareVersion << ") установлен.\n";
    }

    Controller::~Controller()
    {
        std::cout << "[Деструктор] Контроллер демонтирован и уничтожен.\n";
    }

    void Controller::RunDiagnostics()
    {
        std::cout << "Контроллер: Запуск диагностики системы...\n";
        m_hasActiveErrors = false;
        std::cout << "Контроллер: Система работает в штатном режиме.\n";
    }

    void Controller::ProcessData(float sensorValue)
    {
        if (sensorValue < 0.0f)
        {
            std::cout << "Контроллер: Зафиксирована отрицательная температура. Активация режима подогрева.\n";
        }
        else
        {
            std::cout << "Контроллер: Температура в норме. Режим ожидания.\n";
        }
    }

    bool Controller::HasErrors() const
    {
        return m_hasActiveErrors;
    }

} // namespace smarthome