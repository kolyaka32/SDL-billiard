/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/window.hpp"

// Datatypes for better work with coordinats
typedef float local;
typedef float absolute;


//
class Grid {
private:
    // Parameters of grid system
    absolute centerX, centerY;
    float scale;

    // Parameters of movement
    bool capture;
    absolute captureX, captureY;

public:
    Grid();

    void click(float mouseX, float mouseY);
    void unClick(float mouseX, float mouseY);
    void zoom(float mouseX, float mouseY, float wheelY);
    void update(float mouseX, float mouseY);

    // Work with local and absolute coordinats
    absolute absoluteX(local localeX) const;
    absolute absoluteY(local localeY) const;
    SDL_FRect absoluteRect(SDL_FRect locale) const;
    local localX(absolute X) const;
    local localY(absolute Y) const;
};
