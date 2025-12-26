#include "hud.h"

#include <gameplay/game.h>
#include <imgui.h>

void ui::drawHud(Game& game) {
    ImGui::Begin("Hud Placeholder");
    ImGui::Text("Fps: %lf", game.getFps());
    ImGui::Text("Press ESCAPE to open the pause menu.");
    ImGui::End();
}
