#include "pause-menu.h"

#include <gameplay/game.h>
#include <imgui.h>

void ui::drawPauseMenu(Game& game) {
    ImGui::Begin("Hud Placeholder");
    if (ImGui::Button("Resume")) {
        game.setState(GameState::Playing);
    }
    if (ImGui::Button("Main Menu")) {
        game.setState(GameState::MainMenu);
    }
    ImGui::End();
}
