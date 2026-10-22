#include "motion_sensor.hpp"

namespace smarthome {

MotionSensor::MotionSensor()
    : BaseDevice()
    , m_motionDetected(false)
    , m_sensitivity(5)
    , m_armed(true) {
}

MotionSensor::MotionSensor(std::string_view name, std::shared_ptr<Room> room, int sensitivity)
    : BaseDevice(name, std::move(room))
    , m_motionDetected(false)
    , m_sensitivity(sensitivity)
    , m_armed(true) {
    if (sensitivity < 1 || sensitivity > 10) {
        throw InvalidParameterException("чувствительность", "значение должно быть в интервале от 1 до 10!");
    }
}

MotionSensor::MotionSensor(const MotionSensor& other)
    : BaseDevice(other)
    , m_motionDetected(other.m_motionDetected)
    , m_sensitivity(other.m_sensitivity)
    , m_armed(other.m_armed) {
}

MotionSensor::MotionSensor(MotionSensor&& other) noexcept
    : BaseDevice(std::move(other))
    , m_motionDetected(other.m_motionDetected)
    , m_sensitivity(other.m_sensitivity)
    , m_armed(other.m_armed) {
    other.m_sensitivity = 0;
}

MotionSensor& MotionSensor::operator=(const MotionSensor& other) {
    if (this == &other) {
        return *this;
    }
    BaseDevice::operator=(other);
    m_motionDetected = other.m_motionDetected;
    m_sensitivity = other.m_sensitivity;
    m_armed = other.m_armed;
    return *this;
}

MotionSensor& MotionSensor::operator=(MotionSensor&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    BaseDevice::operator=(std::move(other));
    m_motionDetected = other.m_motionDetected;
    m_sensitivity = other.m_sensitivity;
    m_armed = other.m_armed;
    other.m_sensitivity = 0;
    return *this;
}

std::string MotionSensor::Describe() const {
    std::string armedStr = m_armed ? "На страже" : "Снят с охраны";
    std::string motionStr = m_motionDetected ? "ДВИЖЕНИЕ!" : "Спокойно";
    return "Радар движения: " + Header() + " -> [Режим: " + armedStr 
           + ", Статус: " + motionStr + ", Чувств: " + std::to_string(m_sensitivity) + "/10]";
}

std::unique_ptr<BaseDevice> MotionSensor::Clone() const {
    return std::make_unique<MotionSensor>(*this);
}

void MotionSensor::TurnOn() {
    m_armed = true;
    std::cout << "  [IControllable] Радар '" << GetName() << "' поставлен на охрану." << std::endl;
}

void MotionSensor::TurnOff() {
    m_armed = false;
    std::cout << "  [IControllable] Радар '" << GetName() << "' снят с охраны." << std::endl;
}

bool MotionSensor::IsActive() const {
    return m_armed;
}

void MotionSensor::ExecuteCommand(std::string_view command) {
    std::cout << "  [IControllable] Радар '" << GetName() << "' выполнил команду охраны: " << command << std::endl;
}

void MotionSensor::SetSensitivity(int sensitivity) {
    // Проверка правила предметной области через исключение
    if (sensitivity < 1 || sensitivity > 10) {
        throw InvalidParameterException("чувствительность (" + std::to_string(sensitivity) + ")", 
                                        "значение должно быть в интервале от 1 до 10!");
    }
    m_sensitivity = sensitivity;
}

} // namespace smarthome
