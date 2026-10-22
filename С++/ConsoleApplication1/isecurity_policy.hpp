#ifndef ISECURITY_POLICY_HPP
#define ISECURITY_POLICY_HPP

#include <string>
#include <string_view>
#include <iostream>

namespace smarthome {

/// <summary>
/// Интерфейс объекта поведения: стратегия реагирования на тревогу (по маске I*).
/// </summary>
class ISecurityPolicy {
public:
    virtual ~ISecurityPolicy() = default;

    [[nodiscard]] virtual std::string_view GetPolicyName() const = 0;
    virtual void OnAlarm(std::string_view deviceName, int severity) const = 0;
};

/// <summary>
/// Реализация 1: Стандартная политика охраны (логирование и мягкий сигнал).
/// </summary>
class StandardSecurityPolicy : public ISecurityPolicy {
public:
    [[nodiscard]] std::string_view GetPolicyName() const override {
        return "Стандартный режим (Дневной)";
    }

    void OnAlarm(std::string_view deviceName, int severity) const override {
        std::cout << "  [StandardSecurity] Предупреждение от '" << deviceName 
                  << "' (уровень " << severity << "): включен свет и подан мягкий сигнал." << std::endl;
    }
};

/// <summary>
/// Реализация 2: Усиленная политика охраны (блокировка и сирена).
/// </summary>
class StrictSecurityPolicy : public ISecurityPolicy {
public:
    [[nodiscard]] std::string_view GetPolicyName() const override {
        return "Усиленный режим (Охрана периметра)";
    }

    void OnAlarm(std::string_view deviceName, int severity) const override {
        std::cout << "  [StrictSecurity] ВНИМАНИЕ! ТРЕВОГА от '" << deviceName 
                  << "' (уровень " << severity << "): двери заблокированы, включена сирена, отправлен сигнал в полицию!" << std::endl;
    }
};

/// <summary>
/// Реализация 3: Тихий режим (ночной).
/// </summary>
class SilentSecurityPolicy : public ISecurityPolicy {
public:
    [[nodiscard]] std::string_view GetPolicyName() const override {
        return "Ночной тихий режим (Push-уведомления)";
    }

    void OnAlarm(std::string_view deviceName, int severity) const override {
        std::cout << "  [SilentSecurity] Беззвучное оповещение от '" << deviceName 
                  << "': пуш-уведомление отправлено на смартфон владельца." << std::endl;
    }
};

} // namespace smarthome

#endif // ISECURITY_POLICY_HPP
