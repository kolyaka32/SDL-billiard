/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"


Board::Board() {
    // Create first placement
    balls.reserve(4);

    balls.push_back(Ball());
    balls.push_back(Ball());
    balls.push_back(Ball());
    balls.push_back(Ball());

    reset();
}

Board::~Board() {
    balls.clear();
}

void Board::reset() {
    balls[0].set(100, 150);
    balls[1].set(150, 100);
    balls[2].set(200, 150);
    balls[3].set(150, 200);
}

void Board::update() {
    for (int i=0; i < balls.size(); ++i) {
        for (int j=0; j < i; ++j) {
            balls[i].checkCollision(balls[j]);
        }
    }
    for (int i=0; i < balls.size(); ++i) {
        balls[i].checkWalls(sides);
        balls[i].update();
    }
}

void Board::blit(const Window& _window) const {
    _window.blit(_window.getTexture(Textures::Board), sides);
    for (int i=0; i < balls.size(); ++i) {
        balls[i].blit(_window);
    }
}
