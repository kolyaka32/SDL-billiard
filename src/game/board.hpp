/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <vector>
#include "ball.hpp"


//
class Board {
 private:
    Grid grid;
    const int count;
    std::vector<Ball> balls;
    Ball* selected = nullptr;
    SDL_FPoint lastPoint = {0, 0};
    int pressed = 0;
    SDL_FRect sides = {50, 50, 1000, 1000};

    Ball* getNear(SDL_FPoint pos);

 public:
    Board(int count);
    ~Board();
    void reset();

    // Interacting with scale and position
    bool clickBoard(const Mouse mouse);
    void unclickBoard(const Mouse mouse);
    bool scroll(const Mouse mouse, float wheelY);
    void updateBoard(const Mouse mouse);

    // Billiard-specified options
    bool clickBilliard(const Mouse mouse);
    void unclickBilliard(const Mouse mouse);
    void checkWallsCollisions();
    void checkCollisionBilliard();
    void blitBoard(const Window& window) const;

    // Gravity specified options
    void applyGravity(const Mouse _mouse);
    void checkCollisionGravity();

    // General options
    void updatePositions();
    void blitBalls(const Window& window) const;
};
