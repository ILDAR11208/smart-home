#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <string_view>
#include <iostream>

namespace smarthome {

class BaseDevice; // Опережающее объявление для демонстрации this

class Room {
private:
    std::string m_name;

public:
    Room() : m_name("Общая зона") {
        std::cout << "  [Room::Room()] Создана комната по умолчанию: " << m_name << std::endl;
    }

    explicit Room(std::string_view name) : m_name(name) {
        std::cout << "  [Room::Room(name)] Создана комната: " << m_name << std::endl;
    }

    Room(const Room& other) : m_name(other.m_name) {
        std::cout << "  [Room::Room(copy)] Скопирована комната: " << m_name << std::endl;
    }

    ~Room() {
        std::cout << "  [Room::~Room()] Удалена комната: " << m_name << std::endl;
    }

    [[nodiscard]] std::string_view GetName() const {
        return m_name;
    }

    void SetName(std::string_view name) {
        m_name = name;
    }

    // Демонстрация this: метод принимает ссылку на BaseDevice, переданную через *this
    void Report(const BaseDevice& device) const;
};

} // namespace smarthome

#endif // ROOM_HPP
