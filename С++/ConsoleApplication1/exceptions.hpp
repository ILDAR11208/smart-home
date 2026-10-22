#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>
#include <string_view>

namespace smarthome {

/// <summary>
/// Исключение предметной области: устройство недоступно или отключено от сети.
/// Наследник std::runtime_error (ошибка времени выполнения).
/// </summary>
class DeviceOfflineException : public std::runtime_error {
private:
    std::string m_deviceName;

public:
    explicit DeviceOfflineException(std::string_view deviceName, std::string_view message)
        : std::runtime_error("Ошибка сети [Офлайн]: '" + std::string(deviceName) + "' — " + std::string(message))
        , m_deviceName(deviceName) {
    }

    [[nodiscard]] std::string_view GetDeviceName() const noexcept {
        return m_deviceName;
    }
};

/// <summary>
/// Исключение предметной области: передан недопустимый параметр конфигурации.
/// Наследник std::logic_error (логическая ошибка параметров).
/// </summary>
class InvalidParameterException : public std::logic_error {
private:
    std::string m_parameterName;

public:
    explicit InvalidParameterException(std::string_view paramName, std::string_view reason)
        : std::logic_error("Ошибка валидации параметра '" + std::string(paramName) + "': " + std::string(reason))
        , m_parameterName(paramName) {
    }

    [[nodiscard]] std::string_view GetParameterName() const noexcept {
        return m_parameterName;
    }
};

} // namespace smarthome

#endif // EXCEPTIONS_HPP
