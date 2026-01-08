/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameField.hpp"
#include "../data/cycleTemplate.hpp"


// Creating start game field 3 by 3
Board GameField::currentField{};


GameField::GameField(const Window& _window)
: Template(_window) {}

void GameField::restart() {
    currentField.reset();
}

void GameField::click(const Mouse _mouse) {
   currentField.click(_mouse);
}

void GameField::unclick(const Mouse _mouse) {
    currentField.unclick(_mouse);
}

void GameField::scroll(float wheel) {
    currentField.scroll(wheel);
}

void GameField::update() {
    currentField.update();
}

void GameField::blit() const {
    currentField.blit(window);
}
