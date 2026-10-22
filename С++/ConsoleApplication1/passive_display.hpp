#ifndef PASSIVE_DISPLAY_HPP
#define PASSIVE_DISPLAY_HPP

#include "base_device.hpp"

namespace smarthome {

/// <summary>
/// Пассивное настенное табло (наследуется ТОЛЬКО от BaseDevice, НЕ реализует IControllable).
/// Используется для демонстрации dynamic_cast: табло нельзя удаленно выключить или послать команду.
/// </summary>
class PassiveDisplay : public BaseDevice {
private:
    std::string m_displayedText;

public:
    PassiveDisplay(std::string_view name, std::shared_ptr<Room> room, std::string_view text)
        : BaseDevice(name, std::move(room)), m_displayedText(text) {
    }

    [[nodiscard]] std::string GetDeviceType() const {
        return "Информационное табло";
    }

    [[nodiscard]] int GetPollInterval() const override {
        return 60;
    }

    [[nodiscard]] std::string Describe() const override {
        return "Табло: " + Header() + " -> [Экран: \"" + m_displayedText + "\"]";
    }

    [[nodiscard]] std::unique_ptr<BaseDevice> Clone() const override {
        return std::make_unique<PassiveDisplay>(*this);
    }
};

} // namespace smarthome

#endif // PASSIVE_DISPLAY_HPP
