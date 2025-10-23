/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


//
class Ball {
 private:
    const float diameter = 10.0;
    const float G = 0.1;
    SDL_FRect dest;
    float ux = 0.0, uy = 0.0;

 public:
    Ball();
    void set(float X, float Y);
    void update();
    void checkWalls(const SDL_FRect rect);
    void checkCollision(Ball& ball);
    void blit(const Window& window) const;
};
