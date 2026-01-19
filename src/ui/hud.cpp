#include "hud.h"

#include <ecs/queries.h>
#include <ecs/components.h>
#include <gameplay/game.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#include <algorithm>
#include <cmath>
#include <format>

void ui::drawHud(Game& game, const double dt) {
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

    static auto previousLevel{ game.getCurrentLevel() };
    const auto currentLevel{ game.getCurrentLevel() + 1 };

    static double zoomedLevelTime{};
    if (previousLevel != currentLevel) {
        zoomedLevelTime = 1.5;
    }
    previousLevel = currentLevel;

    const std::string levelText{ std::format("Level {}", currentLevel) };
    if (zoomedLevelTime > 0.0) {
        zoomedLevelTime -= dt;

        ImGui::PushFont(NULL, 50.f);
        const ImVec2 levelTextSize{ ImGui::CalcTextSize(levelText.c_str()) };
        drawList->AddText(
            {
                (mainViewport->WorkSize.x - levelTextSize.x) / 2.f,
                (mainViewport->WorkSize.y - levelTextSize.y) / 2.f,
            },
            IM_COL32_WHITE,
            levelText.c_str()
        );
    } else {
        ImGui::PushFont(NULL, 25.f);
        drawList->AddText(
            {
                (mainViewport->WorkSize.x - ImGui::CalcTextSize(levelText.c_str()).x) / 2.f,
                padding
            },
            IM_COL32_WHITE,
            levelText.c_str()
        );
    }

    ImGui::PopFont();

    const Health playerHealth{ getPlayerHealth(game.getRegistry()) };
    const float healthPercentage{ std::clamp(static_cast<float>(playerHealth.current) / playerHealth.max, 0.f, 1.f) };
    ImU32 healthColor{};
    switch (std::lround(healthPercentage * 3)) {
    case 0: healthColor = IM_COL32(255, 0, 0, 255); break;
    case 1: healthColor = IM_COL32(255, 127, 0, 255); break;
    case 2: healthColor = IM_COL32(255, 255, 0, 255); break;
    case 3: healthColor = IM_COL32(0, 255, 0, 255); break;
    }

    ImGui::PushFont(NULL, 25.f);

    const std::string hpText{ std::format("Health: {}", playerHealth.current) };
    const ImVec2 hpTextSize{ ImGui::CalcTextSize(hpText.c_str()) };
    const ImVec2 hpBoxTopLeft{
        (mainViewport->WorkSize.x - hpTextSize.x) / 2.f,
        mainViewport->WorkSize.y - hpTextSize.y - padding * 3
    };

    drawList->AddText(
        hpBoxTopLeft,
        healthColor,
        hpText.c_str()
    );

    ImGui::PopFont();

    drawList->AddRectFilled(
        hpBoxTopLeft + ImVec2{ 0.f, hpTextSize.y + padding },
        hpBoxTopLeft + ImVec2{ hpTextSize.x * healthPercentage, hpTextSize.y + padding * 2 },
        healthColor
    );

    drawList->AddRect(
        hpBoxTopLeft + ImVec2{ 0.f, hpTextSize.y + padding },
        hpBoxTopLeft + ImVec2{ hpTextSize.x, hpTextSize.y + padding * 2 },
        IM_COL32_WHITE,
        0.f,
        ImDrawFlags_None,
        2.f
    );
}
