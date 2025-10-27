/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../game/gameField.hpp"


// Cycle with game template
class GameCycle : public BaseCycle {
 protected:
    // Active game part
    GameField field;

    // New overrided cycle functions
    bool inputMouseDown() override;
    void inputMouseUp() override;
    void inputMouseWheel(float _wheelY) override;
    void inputKeys(SDL_Keycode _key) override;
    void update() override;
    void draw() const override;

 public:
    GameCycle(Window& _window);
};
