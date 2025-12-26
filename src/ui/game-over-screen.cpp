#include "game-over-screen.h"

#include <gameplay/game.h>
#include <imgui.h>

void ui::drawGameOverScreen(Game& game) {
    ImGui::Begin("Hud Placeholder");
    ImGui::Text("Game Over!");
    if (ImGui::Button("Main Menu")) {
        game.setState(GameState::MainMenu);
    }
    ImGui::End();
}
