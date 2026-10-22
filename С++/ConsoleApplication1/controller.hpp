#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include <string_view>

namespace smarthome {

class Controller {
private:
    std::string m_firmwareVersion;
    bool m_hasActiveErrors;

public:
    Controller(std::string_view firmware);
    ~Controller();

    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;

    void RunDiagnostics();
    void ProcessData(float sensorValue);
    bool HasErrors() const;
};

} // namespace smarthome

#endif // CONTROLLER_HPP
