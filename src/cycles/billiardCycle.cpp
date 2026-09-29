/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "billiardCycle.hpp"


BilliardCycle::BilliardCycle(Window& _window)
: BaseCycle(_window),
field(200) {
    if (!isRestarted()) {
        // Resetting field
        field.reset();
    }
}

bool BilliardCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    if (exitButton.in(mouse)) {
        stop();
        App::setNextCycle(Cycle::Select);
        return true;
    }
    if (field.clickBoard(mouse)) {
        return true;
    }
    if (field.clickBilliard(mouse)) {
        return true;
    }
    return false;
}

void BilliardCycle::inputMouseUp() {
    BaseCycle::inputMouseUp();
    field.unclickBoard(mouse);
    field.unclickBilliard(mouse);
}

bool BilliardCycle::inputMouseWheel(float _wheelY) {
    if (BaseCycle::inputMouseWheel(_wheelY)) {
        return true;
    }
    if (field.scroll(mouse, _wheelY)) {
        return true;
    }
    return false;
}

bool BilliardCycle::inputKeys(SDL_Keycode _key) {
    if (_key == SDLK_Q) {
        // Quiting to menu
        stop();
        return true;
    }
    if (BaseCycle::inputKeys(_key)) {
        return true;
    }
    return false;
}

void BilliardCycle::update() {
    BaseCycle::update();

    mouse.updatePos();
    field.updateBoard(mouse);
    field.checkCollisionBilliard();
    field.checkWallsCollisions();
    field.updatePositions();
}

void BilliardCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    field.blitBoard(window);
    field.blitBalls(window);

    // Drawing upper dashboard
    exitButton.blit();
    settings.blit();

    // Bliting all to screen
    window.render();
}
