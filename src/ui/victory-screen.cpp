#include "victory-screen.h"

#include <ecs/queries.h>
#include <gameplay/game.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#include <array>
#include <format>
#include <string>
#include <utility>

void ui::drawVictoryScreen(Game& game) {
    const ImGuiViewport* const mainViewport{ ImGui::GetMainViewport() };
    ImGui::SetNextWindowPos(mainViewport->Pos);
    ImGui::SetNextWindowSize(mainViewport->Size);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.05f, 0.05f, 0.1f, 1.f });
    ImGui::Begin(
        "VictoryScreen",
        NULL,
        ImGuiWindowFlags_NoDecoration
        | ImGuiWindowFlags_NoSavedSettings
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus
    );
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();

    ImGui::PushFont(NULL, std::min(120.f, mainViewport->WorkSize.x * 0.1f));

    constexpr auto titleText{ "Victory!" };
    const float titleWidth{ ImGui::CalcTextSize(titleText).x };
    ImGui::SetCursorPos({
        (mainViewport->WorkSize.x - titleWidth) * 0.5f,
        std::min(150.f, mainViewport->WorkSize.y * 0.1f)
    });
    ImGui::TextUnformatted(titleText);

    ImGui::PopFont();
    ImGui::PushFont(NULL, 20.f);

    const Stats playerStats{ getPlayerStats(game.getRegistry()) };
    using namespace std::string_literals;
    const auto formattedStats{ std::array{
        "Congratulations, all invaders were DESTROYED!"s,
        std::format("Lost health: {}", playerStats.lostHealth),
        std::format("Bullets fired: {}", playerStats.firedBullets),
        std::format("Damage dealt: {}", playerStats.damageDealt)
    } };

    for (const auto& text : formattedStats) {
        const ImVec2 textSize{ ImGui::CalcTextSize(text.c_str()) };

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20.f);
        ImGui::SetCursorPosX((mainViewport->WorkSize.x - textSize.x) * 0.5f);
        ImGui::TextUnformatted(text.c_str());
    }

    ImGui::PushStyleColor(ImGuiCol_Button, { 0.35f, 0.35f, 0.2f, 1.f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.45f, 0.45f, 0.3f, 1.f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.55f, 0.55f, 0.4f, 1.f });

    constexpr auto mainMenuText{ "Main Menu" };
    const ImVec2 mainMenuTextSize{ ImGui::CalcTextSize(mainMenuText) };
    const float buttonWidth{ mainMenuTextSize.x + 170.f };
    ImGui::SetCursorPos({
        (mainViewport->WorkSize.x - buttonWidth) * 0.5f,
        ImGui::GetCursorPosY() + 30.f
    });

    if (ImGui::Button(mainMenuText, { buttonWidth, mainMenuTextSize.y + 30.f })) {
        game.setState(GameState::MainMenu);
    }

    ImGui::PopStyleColor(3);
    ImGui::PopFont();

    ImGui::End();
}
