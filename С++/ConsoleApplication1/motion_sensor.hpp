#ifndef MOTION_SENSOR_HPP
#define MOTION_SENSOR_HPP

#include "base_device.hpp"

namespace smarthome {

/// <summary>
/// Датчик движения.
/// Модификатор final запрещает дальнейшее наследование от этого класса.
/// </summary>
class MotionSensor final : public BaseDevice {
private:
    bool m_motionDetected;
    int m_sensitivity; // Чувствительность (1-10)

public:
    MotionSensor();
    MotionSensor(std::string_view name, std::shared_ptr<Room> room, int sensitivity);
    MotionSensor(const MotionSensor& other);
    MotionSensor(MotionSensor&& other) noexcept;
    MotionSensor& operator=(const MotionSensor& other);
    MotionSensor& operator=(MotionSensor&& other) noexcept;
    ~MotionSensor() override;

    // Реализация чисто виртуального метода базы
    [[nodiscard]] int GetPollInterval() const override {
        return 5; // Быстрый опрос движения раз в 5 секунд
    }

    // Переопределение метода БЕЗ ВЫЗОВА базового класса (полная замена поведения)
    [[nodiscard]] std::string Describe() const override;

    // Виртуальный метод клонирования
    [[nodiscard]] std::unique_ptr<BaseDevice> Clone() const override;

    [[nodiscard]] bool IsMotionDetected() const { return m_motionDetected; }
    void SetMotionDetected(bool detected) { m_motionDetected = detected; }
    [[nodiscard]] int GetSensitivity() const { return m_sensitivity; }
};

} // namespace smarthome

#endif // MOTION_SENSOR_HPP
