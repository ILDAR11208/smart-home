#include "base_device.hpp"

namespace smarthome {

std::string BaseDevice::Header() const {
    std::string roomName = m_room ? std::string(m_room->GetName()) : "Без комнаты";
    std::string status = m_isOnline ? "Онлайн" : "ОФЛАЙН";
    return "[ID " + std::to_string(m_id) + "] " + m_name + " (" + roomName + ", " + status + ")";
}

BaseDevice::BaseDevice()
    : m_id(NextId())
    , m_name("Безымянное устройство")
    , m_room(std::make_shared<Room>("Не назначена"))
    , m_isOnline(true) {
}

BaseDevice::BaseDevice(std::string_view name, std::shared_ptr<Room> room)
    : m_id(NextId())
    , m_name(name)
    , m_room(std::move(room))
    , m_isOnline(true) {
}

BaseDevice::BaseDevice(const BaseDevice& other)
    : m_id(NextId())
    , m_name(other.m_name)
    , m_room(other.m_room ? std::make_shared<Room>(*other.m_room) : nullptr)
    , m_isOnline(other.m_isOnline) {
}

BaseDevice::BaseDevice(BaseDevice&& other) noexcept
    : m_id(other.m_id)
    , m_name(std::move(other.m_name))
    , m_room(std::move(other.m_room))
    , m_isOnline(other.m_isOnline) {
    other.m_id = 0;
}

BaseDevice& BaseDevice::operator=(const BaseDevice& other) {
    if (this == &other) {
        return *this;
    }
    m_name = other.m_name;
    m_room = other.m_room ? std::make_shared<Room>(*other.m_room) : nullptr;
    m_isOnline = other.m_isOnline;
    return *this;
}

BaseDevice& BaseDevice::operator=(BaseDevice&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    m_id = other.m_id;
    m_name = std::move(other.m_name);
    m_room = std::move(other.m_room);
    m_isOnline = other.m_isOnline;
    other.m_id = 0;
    return *this;
}

BaseDevice::~BaseDevice() noexcept {
}

std::string BaseDevice::Describe() const {
    return Header() + ", опрос каждые " + std::to_string(GetPollInterval()) + " сек.";
}

void BaseDevice::Ping() const {
    if (!m_isOnline) {
        // Создание исключения предметной области при нарушении правила
        throw DeviceOfflineException(m_name, "устройство не отвечает на запросы сети!");
    }
    std::cout << "  [Ping OK] Устройство '" << m_name << "' успешно ответило на пинг." << std::endl;
}

void BaseDevice::RenameRoom(std::string_view newName) {
    if (m_room) {
        m_room->SetName(newName);
    }
}

} // namespace smarthome
