#include "game.h"

#include <ui/main-menu.h>
#include <ui/hud.h>
#include <ui/pause-menu.h>
#include <ui/game-over-screen.h>

#include <ecs/systems.h>

#include <iostream>

Game::Game(InputManager& inputManager)
    : m_inputManager{ inputManager }
{}

void Game::update(const double dt) {
    m_fpsCounter.update(dt);

    switch (m_gameState) {
    case GameState::MainMenu:
        ui::drawMainMenu(*this);
        break;
    case GameState::Playing:
        ui::drawHud(*this);
        if (m_inputManager.isPressed(InputManager::Escape)) {
            m_gameState = GameState::Paused;
        }
        updateSystems(dt);
        break;
    case GameState::Paused:
        ui::drawHud(*this);
        ui::drawPauseMenu(*this);
        if (m_inputManager.isPressed(InputManager::Escape)) {
            m_gameState = GameState::Playing;
        }
        break;
    case GameState::GameOver:
        ui::drawGameOverScreen(*this);
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
    default:
        break;
    }
}

void Game::loadEntities() {
    std::cout << "W?" << "\n";
    constexpr auto playerPath{"assets/3d-models/Battle-SpaceShip-Free-3D-Low-Poly-Models/Destroyer_01.fbx"};

    m_registry.clear();

    createEntity(m_registry, m_modelStore.load(playerPath, 0.0003f), glm::vec3{ -3.75f, -2.f, -17.f });
    createEntity(m_registry, m_modelStore.load(playerPath, 0.0003f), glm::vec3{ 0.f, -2.f, -17.f });
    createEntity(m_registry, m_modelStore.load(playerPath, 0.0003f), glm::vec3{ 3.75f, -2.f, -17.f });

    //createPlayer(m_registry, m_modelStore.load(playerPath, 0.0003f), glm::vec3{ 0.f, -2.f, -7.f });
}

void Game::updateSystems(const double dt) {
    //std::cout << "W" << "\n";
    cleanUpSystem(m_registry);
    enemyShootingSystem(m_registry, m_modelStore, dt);
    receivingDamageSystem(m_registry, dt);
    playerInputSystem(m_registry, m_inputManager, m_modelStore, dt);
    movementSystem(m_registry, dt);
}

