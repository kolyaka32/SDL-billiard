/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gravityCycle.hpp"


GravityCycle::GravityCycle(Window& _window)
: BaseCycle(_window),
field(1000) {
    if (!isRestarted()) {
        field.reset();
    }
}

bool GravityCycle::inputMouseDown() {
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
    return false;
}

void GravityCycle::inputMouseUp() {
    BaseCycle::inputMouseUp();
    field.unclickBoard(mouse);
}

bool GravityCycle::inputMouseWheel(float _wheelY) {
    if (BaseCycle::inputMouseWheel(_wheelY)) {
        return true;
    }
    if (field.scroll(mouse, _wheelY)) {
        return true;
    }
    return false;
}

bool GravityCycle::inputKeys(SDL_Keycode _key) {
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

void GravityCycle::update() {
    BaseCycle::update();

    mouse.updatePos();
    field.updateBoard(mouse);
    field.applyGravity(mouse);
    field.checkCollisionGravity();
    field.updatePositions();
}

void GravityCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    field.blitBalls(window);

    // Drawing upper dashboard
    exitButton.blit();
    settings.blit();

    // Bliting all to screen
    window.render();
}
