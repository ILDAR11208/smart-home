#include "base_device.hpp"

namespace smarthome {

void Room::Report(const BaseDevice& device) const {
    std::cout << "  [Room::Report] Комната '" << m_name 
              << "' зафиксировала устройство: " << device.GetName() 
              << " (ID=" << device.GetId() << ")" << std::endl;
}

std::string BaseDevice::Header() const {
    std::string roomName = m_room ? std::string(m_room->GetName()) : "Без комнаты";
    return "[ID " + std::to_string(m_id) + "] " + m_name + " (Комната: " + roomName + ")";
}

BaseDevice::BaseDevice()
    : m_id(NextId()), m_name("Безымянное устройство"), m_room(std::make_shared<Room>("Не назначена")) {
    std::cout << "[BaseDevice::BaseDevice()] Создана база по умолчанию ID=" << m_id << std::endl;
}

BaseDevice::BaseDevice(std::string_view name, std::shared_ptr<Room> room)
    : m_id(NextId()), m_name(name), m_room(std::move(room)) {
    std::cout << "[BaseDevice::BaseDevice(params)] Создана база '" << m_name << "' ID=" << m_id << std::endl;
}

BaseDevice::BaseDevice(const BaseDevice& other)
    : m_id(NextId()) // новому клону выдаётся собственный уникальный ID
    , m_name(other.m_name)
    , m_room(other.m_room ? std::make_shared<Room>(*other.m_room) : nullptr) // Глубокая копия вложенного объекта
{
    std::cout << "[BaseDevice::BaseDevice(copy)] Глубокая копия базы '" << m_name << "' -> новый ID=" << m_id << std::endl;
}

BaseDevice::BaseDevice(BaseDevice&& other) noexcept
    : m_id(other.m_id)
    , m_name(std::move(other.m_name))
    , m_room(std::move(other.m_room)) {
    other.m_id = 0;
    std::cout << "[BaseDevice::BaseDevice(move)] Перемещение базы ID=" << m_id << std::endl;
}

BaseDevice& BaseDevice::operator=(const BaseDevice& other) {
    std::cout << "[BaseDevice::operator=] Копирующее присваивание" << std::endl;
    // 1. Проверка самоприсваивания через указатель this
    if (this == &other) {
        std::cout << "  -> Обнаружено самоприсваивание (this == &other), действие пропущено." << std::endl;
        return *this;
    }
    m_name = other.m_name;
    // Глубокое копирование ресурса
    m_room = other.m_room ? std::make_shared<Room>(*other.m_room) : nullptr;
    // 2. Возврат *this для поддержки цепочки присваиваний a = b = c
    return *this;
}

BaseDevice& BaseDevice::operator=(BaseDevice&& other) noexcept {
    std::cout << "[BaseDevice::operator=(move)] Перемещающее присваивание" << std::endl;
    if (this == &other) {
        return *this;
    }
    m_id = other.m_id;
    m_name = std::move(other.m_name);
    m_room = std::move(other.m_room);
    other.m_id = 0;
    return *this;
}

BaseDevice::~BaseDevice() {
    std::cout << "[~BaseDevice()] Уничтожена база '" << m_name << "' ID=" << m_id << std::endl;
}

std::string BaseDevice::Describe() const {
    return Header() + ", опрос каждые " + std::to_string(GetPollInterval()) + " сек.";
}

void BaseDevice::AttachToRoom(Room& room) const {
    // 3. Передача текущего объекта другому объекту через разыменование this (*this)
    room.Report(*this);
}

void BaseDevice::RenameRoom(std::string_view newName) {
    if (m_room) {
        m_room->SetName(newName);
    }
}

} // namespace smarthome
