#include "victory-screen.h"

#include <gameplay/game.h>
#include <imgui.h>

void ui::drawVictoryScreen(Game& game) {
    ImGui::Begin("Victory Screen Placeholder");
    ImGui::Text("You Won!");
    if (ImGui::Button("Main Menu")) {
        game.setState(GameState::MainMenu);
    }
    ImGui::End();
}
