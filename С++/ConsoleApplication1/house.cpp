// house.cpp
#include "house.hpp"
#include <iostream>

namespace smarthome
{

    House::House(std::string_view address, std::string_view controllerFirmware)
        : m_address{ address }, m_controller(controllerFirmware), m_linkedSensor{ nullptr }
    {
        std::cout << "[Конструктор] Дом по адресу '" << m_address << "' построен.\n";
    }

    House::~House()
    {
        std::cout << "[Деструктор] Дом по адресу '" << m_address << "' сносится.\n";
    }

    void House::BindSensor(Sensor* sensor)
    {
        m_linkedSensor = sensor;
        if (m_linkedSensor != nullptr)
        {
            std::cout << "Дом: Датчик '" << m_linkedSensor->GetName() << "' успешно привязан к системе.\n";
        }
    }

    void House::UpdateClimate()
    {
        // ПРОВЕРКА ПРАВИЛА: Устройства могут выходить из строя (Сценарий 2)
        if (m_linkedSensor == nullptr)
        {
            std::cout << "Дом [ОШИБКА]: Нет привязанного датчика! Отказ выполнения.\n";
            return;
        }

        if (!m_linkedSensor->IsOnline())
        {
            std::cout << "Дом [ОШИБКА]: Датчик '" << m_linkedSensor->GetName()
                << "' не отвечает! Отказ выполнения команды климат-контроля.\n";
            return;
        }

        std::cout << "Дом: Считывание данных с датчика...\n";
        float val = m_linkedSensor->ReadValue();
        m_controller.ProcessData(val);
    }

} // namespace smarthome