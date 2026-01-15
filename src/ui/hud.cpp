#include "hud.h"

#include <ecs/queries.h>
#include <gameplay/game.h>

#include <imgui.h>
#include <format>

void ui::drawHud(Game& game) {
    const ImGuiViewport* const mainViewport{ ImGui::GetMainViewport() };
    ImDrawList* const drawList{ ImGui::GetBackgroundDrawList() };
    constexpr float padding{ 10.f };

    if (game.getSettings().showFps) {
        const std::string fpsText{ std::format("{:.2f} FPS", game.getFps()) };

        drawList->AddText(
            { mainViewport->WorkSize.x - ImGui::CalcTextSize(fpsText.c_str()).x - padding, padding },
            IM_COL32_WHITE,
            fpsText.c_str()
        );
    }

    ImGui::PushFont(NULL, 25.f);
    const std::string levelText{ std::format("Level {}", game.getCurrentLevel() + 1) };

    drawList->AddText(
        { (mainViewport->WorkSize.x - ImGui::CalcTextSize(levelText.c_str()).x) / 2.f, padding },
        IM_COL32_WHITE,
        levelText.c_str()
    );

    const std::string hpText{ std::format("Health: {}", getPlayerHealth(game.getRegistry())) };
    const ImVec2 hpTextSize{ ImGui::CalcTextSize(hpText.c_str()) };
    drawList->AddText(
        {
            (mainViewport->WorkSize.x - hpTextSize.x) / 2.f,
            mainViewport->WorkSize.y - hpTextSize.y - padding
        },
        IM_COL32_WHITE,
        hpText.c_str()
    );
    ImGui::PopFont();
}
