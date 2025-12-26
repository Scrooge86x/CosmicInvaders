#include "settings-menu.h"

#include <core/settings.h>
#include <gameplay/game.h>

#include <imgui.h>

void ui::drawSettingsMenu(Game& game, bool& isOpen) {
    if (!isOpen) {
        return;
    }

    Settings& settings{ game.getSettings() };

    ImGui::Begin("Settings", &isOpen);
    ImGui::Checkbox("Show fps", &settings.showFps);
    if (ImGui::Button("Save settings")) {
        settings.saveToFile();
    }
    ImGui::End();
}
