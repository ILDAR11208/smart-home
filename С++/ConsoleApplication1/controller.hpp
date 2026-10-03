// controller.hpp
#pragma once

#include <string>
#include <string_view>

namespace smarthome
{

    class Controller
    {
    private:
        std::string m_firmwareVersion;
        bool m_hasActiveErrors;

    public:
        Controller(std::string_view firmware);
        ~Controller();

        // Содержательные методы
        void RunDiagnostics();
        void ProcessData(float sensorValue);

        [[nodiscard]] bool HasErrors() const;
    };

} // namespace smarthome