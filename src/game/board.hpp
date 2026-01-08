/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "ball.hpp"


//
class Board {
private:
    Grid grid;
    std::vector<Ball> balls;
    #if (BILLIARD)
    Ball* selected = nullptr;
    SDL_FPoint lastPoint = {0, 0};
    const int count = 200;
    #else
    int pressed = 0;
    const int count = 1000;
    #endif
    SDL_FRect sides = {50, 50, 1000, 1000};

public:
    Board();
    ~Board();
    void reset();
    void click(const Mouse _mouse);
    void unclick(const Mouse _mouse);
    void scroll(float wheelY);
    void applyInteraction();
    void checkCollision();
    void updatePositions();
    void update();
    void blit(const Window& window) const;
};
