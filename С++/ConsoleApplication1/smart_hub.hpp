#ifndef SMART_HUB_HPP
#define SMART_HUB_HPP

#include "isecurity_policy.hpp"
#include "icontrollable.hpp"
#include "base_device.hpp"
#include <memory>
#include <string>
#include <string_view>
#include <iostream>

namespace smarthome {

/// <summary>
/// Главный контроллер умного дома (SmartHub).
/// Демонстрирует:
/// 1. Конфигурирование поведения через объект поведения (стратегию ISecurityPolicy).
///    Объект хранит политику в std::unique_ptr<ISecurityPolicy>.
/// 2. Работу с устройствами через интерфейс-контракт IControllable без знания конкретных классов.
/// 3. Проверку типа во время выполнения через dynamic_cast.
/// </summary>
class SmartHub {
private:
    std::string m_hubName;
    std::unique_ptr<ISecurityPolicy> m_policy; // Объект поведения

public:
    // Статическое конфигурирование: политика задаётся при создании
    SmartHub(std::string_view name, std::unique_ptr<ISecurityPolicy> policy)
        : m_hubName(name), m_policy(std::move(policy)) {
        std::cout << "[SmartHub] Хаб '" << m_hubName << "' запущен. Активная политика: " 
                  << m_policy->GetPolicyName() << std::endl;
    }

    // Динамическое конфигурирование: смена объекта поведения во время работы программы
    void SetSecurityPolicy(std::unique_ptr<ISecurityPolicy> newPolicy) {
        std::cout << "\n[SmartHub] Смена политики охраны: '" << m_policy->GetPolicyName() 
                  << "' -> '" << newPolicy->GetPolicyName() << "'" << std::endl;
        m_policy = std::move(newPolicy);
    }

    // Делегирование действия объекту поведения
    void RaiseAlarm(std::string_view deviceName, int severity) const {
        std::cout << "[SmartHub] Зафиксировано тревожное событие! Передача объекту политики..." << std::endl;
        m_policy->OnAlarm(deviceName, severity);
    }

    // 2. Использование интерфейса: функция работает с объектом через IControllable
    // и совершенно ничего не знает о конкретном классе (TemperatureSensor или MotionSensor)!
    void SendEmergencyCommand(IControllable& device, std::string_view command) {
        std::cout << "  [SmartHub -> IControllable] Отправка управляющей команды через интерфейс..." << std::endl;
        device.ExecuteCommand(command);
    }

    // 5. Проверка типа во время выполнения через dynamic_cast
    void TryToggleDevice(BaseDevice& device) {
        std::cout << "  Проверка возможности управления устройством '" << device.GetName() << "'..." << std::endl;
        if (auto* controllable = dynamic_cast<IControllable*>(&device)) {
            // Успешный dynamic_cast: объект реализует интерфейс IControllable
            std::cout << "  -> dynamic_cast успешен! Устройство поддерживает IControllable." << std::endl;
            if (controllable->IsActive()) {
                controllable->TurnOff();
            } else {
                controllable->TurnOn();
            }
        } else {
            // dynamic_cast вернул nullptr: объект не реализует интерфейс
            std::cout << "  -> dynamic_cast вернул nullptr! Устройство '" << device.GetName() 
                      << "' является пассивным и НЕ поддерживает интерфейс управления IControllable." << std::endl;
        }
    }
};

} // namespace smarthome

#endif // SMART_HUB_HPP
