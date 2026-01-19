#include "game.h"

#include <core/gl-window.h>

#include <ui/main-menu.h>
#include <ui/hud.h>
#include <ui/pause-menu.h>
#include <ui/game-over-screen.h>
#include <ui/victory-screen.h>

#include <ecs/systems.h>
#include <ecs/queries.h>

#include "levels.h"

#include <iostream>

Game::Game(const GlWindow& window) noexcept
    : m_inputManager{ window.getNativeHandle() }
{}

void Game::update(double dt) {
    m_fpsCounter.update(dt);
    m_inputManager.update();

    dt *= m_settings.gameSpeed;

    switch (m_gameState) {
    case GameState::MainMenu:
        ui::drawMainMenu(*this);
        break;
    case GameState::Playing:
        ui::drawHud(*this, dt);
        if (m_inputManager.isPressed(InputManager::Escape)) {
            m_gameState = GameState::Paused;
        }
        updateSystems(dt);
        break;
    case GameState::Paused:
        ui::drawHud(*this, dt);
        ui::drawPauseMenu(*this);
        if (m_inputManager.isPressed(InputManager::Escape)) {
            m_gameState = GameState::Playing;
        }
        break;
    case GameState::GameOver:
        ui::drawGameOverScreen(*this);
        break;
    case GameState::Victory:
        ui::drawVictoryScreen(*this);
        break;
    default:
        break;
    }
}

void Game::render(Renderer& renderer) {
    switch (m_gameState) {
    case GameState::Playing:
        //std::cout << "W" << "\n";
        renderingSystem(m_registry, renderer);
        break;
    case GameState::Paused:
        // TODO: Render the ECS entities
        break;
    case GameState::MainMenu:
    case GameState::GameOver:
    case GameState::Victory:
    default:
        break;
    }
}

void Game::loadPlayer() {
    constexpr auto playerPath{ "assets/3d-models/Battle-SpaceShip-Free-3D-Low-Poly-Models/Destroyer_01.fbx" };

    m_enemyIdx = 0;
    m_currentLevel = 0;
    m_timePassed = 0;

    m_registry.clear();

    createPlayer(m_registry, m_modelStore.load(playerPath, 0.0003f), glm::vec3{ 0.f, -2.f, -7.f });
}

void Game::updateSystems(const double dt) {

    if (!isPlayerAlive(m_registry)) {
        m_gameState = GameState::GameOver;
        return;
    }

    m_timePassed += dt;

    if (gameplay::levels.size() <= m_currentLevel) {
        m_gameState = GameState::Victory;
        return;
    }

    if (gameplay::levels[m_currentLevel].spawns.size() <= m_enemyIdx) {
        if (m_currentLevel < gameplay::levels.size() && !enemyExists(m_registry)) {
            ++m_currentLevel;
            m_enemyIdx = 0;
            m_timePassed = 0;
            restorePlayerHealthSystem(m_registry);
        }
    }
    else if (gameplay::levels[m_currentLevel].spawns[m_enemyIdx].spawnTime < m_timePassed * 1000) {
        auto enemyType{ gameplay::levels[m_currentLevel].spawns[m_enemyIdx].enemyType };
        auto lane{ gameplay::levels[m_currentLevel].spawns[m_enemyIdx].lane };
        createEntity(m_registry, enemyType, m_modelStore, lane);
        ++m_enemyIdx;
    }

    cleanUpSystem(m_registry);
    enemyShootingSystem(m_registry, m_modelStore, dt);
    receivingDamageSystem(m_registry, dt);
    playerInputSystem(m_registry, m_inputManager, m_modelStore, m_audioEngine, dt);
    movementSystem(m_registry, dt);
}

