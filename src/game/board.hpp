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
    Grid grid;
    std::vector<Ball> balls;
    int pressed = 0;
    float lastPointX = 0, lastPointY = 0;

public:
    Board();
    ~Board();
    void reset();
    void click(const Mouse _mouse);
    void unclick(const Mouse _mouse);
    void scroll(float wheelY);
    void update();
    void blit(const Window& window) const;
};
