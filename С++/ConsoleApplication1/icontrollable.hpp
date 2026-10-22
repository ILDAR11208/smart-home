#ifndef ICONTROLLABLE_HPP
#define ICONTROLLABLE_HPP

#include <string_view>

namespace smarthome {

/// <summary>
/// Интерфейс-контракт управляемого устройства умного дома (по маске I*).
/// Не содержит полей. Все методы чисто виртуальные.
/// Виртуальный деструктор по умолчанию.
/// </summary>
class IControllable {
public:
    virtual ~IControllable() = default;

    virtual void TurnOn() = 0;
    virtual void TurnOff() = 0;
    [[nodiscard]] virtual bool IsActive() const = 0;
    virtual void ExecuteCommand(std::string_view command) = 0;
};

} // namespace smarthome

#endif // ICONTROLLABLE_HPP
