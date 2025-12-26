#include "main-menu.h"

#include <gameplay/game.h>
#include <imgui.h>

void ui::drawMainMenu(Game& game) {
    ImGui::Begin("Main Menu Placeholder");
    if (ImGui::Button("Play")) {
        game.setState(GameState::Playing);
    }
    if (ImGui::Button("Quit")) {
        game.requestQuit();
    }
    ImGui::End();
}
