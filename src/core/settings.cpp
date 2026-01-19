#define SETTINGS_H_NO_X_MACRO_UNDEF
#include "settings.h"

#include <nlohmann/json.hpp>

#include <fstream>

using json = nlohmann::json;

Settings::Settings(const std::filesystem::path& path)
        : m_configPath{ path } {
    std::ifstream file{ m_configPath };
    if (!file) {
        return;
    }

    json data{ json::parse(file) };

#define X(type, name, val) name = data.value(#name, val);
    SETTINGS_H_CONFIG
#undef X
}

bool Settings::saveToFile() const {
    std::ofstream file{ m_configPath };
    if (!file) {
        return false;
    }

    json data{};

#define X(type, name, value) data[#name] = name;
    SETTINGS_H_CONFIG
#undef X

    file << data;
    return true;
}
