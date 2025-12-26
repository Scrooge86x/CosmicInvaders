#include "pause-menu.h"

#include <gameplay/game.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#include <algorithm>

void ui::drawPauseMenu(Game& game) {
    const ImGuiViewport* const mainViewport{ ImGui::GetMainViewport() };
    ImGui::SetNextWindowPos(mainViewport->Pos);
    ImGui::SetNextWindowSize(mainViewport->Size);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.f, 0.f, 0.f, 0.6f });
    ImGui::Begin(
        "PauseMenu",
        nullptr,
        ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_NoMove
    );
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();

    constexpr int numButtons{ 4 };
    constexpr float padding{ 20.f };
    constexpr float buttonSpacing{ 10.f };

    const ImVec2 menuSize{
        std::clamp(mainViewport->WorkSize.x - 10.f, 50.f, 400.f),
        std::min(70.f * numButtons, std::max(40.f * numButtons, mainViewport->WorkSize.y - 10.f))
    };
    const ImVec2 buttonSize{
        menuSize.x - padding * 2.f,
        (menuSize.y - padding * 2.f) / numButtons - buttonSpacing
    };

    const ImVec2 center{ mainViewport->GetCenter() };
    ImGui::SetCursorPos(center - menuSize * 0.5f);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ padding, padding });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.f, buttonSpacing });

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{ 0.05f, 0.05f, 0.05f, 1.f });
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.15f, 0.15f, 0.15f, 1.f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.25f, 0.25f, 0.25f, 1.f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.35f, 0.35f, 0.35f, 1.f });

    ImGui::BeginChild("MenuPanel", menuSize, true, ImGuiWindowFlags_NoDecoration);

    ImGui::PushFont(NULL, std::min(40.f, mainViewport->WorkSize.x / 10.f));

    constexpr auto titleText{ "Cosmic Invaders" };
    const float titleWidth{ ImGui::CalcTextSize(titleText).x };
    ImGui::SameLine((menuSize.x - titleWidth) * 0.5f);

    ImGui::TextUnformatted(titleText);
    ImGui::Spacing();

    ImGui::PopFont();

    if (ImGui::Button("Resume", buttonSize)) {
        game.setState(GameState::Playing);
    }
    if (ImGui::Button("Settings", buttonSize)) {
        // TODO: ui::drawSettings(game);
    }
    if (ImGui::Button("Main Menu", buttonSize)) {
        game.setState(GameState::MainMenu);
    }

    ImGui::EndChild();

    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar(2);
    ImGui::End();
}
