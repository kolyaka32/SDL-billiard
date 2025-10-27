/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameCycle.hpp"
#include "selectCycle.hpp"


GameCycle::GameCycle(Window& _window)
: BaseCycle(_window),
field(window) {
    if (!isRestarted()) {
        // Resetting field
        field.restart();
    }
    // Starting main song (if wasn't started)
    music.startFading(Music::MainCalm);
}

bool GameCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    // Normal turn
    field.clickCoop(mouse);
    return false;
}

void GameCycle::inputMouseUp() {
    mouse.updatePos();
    field.unclickCoop(mouse);
    settings.unClick();
}

void GameCycle::inputMouseWheel(float _wheelY) {
    BaseCycle::inputMouseWheel(_wheelY);
}

void GameCycle::inputKeys(SDL_Keycode _key) {
    // Quiting to menu
    if (_key == SDLK_Q) {
        stop();
    }
    if (_key == SDLK_ESCAPE) {
        // Closing top open object
        settings.activate();
        return;
    }
    GameCycle::inputKeys(_key);
}

void GameCycle::update() {
    BaseCycle::update();
    field.update();
}

void GameCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Blitting field
    field.blit();

    // Drawing upper dashboard
    exitButton.blit();
    settings.blit();

    // Bliting all to screen
    window.render();
}
