/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "../data/array.hpp"
#include "ball.hpp"


//
class Board {
private:
    Ball balls[4];
    const SDL_FRect sides = {50, 50, 400, 400};

public:
    Board();
    ~Board();
    void reset();
    void update();
    void blit(const Window& window) const;
};
