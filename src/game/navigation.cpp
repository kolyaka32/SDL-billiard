/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "navigation.hpp"
#include "../define.hpp"
#include "../data/macroses.hpp"


Grid::Grid() {
    capture = false;
    centerX = 0;
    centerY = 0;
    scale = 1;
}

void Grid::update(float mouseX, float mouseY) {
    if (capture) {
        // Keeping captured point at it place
        centerX = (mouseX) - captureX*scale;
        centerY = (mouseY) - captureY*scale;
        logAdditional("Press at %f : %f, get at %f : %f", mouseX, mouseY, centerX, centerY);
    }
}

void Grid::click(float mouseX, float mouseY) {
    capture = true;
    captureX = (mouseX - centerX)/scale;
    captureY = (mouseY - centerY)/scale;
    logAdditional("Press at %f : %f, get at %f : %f", mouseX, mouseY, captureX, captureY);
}

void Grid::unClick(float mouseX, float mouseY) {
    capture = false;
}

void Grid::zoom(float mouseX, float mouseY, float wheelY) {
    centerX += mouseX*scale;
    centerY += mouseY*scale;

    scale *= SDL_powf(1.5, wheelY);

    setMin(scale, 0.1f);
    setMax(scale, 20.0f);

    centerX -= mouseX*scale;
    centerY -= mouseY*scale;
}

// float-float transformations
float Grid::absoluteX(float _x) const {
    return _x * scale + centerX;
}

float Grid::absoluteY(float _y) const {
    return _y * scale + centerY;
}

SDL_FPoint Grid::absolute(const SDL_FPoint _local) const {
    return SDL_FPoint{absoluteX(_local.x),
        absoluteY(_local.y)};
}

SDL_FRect Grid::absolute(SDL_FRect _local) const {
    return SDL_FRect{absoluteX(_local.x),
        absoluteY(_local.y),
        _local.w*scale,
        _local.h*scale};
}

float Grid::localX(float _x) const {
    return (_x - centerX) / scale;
}

float Grid::localY(float _y) const {
    return (_y - centerY) / scale;
}

SDL_FPoint Grid::local(SDL_FPoint _absolute) const {
    return SDL_FPoint{localX(_absolute.x),
        localX(_absolute.y)};
}

SDL_FPoint Grid::local(const Mouse _mouse) const {
    return SDL_FPoint{localX(_mouse.getX()),
        localY(_mouse.getY())};
}

SDL_FRect Grid::local(SDL_FRect _absolute) const {
    return SDL_FRect{localX(_absolute.x),
        localY(_absolute.y),
        _absolute.w/scale,
        _absolute.h/scale};
}
