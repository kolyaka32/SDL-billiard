/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"
#include "cycles/selectCycle.hpp"
#include "cycles/billiardCycle.hpp"
#include "cycles/gravityCycle.hpp"


Cycle App::nextCycle = Cycle::Select;

void App::run(Window& _window) {
    logger.additional("\nStart app");

    // Starting loop of selecting cycles
    while (running) {
        switch (nextCycle) {
        case Cycle::Select:
            runCycle<SelectCycle>(_window);
            break;

        case Cycle::Billiard:
            runCycle<BilliardCycle>(_window);
            break;

        case Cycle::Gravity:
            runCycle<GravityCycle>(_window);
            break;

        default:
            running = false;
            break;
        }
    }
}
