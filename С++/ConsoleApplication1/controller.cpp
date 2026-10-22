#include "controller.hpp"
#include <iostream>

namespace smarthome {

Controller::Controller(std::string_view firmware)
    : m_firmwareVersion(firmware), m_hasActiveErrors(false) {
    std::cout << "[Конструктор] Контроллер (версия " << m_firmwareVersion
              << ") установлен." << std::endl;
}

Controller::~Controller() {
    std::cout << "[Деструктор] Контроллер демонтирован и уничтожен." << std::endl;
}

void Controller::RunDiagnostics() {
    std::cout << "Диагностика контроллера (версия " << m_firmwareVersion
              << ")... ";
    if (m_hasActiveErrors) {
        std::cout << "Обнаружены ошибки!" << std::endl;
    } else {
        std::cout << "Всё в норме." << std::endl;
    }
}

void Controller::ProcessData(float sensorValue) {
    std::cout << "Обработка данных: значение = " << sensorValue << ". ";
    if (sensorValue < 0) {
        std::cout << "Активация режима подогрева." << std::endl;
    } else {
        std::cout << "Режим ожидания." << std::endl;
    }
}

bool Controller::HasErrors() const {
    return m_hasActiveErrors;
}

} // namespace smarthome
