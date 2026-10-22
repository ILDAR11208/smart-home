#ifndef MOTION_SENSOR_HPP
#define MOTION_SENSOR_HPP

#include "base_device.hpp"
#include "icontrollable.hpp"

namespace smarthome {

/// <summary>
/// Датчик движения.
/// Множественное наследование: BaseDevice + IControllable.
/// </summary>
class MotionSensor : public BaseDevice, public IControllable {
private:
    bool m_motionDetected{ false };
    int m_sensitivity{ 5 };
    bool m_armed{ true };

public:
    MotionSensor();
    MotionSensor(std::string_view name, std::shared_ptr<Room> room, int sensitivity);
    MotionSensor(const MotionSensor& other);
    MotionSensor(MotionSensor&& other) noexcept;
    MotionSensor& operator=(const MotionSensor& other);
    MotionSensor& operator=(MotionSensor&& other) noexcept;
    ~MotionSensor() noexcept override = default;

    // Раннее связывание: невиртуальный метод
    [[nodiscard]] std::string GetDeviceType() const {
        return "Охранный радар движения";
    }

    // Позднее связывание: виртуальный метод
    [[nodiscard]] std::string Describe() const override;

    [[nodiscard]] int GetPollInterval() const override { return 5; }
    [[nodiscard]] std::unique_ptr<BaseDevice> Clone() const override;

    // Реализация контракта IControllable
    void TurnOn() override;
    void TurnOff() override;
    [[nodiscard]] bool IsActive() const override;
    void ExecuteCommand(std::string_view command) override;

    [[nodiscard]] bool IsMotionDetected() const noexcept { return m_motionDetected; }
    void SetMotionDetected(bool detected) noexcept { m_motionDetected = detected; }
    [[nodiscard]] int GetSensitivity() const noexcept { return m_sensitivity; }

    // Валидация параметра: чувствительность от 1 до 10
    void SetSensitivity(int sensitivity);
};

} // namespace smarthome

#endif // MOTION_SENSOR_HPP
