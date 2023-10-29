#include "GameState.h"

GameStateManager::GameStateManager() : currentState(GameState::TitleScreen) {}

void GameStateManager::changeState(GameState newState) {
    currentState = newState;
}

GameState GameStateManager::getState() const {
    return currentState;
}