#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <string_view>
#include <iostream>

namespace smarthome {

class Room {
private:
    std::string m_name;

public:
    Room() : m_name("Общая зона") {}
    explicit Room(std::string_view name) : m_name(name) {}

    [[nodiscard]] std::string_view GetName() const noexcept {
        return m_name;
    }

    void SetName(std::string_view name) {
        m_name = name;
    }
};

} // namespace smarthome

#endif // ROOM_HPP
