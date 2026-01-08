/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"


Board::Board() {
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
    for (int i=0; i < balls.size(); ++i) {
        balls[i].set(grid.absolute(SDL_FPoint{SDL_randf()*sides.w + sides.x,
            SDL_randf()*sides.h + sides.y}));
    }
}

void Board::click(const Mouse _mouse) {
    // Finding nearest ball
    #if (BILLIARD)
    selected = nullptr;
    SDL_FPoint current = grid.local(_mouse);
    if (_mouse.getState() & SDL_BUTTON_LMASK) {
        for (int i=0; i < balls.size(); ++i) {
            if (balls[i].isSelected(current)) {
                selected = &balls[i];
                lastPoint = current;
                logAdditional("Selected %d", i);
                return;
            }
        }
    }
    #endif
    if (_mouse.getState() & SDL_BUTTON_MMASK) {
        grid.click(_mouse.getX(), _mouse.getY());
    }
}

void Board::unclick(const Mouse _mouse) {
    // Launching selected ball
    #if (BILLIARD)
    if (selected) {
        SDL_FPoint current = grid.local(_mouse);
        selected->setSpeed(current.x - lastPoint.x, current.y - lastPoint.y);
    }
    #endif
    grid.unClick(_mouse.getX(), _mouse.getY());
}

void Board::scroll(float _wheelY) {
    Mouse mouse{};
    mouse.updatePos();

    grid.zoom(_wheelY, mouse);
}

void Board::applyInteraction() {
    Mouse mouse{};
    mouse.updatePos();
    #if (BILLIARD)
    for (int i=0; i < balls.size(); ++i) {
        balls[i].checkWalls(sides);
    }
    #else
    if (mouse.getState() & SDL_BUTTON_LMASK) {
        // Appling push to all
        for (int i=0; i < balls.size(); ++i) {
            balls[i].push(grid.local(mouse));
        }
    }
    if (mouse.getState() & SDL_BUTTON_RMASK) {
        // Appling pull to all
        for (int i=0; i < balls.size(); ++i) {
            balls[i].pull(grid.local(mouse));
        }
    }
    #endif
    grid.update(mouse.getX(), mouse.getY());
}

void Board::checkCollision() {
    for (int i=0; i < balls.size(); ++i) {
        for (int j=1+i; j < balls.size(); ++j) {
            balls[i].checkCollision(balls[j]);
        }
    }
}

void Board::updatePositions() {
    for (int i=0; i < balls.size(); ++i) {
        balls[i].update();
    }
}

void Board::update() {
    applyInteraction();

    for (int i=0; i < 5; ++i) {
        checkCollision();
    }
    updatePositions();
}

void Board::blit(const Window& _window) const {
    #if (BILLIARD)
    _window.blit(_window.getTexture(Textures::Board), grid.absolute(sides));
    #endif
    for (int i=0; i < balls.size(); ++i) {
        balls[i].blit(_window, grid);
    }
}
