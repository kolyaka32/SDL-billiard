/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"


Board::Board(int _count)
: count(_count) {
    // Create first placement
    for (int i=0; i < count; ++i) {
        balls.push_back(Ball());
    }
    reset();
}

Board::~Board() {
    balls.clear();
}

void Board::reset() {
    SDL_srand(getTime());
    for (int i=0; i < count; ++i) {
        balls[i].set(grid.absolute(SDL_FPoint{SDL_randf()*sides.w + sides.x,
            SDL_randf()*sides.h + sides.y}));
    }
}

Ball* Board::getNear(SDL_FPoint _pos) {
    for (int i=0; i < count; ++i) {
        if (balls[i].isSelected(_pos)) {
            return &balls[i];
        }
    }
    return nullptr;
}

bool Board::clickBoard(const Mouse _mouse) {
    // Start camera movement
    if (_mouse.getState() & SDL_BUTTON_MMASK) {
        grid.click(_mouse);
        return true;
    }
    return false;
}

bool Board::scroll(const Mouse _mouse, float _wheelY) {
    grid.zoom(_mouse, _wheelY);
    return true;
}

void Board::updateBoard(const Mouse _mouse) {
    grid.update(_mouse);
}

void Board::unclickBoard(const Mouse _mouse) {
    grid.unClick(_mouse);
}

bool Board::clickBilliard(const Mouse _mouse) {
    if (_mouse.getState() & SDL_BUTTON_LMASK) {
        SDL_FPoint pos = grid.local(_mouse);
        if (selected = getNear(pos)) {
            lastPoint = pos;
        }
        return true;
    }
    return false;
}

void Board::unclickBilliard(const Mouse _mouse) {
    // Launching selected ball
    if (selected) {
        SDL_FPoint current = grid.local(_mouse);
        selected->setSpeed(current.x - lastPoint.x, current.y - lastPoint.y);
        selected = nullptr;
    }
}

void Board::checkWallsCollisions() {
    for (int i=0; i < count; ++i) {
        balls[i].checkWalls(sides);
    }
}

void Board::checkCollisionBilliard() {
    for (int i=0; i < count; ++i) {
        for (int j=1+i; j < count; ++j) {
            balls[i].checkCollisionBilliard(balls[j]);
        }
    }
}

void Board::blitBoard(const Window& _window) const {
    _window.blit(_window.getTexture(Textures::Board), grid.absolute(sides));
}

void Board::applyGravity(const Mouse _mouse) {
    if (_mouse.getState() & SDL_BUTTON_LMASK) {
        // Appling push to all
        for (int i=0; i < count; ++i) {
            balls[i].push(grid.local(_mouse));
        }
    }
    if (_mouse.getState() & SDL_BUTTON_RMASK) {
        // Appling pull to all
        for (int i=0; i < count; ++i) {
            balls[i].pull(grid.local(_mouse));
        }
    }
}

void Board::checkCollisionGravity() {
    for (int i=0; i < count; ++i) {
        for (int j=1+i; j < count; ++j) {
            balls[i].checkCollisionGravity(balls[j]);
        }
    }
}

void Board::updatePositions() {
    for (int i=0; i < count; ++i) {
        balls[i].update();
    }
}

void Board::blitBalls(const Window& _window) const {
    for (int i=0; i < count; ++i) {
        balls[i].blit(_window, grid);
    }
}
