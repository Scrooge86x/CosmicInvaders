#include "game.h"

#include <ui/main-menu.h>
#include <ui/hud.h>
#include <ui/pause-menu.h>
#include <ui/game-over-screen.h>

Game::Game(InputManager& inputManager)
    : m_inputManager{ inputManager }
{}

void Game::update() {
    m_timer.update();
    m_fpsCounter.update(m_timer.getDt<double>());

    switch (m_gameState) {
    case GameState::MainMenu:
        ui::drawMainMenu(*this);
        break;
    case GameState::Playing:
        ui::drawHud(*this);
        if (m_inputManager.isPressed(InputManager::Escape)) {
            m_gameState = GameState::Paused;
        }
        break;
    case GameState::Paused:
        ui::drawPauseMenu(*this);
        break;
    case GameState::GameOver:
        ui::drawGameOverScreen(*this);
        break;
    default:
        break;
    }
}
