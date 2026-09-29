/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "selectCycle.hpp"


SelectCycle::SelectCycle(Window& _window)
: BaseCycle(_window),
titleText(window, {"Billiard", "Бильярд", "Billardkugel", "Більярд"}, {0.5, 0.15, .frame=3, .height=GUI::Title}),
billiardButton(window, {"Billiard mode", "Режим бильярда", "Billard-Modus", "Рэжым більярда"}, {0.5, 0.4, .frame=1}),
gravityButton(window, {"Gravity mode", "Режим гравитации", "Schwerkraft-Modus", "Рэжым гравітацыі"}, {0.5, 0.6, .frame=1}) {
    // Starting menu song (if wasn't started)
    // music.start(Music::Menu);
    logger.additional("Start select cycle");
}

bool SelectCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        return true;
    }
    if (billiardButton.in(mouse)) {
        App::setNextCycle(Cycle::Billiard);
        return true;
    }
    if (gravityButton.in(mouse)) {
        App::setNextCycle(Cycle::Gravity);
        return true;
    }
    return false;
}

void SelectCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Bliting title
    titleText.blit();

    // Blitting start buttons
    billiardButton.blit();
    gravityButton.blit();

    // Settings menu
    settings.blit();

    // Bliting all to screen
    window.render();
}
