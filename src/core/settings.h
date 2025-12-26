#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

#include <filesystem>

#define SETTINGS_H_CONFIG \
    X(float, modelScale, 4.f) \
    X(float, rotationSpeed, 0.5f)

class Settings {
public:
#define X(type, name, value) type name{ value };
    SETTINGS_H_CONFIG
#undef X

public:
    explicit Settings(const std::filesystem::path& path);

    bool saveToFile() const;

private:
    std::filesystem::path m_configPath{};
};

#ifndef SETTINGS_H_NO_X_MACRO_UNDEF
    #undef SETTINGS_H_CONFIG
#endif // SETTINGS_H_NO_X_MACRO_UNDEF


#endif // SETTINGS_H
