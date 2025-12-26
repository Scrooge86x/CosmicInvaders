#include "hud.h"

#include <gameplay/game.h>
#include <imgui.h>
#include <format>

void ui::drawHud(Game& game) {
    const ImGuiViewport* const mainViewport{ ImGui::GetMainViewport() };
    ImDrawList* const drawList{ ImGui::GetForegroundDrawList() };

    const std::string fpsText{ std::format("{:.2f} FPS", game.getFps()) };
    const ImVec2 textSize{ ImGui::CalcTextSize(fpsText.c_str()) };

    constexpr float padding{ 10.f };
    drawList->AddText(
        { mainViewport->WorkSize.x - textSize.x - padding, padding },
        IM_COL32_WHITE,
        fpsText.c_str()
    );
}
