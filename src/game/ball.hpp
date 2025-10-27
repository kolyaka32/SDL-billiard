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
    const float friction = 0;
    const float speed = 1;
    const float G = 1;
    SDL_FRect dest;
    float ux = 0.0, uy = 0.0;

 public:
    Ball();
    void set(float X, float Y);
    void setSpeed(float ux, float uy);
    void pull(float x, float y);
    void push(float x, float y);
    bool isSelected(const Mouse mouse);
    void update();
    void checkWalls(const SDL_FRect rect);
    void checkCollision(Ball& ball);
    void blit(const Window& window) const;
};
