#include "house.hpp"
#include <iostream>

namespace smarthome {

House::House(std::string_view address, std::string_view controllerFirmware)
    : m_address(address), m_controller(controllerFirmware) {
    std::cout << "[Конструктор] Дом по адресу '" << m_address
              << "' построен." << std::endl;
}

House::~House() {
    std::cout << "[Деструктор] Дом по адресу '" << m_address
              << "' сносится." << std::endl;
}

void House::BindSensor(const std::shared_ptr<Sensor>& sensor) {
    m_linkedSensor = sensor;
    std::cout << "Датчик '" << sensor->GetName()
              << "' привязан к дому '" << m_address << "'." << std::endl;
}

void House::UpdateClimate() {
    std::cout << "--- Обновление климата в доме '" << m_address << "' ---"
              << std::endl;

    // Пытаемся получить shared_ptr из weak_ptr
    std::shared_ptr<Sensor> sensor = m_linkedSensor.lock();

    if (!sensor) {
        std::cout << "Ошибка: датчик недоступен (объект уничтожен)!" << std::endl;
        return;
    }

    if (!sensor->IsOnline()) {
        std::cout << "Ошибка: датчик '" << sensor->GetName()
                  << "' не в сети! Невозможно обновить климат." << std::endl;
        return;
    }

    float value = sensor->ReadValue();
    std::cout << "Датчик '" << sensor->GetName()
              << "' передал значение: " << value << std::endl;
    m_controller.ProcessData(value);
}

} // namespace smarthome
