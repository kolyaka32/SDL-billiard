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
        SDL_Log("Press at %f : %f, get at %f : %f", mouseX, mouseY, centerX, centerY);
    }
}

void Grid::click(float mouseX, float mouseY) {
    capture = true;
    captureX = (mouseX - centerX)/scale;
    captureY = (mouseY - centerY)/scale;
    //SDL_Log("Press at %f : %f, get at %f : %f", mouseX, mouseY, captureX, captureY);
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

// Local-absolute transformations
absolute Grid::absoluteX(local _x) const {
    return _x * scale + centerX;
}

absolute Grid::absoluteY(local _y) const {
    return _y * scale + centerY;
}

SDL_FRect Grid::absoluteRect(SDL_FRect _local) const {
    return SDL_FRect{absoluteX(_local.x), absoluteY(_local.y),
        _local.w*scale, _local.h*scale};
}

local Grid::localX(absolute _x) const {
    return (_x - centerX) / scale;
}

local Grid::localY(absolute _y) const {
    return (_y - centerY) / scale;
}
