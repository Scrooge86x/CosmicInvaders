#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

#include <filesystem>

#define SETTINGS_H_CONFIG \
    X(bool, showFps, true)

/**
 * @brief Application configuration container.
 *
 * Loads and saves configuration values defined
 * by SETTINGS_H_CONFIG in JSON format.
 */
class Settings {
public:
#define X(type, name, value) type name{ value };
    SETTINGS_H_CONFIG
#undef X

public:
    /**
     * @brief Loads settings from a file.
     * @param path Path to the configuration file.
     */
    explicit Settings(const std::filesystem::path& path);

    /**
     * @brief Saves settings to disk.
     * @return True on success.
     */
    bool saveToFile() const;

private:
    std::filesystem::path m_configPath{};
};

#ifndef SETTINGS_H_NO_X_MACRO_UNDEF
    #undef SETTINGS_H_CONFIG
#endif // SETTINGS_H_NO_X_MACRO_UNDEF


#endif // SETTINGS_H
