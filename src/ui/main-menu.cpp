#include "main-menu.h"
#include "settings-menu.h"

#include <gameplay/game.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#include <algorithm>

void ui::drawMainMenu(Game& game) {
    const ImGuiViewport* const mainViewport{ ImGui::GetMainViewport() };
    ImGui::SetNextWindowPos(mainViewport->Pos);
    ImGui::SetNextWindowSize(mainViewport->Size);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.05f, 0.05f, 0.1f, 1.f });
    ImGui::Begin(
        "MainMenu",
        NULL,
        ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoBringToFrontOnFocus
    );
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();

    constexpr int numButtons{ 3 };
    constexpr float padding{ 20.f };
    constexpr float buttonSpacing{ 10.f };

    const ImVec2 menuSize{
        std::clamp(mainViewport->WorkSize.x - 10.f, 50.f, 400.f),
        std::min(70.f * numButtons, std::max(40.f * numButtons, mainViewport->WorkSize.y - 10.f))
    };
    const ImVec2 buttonSize{
        menuSize.x - padding * 2.f,
        (menuSize.y - padding * 2.f - (numButtons - 1) * buttonSpacing) / numButtons
    };
    const ImVec2 center{ mainViewport->GetCenter() };

    ImGui::PushFont(NULL, std::min(120.f, mainViewport->WorkSize.x / 10.f));

    constexpr auto titleText{ "Cosmic Invaders" };
    const float titleWidth{ ImGui::CalcTextSize(titleText).x };
    ImGui::SetCursorPos({
        (mainViewport->WorkSize.x - titleWidth) * 0.5f,
        (center.y - menuSize.y) * 0.5f
    });
    ImGui::TextUnformatted(titleText);

    ImGui::PopFont();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ padding, padding });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.f, buttonSpacing });

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.15f, 0.15f, 0.2f, 1.f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.25f, 0.25f, 0.3f, 1.f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.35f, 0.35f, 0.4f, 1.f });

    ImGui::SetCursorPos(center - menuSize * 0.5f);
    ImGui::BeginChild("MenuPanel", menuSize, true, ImGuiWindowFlags_NoDecoration);

    static bool s_showSettings{};
    if (ImGui::Button("Play", buttonSize)) {
        s_showSettings = false;
        game.setState(GameState::Playing);
    }
    if (ImGui::Button("Settings", buttonSize)) {
        s_showSettings = true;
    }
    if (ImGui::Button("Quit", buttonSize)) {
        game.requestQuit();
    }

    ImGui::EndChild();

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(2);
    ImGui::End();

    drawSettingsMenu(game, s_showSettings);
}
