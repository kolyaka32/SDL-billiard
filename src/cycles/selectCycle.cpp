/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "selectCycle.hpp"
#include "gameCycle.hpp"


// Starting basic template with main theme
SelectCycle::SelectCycle(Window& _window)
: BaseCycle(_window),
titleText(window, 0.5, 0.15, {"Billiard", "Бильярд", "Tic-tac-toe", "Крыжыкі нулікі"}, 3, Height::Title),
twoPlayerButton(window, 0.5, 0.5, {"Two players", "Два игрока", "Zwei Spieler", "Два гульца"}) {
    // Starting menu song (if wasn't started)
    // music.start(Music::Menu);
    logAdditional("Start select cycle");
}

// Getting selected button
bool SelectCycle::inputMouseDown() {
    if (settings.click(mouse)) {
        return true;
    }
    if (twoPlayerButton.in(mouse)) {
        runCycle<GameCycle>(window);
        return true;
    }
    return false;
}

void SelectCycle::inputKeys(SDL_Keycode _key) {
    switch (_key) {
    case SDLK_ESCAPE:
        settings.activate();
        return;
    }
}

void SelectCycle::update() {
    BaseCycle::update();
}

void SelectCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Bliting title
    titleText.blit();

    // Blitting start buttons
    //singleplayerButton.blit();
    twoPlayerButton.blit();
    //serverButton.blit();
    //connectButton.blit();

    // Settings menu
    settings.blit();

    // Bliting all to screen
    window.render();
}
