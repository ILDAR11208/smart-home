#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <string_view>
#include <iostream>

namespace smarthome {

/// <summary>
/// Демонстрация работы со строками std::string по теме проекта:
/// конкатенация (+, +=), поиск (find), подстрока (substr), сравнение (==).
/// </summary>
class StringUtils {
public:
    // Нормализация серийного номера: удаляет лишние дефисы и пробелы, переводит в верхний регистр
    static std::string NormalizeCode(std::string_view rawCode) {
        std::string result;
        for (char ch : rawCode) {
            if (ch != '-' && ch != ' ' && ch != '_') {
                result += static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
            }
        }
        return result;
    }

    // Демонстрация поиска, выделения подстроки и сравнения
    static void DemonstrateStringOperations() {
        std::cout << "\n--- Демонстрация операций со строками std::string ---" << std::endl;

        // 1. Конкатенация
        std::string prefix = "DEVICE";
        std::string type = "TEMP";
        std::string serial = prefix + "-" + type; // оператор +
        serial += "-2026-X";                      // оператор +=
        std::cout << "1. Конкатенация (+, +=): '" << serial << "'" << std::endl;

        // 2. Поиск подстроки (find)
        std::size_t foundPos = serial.find("TEMP");
        if (foundPos != std::string::npos) {
            std::cout << "2. Поиск (find): подстрока 'TEMP' найдена на позиции " << foundPos << std::endl;

            // 3. Выделение подстроки (substr)
            std::string sub = serial.substr(foundPos, 4);
            std::cout << "3. Выделение подстроки (substr): '" << sub << "'" << std::endl;
        }

        // 4. Сравнение строк (==)
        std::string expected = "DEVICE-TEMP-2026-X";
        if (serial == expected) {
            std::cout << "4. Сравнение (==): серийный номер совпадает с эталоном '" << expected << "'" << std::endl;
        }

        // 5. Функция нормализации
        std::string rawInput = "sn - temp - 101 - ok";
        std::string clean = NormalizeCode(rawInput);
        std::cout << "5. Нормализация кода: из '" << rawInput << "' -> '" << clean << "'" << std::endl;
    }
};

} // namespace smarthome

#endif // STRING_UTILS_HPP
