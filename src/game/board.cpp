/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"


Board::Board() {
    // Create first placement
    for (int i=0; i < 40; ++i) {
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
    if (_mouse.getState() & SDL_BUTTON_MMASK) {
        grid.click(_mouse.getX(), _mouse.getY());
    }
}

void Board::unclick(const Mouse _mouse) {
    // Launching selected ball
    if (selected) {
        SDL_FPoint current = grid.local(_mouse);
        selected->setSpeed(current.x - lastPoint.x, current.y - lastPoint.y);
    }
    grid.unClick(_mouse.getX(), _mouse.getY());
}

void Board::scroll(float _wheelY) {
    Mouse mouse{};
    mouse.updatePos();

    grid.zoom(_wheelY, mouse);
}

void Board::update() {
    Mouse mouse{};
    mouse.updatePos();
    /*if (mouse.getState() & SDL_BUTTON_LMASK) {
        // Appling push to all
        for (int i=0; i < balls.size(); ++i) {
            balls[i].push(grid.localX(mouse.getX()),
                grid.localY(mouse.getY()));
        }
    }
    if (mouse.getState() & SDL_BUTTON_RMASK) {
        // Appling pull to all
        for (int i=0; i < balls.size(); ++i) {
            balls[i].pull(grid.localX(mouse.getX()),
                grid.localY(mouse.getY()));
        }
    }*/
    grid.update(mouse.getX(), mouse.getY());

    for (int i=0; i < balls.size(); ++i) {
        balls[i].update();
    }
    for (int i=0; i < balls.size(); ++i) {
        for (int j=1+i; j < balls.size(); ++j) {
            balls[i].checkCollision(balls[j]);
        }
    }
    for (int i=0; i < balls.size(); ++i) {
        balls[i].checkWalls(sides);
    }
}

void Board::blit(const Window& _window) const {
    _window.blit(_window.getTexture(Textures::Board), grid.absolute(sides));
    for (int i=0; i < balls.size(); ++i) {
        balls[i].blit(_window, grid);
    }
}
