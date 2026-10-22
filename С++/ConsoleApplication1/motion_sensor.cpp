#include "motion_sensor.hpp"

namespace smarthome {

MotionSensor::MotionSensor()
    : BaseDevice()
    , m_motionDetected(false)
    , m_sensitivity(5) {
    std::cout << "[MotionSensor::MotionSensor()] Создан датчик движения по умолчанию" << std::endl;
}

MotionSensor::MotionSensor(std::string_view name, std::shared_ptr<Room> room, int sensitivity)
    : BaseDevice(name, std::move(room))
    , m_motionDetected(false)
    , m_sensitivity(sensitivity) {
    std::cout << "[MotionSensor::MotionSensor(params)] Создан датчик движения '" << name 
              << "', чувств=" << m_sensitivity << std::endl;
}

MotionSensor::MotionSensor(const MotionSensor& other)
    : BaseDevice(other)
    , m_motionDetected(other.m_motionDetected)
    , m_sensitivity(other.m_sensitivity) {
    std::cout << "[MotionSensor::MotionSensor(copy)] Копия датчика движения" << std::endl;
}

MotionSensor::MotionSensor(MotionSensor&& other) noexcept
    : BaseDevice(std::move(other))
    , m_motionDetected(other.m_motionDetected)
    , m_sensitivity(other.m_sensitivity) {
    other.m_sensitivity = 0;
    std::cout << "[MotionSensor::MotionSensor(move)] Перемещение датчика движения" << std::endl;
}

MotionSensor& MotionSensor::operator=(const MotionSensor& other) {
    std::cout << "[MotionSensor::operator=] Присваивание датчика движения" << std::endl;
    if (this == &other) {
        return *this;
    }
    BaseDevice::operator=(other);
    m_motionDetected = other.m_motionDetected;
    m_sensitivity = other.m_sensitivity;
    return *this;
}

MotionSensor& MotionSensor::operator=(MotionSensor&& other) noexcept {
    std::cout << "[MotionSensor::operator=(move)] Перемещающее присваивание" << std::endl;
    if (this == &other) {
        return *this;
    }
    BaseDevice::operator=(std::move(other));
    m_motionDetected = other.m_motionDetected;
    m_sensitivity = other.m_sensitivity;
    other.m_sensitivity = 0;
    return *this;
}

MotionSensor::~MotionSensor() {
    std::cout << "[~MotionSensor()] Уничтожен датчик движения" << std::endl;
}

std::string MotionSensor::Describe() const {
    // ПОЛНАЯ ЗАМЕНА без вызова BaseDevice::Describe()
    // Наследник использует protected-метод Header() для получения префикса
    std::string state = m_motionDetected ? "ТРЕВОГА (движение обнаружено!)" : "Спокойно (нет движения)";
    return "Датчик движения: " + Header() + " -> [Статус: " + state 
           + ", Чувствительность: " + std::to_string(m_sensitivity) + "/10]";
}

std::unique_ptr<BaseDevice> MotionSensor::Clone() const {
    return std::make_unique<MotionSensor>(*this);
}

} // namespace smarthome
