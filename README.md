# <center>Cosmic Invaders </center>

## Introduction

Cosmic Invaders is a 3D game inspired by old classic, "Space Invaders". It is built using C++, OpenGL and ECS architecture with EnTT.

## Screenshots

Main menu (running on [WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux))  

Game over screen (running on windows 11)  
<img width="902" height="632" alt="game-over-on-windows-11" src="https://github.com/user-attachments/assets/af7c565a-801c-46a8-837c-c3b6d9f9b0fa" />

Victory screen (running on kubuntu)  
<img width="904" height="633" alt="victory-screen-on-kubuntu" src="https://github.com/user-attachments/assets/f5ee6ba0-8455-47e2-b52e-04a3f7aaccd9" />

## Prerequisites

- CMake 3.30 or newer
- C++20 compatible compiler

## Building

1. Clone or download zip of repository.
2. Open terminal/cmd inside of decompressed folder.
3. Run `cmake -S . -B build`
4. `cmake --build build`

## How to Play

### Movement

Use the A and D keys to move your character left and right, avoiding incoming enemy projectiles.

### Attacking

Press and hold the Spacebar to fire bullets. Each hit deals 30 HP damage to enemies.
Note: There is a 1-second cooldown between shots.

### Game Control

Pause the game at any time by pressing the Esc key.

### Objectives & Penalties

Your main goal is to destroy enemies before they pass you.

If an enemy gets past you, you lose 50 HP.

You can physically block an enemy to destroy it, but this will still cost you 30 HP in damage.

### Enemy Types

All enemies shoot projectiles that deal 10 HP damage. Their firing delay is random, between 2 to 3 seconds.

| Type  | Health | Speed    |
| ----- | ------ | -------- |
| Basic | 50 HP  | Balanced |
| Slim  | 30 HP  | Fast     |
| Bulky | 100 HP | Slow     |

## Documentation

Game was documented with doxygen. To generate it follow these steps:

1. Download and install [Doxygen](https://www.doxygen.nl/download.html).
2. Open terminal/cmd in CosmicInvaders folder.
3. Run `doxygen`
Documentation will be in `./docs` folder.

## Used libraries

- [assimp](https://assimp.org/)
- [entt](https://github.com/skypjack/entt)
- [glad](https://github.com/Dav1dde/glad)
- [glfw](https://www.glfw.org/)
- [glm](https://github.com/g-truc/glm)
- [imgui](https://www.dearimgui.com/)
- [miniaudio](https://miniaud.io/)
- [nlohmann/json](https://github.com/nlohmann/json)
- [stb](https://nothings.org/stb/)

### assets

During build they are copied to the folder with the executable file.

### core

All core classes, like AudioEngine and InputManager.

### ecs

Contains ECS implementation with EnTT library.

### gameplay

Contains class that updates whole game and namespace that contains informations about levels.

### renderer

All classes related to model processing and rendering.

### ui

Implemetation of games UI.

### demo.cpp

Runs demo that shows rendering capabilities.

### main.cpp

Main gameplay loop.
