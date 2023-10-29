#pragma once

enum class GameState {
    TitleScreen,
    Countdown,
    Playing,
    GameOver,
    Leaderboard
};

class GameStateManager {
public:
    GameStateManager();
    void changeState(GameState newState);
    GameState getState() const;

private:
    GameState currentState;
};