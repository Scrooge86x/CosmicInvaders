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
    ImGui::SliderFloat("Game speed", &settings.gameSpeed, 0.4f, 1.5f);
    ImGui::SliderFloat("Volume", &settings.volume, 0.f, 1.f);
    if (ImGui::IsItemDeactivatedAfterEdit()) {
        game.getAudioEngine().setVolume(settings.volume);
    }
    if (ImGui::Button("Save settings")) {
        settings.saveToFile();
    }
    ImGui::End();
}
