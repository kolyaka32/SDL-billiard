/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"


Board::Board() {
    // Create first placement
    for (int i=0; i < 200; ++i) {
        balls.push_back(Ball());
    }
    reset();
}

Board::~Board() {
    balls.clear();
}

void Board::reset() {
    for (int i=0; i < balls.size(); ++i) {
        balls[i].set(SDL_randf()*400 + 50,
            SDL_randf()*400 + 50);
    }
}

void Board::click(const Mouse _mouse) {
    // Finding nearest ball
    /*selected = nullptr;
    for (int i=0; i < balls.size(); ++i) {
        if (balls[i].isSelected(_mouse)) {
            selected = &balls[i];
            lastPointX = _mouse.getX();
            lastPointY = _mouse.getY();
            return;
        }
    }*/
    if (_mouse.getState() & SDL_BUTTON_MMASK) {
        grid.click(_mouse.getX(), _mouse.getY());
    }
}

void Board::unclick(const Mouse _mouse) {
    // Launching selected ball
    /*if (selected) {
        selected->setSpeed(_mouse.getX() - lastPointX, _mouse.getY() - lastPointY);
    }*/
    grid.unClick(_mouse.getX(), _mouse.getY());
}

void Board::scroll(float _wheelY) {
    Mouse mouse{};
    mouse.updatePos();

    grid.zoom(mouse.getX(), mouse.getY(), _wheelY);
}

void Board::update() {
    Mouse mouse{};
    mouse.updatePos();
    if (mouse.getState() & SDL_BUTTON_LMASK) {
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
    }
    grid.update(mouse.getX(), mouse.getY());

    for (int i=0; i < balls.size(); ++i) {
        balls[i].update();
    }
    for (int i=0; i < balls.size(); ++i) {
        for (int j=1+i; j < balls.size(); ++j) {
            balls[i].checkCollision(balls[j]);
        }
    }
    /*for (int i=0; i < balls.size(); ++i) {
        balls[i].checkWalls(sides);
    }*/
}

void Board::blit(const Window& _window) const {
    //_window.blit(_window.getTexture(Textures::Board), sides);
    for (int i=0; i < balls.size(); ++i) {
        balls[i].blit(_window, grid);
    }
}
