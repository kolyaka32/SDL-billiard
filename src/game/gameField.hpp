/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "board.hpp"


// Cycle with field with game objects on it
class GameField : public GUI::Template {
 private:
    // Game field
    static Board currentField;

 public:
    explicit GameField(const Window& window);

    void restart();

    void update();

    void blit() const override;

    // Game turns
    void click(const Mouse mouse);
    void unclick(const Mouse mouse);
    void scroll(float wheel);
};
