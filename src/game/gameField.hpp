/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "save.hpp"


// Cycle with field with game objects on it
class GameField : public GUI::Template {
 private:
    // Game field
    static Board currentField;
    // Function for do after game end
    void checkEnd();
    // Similar to checkEnd(), but for client side
    void checkEndInverted();

 public:
    explicit GameField(const Window& window);
    // GameState getState() const;
    // void setState(GameState state);
    // static int getWidth();

    bool isGameEnd() const;
    void restart();
    void setNewField(const Board& field);
    const Save saveField() const;
    // const Array<char> getSave() const;

    void update();

    void blit() const override;

    // Game turns
    void clickCoop(const Mouse mouse);              // Clicking in coop mode, return if have turn
    void unclickCoop(const Mouse mouse);            // Clicking in coop mode, return if have turn
    void scroll(float wheel);
};
