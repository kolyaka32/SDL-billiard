/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "ball.hpp"


Ball::Ball()
: dest({0, 0, diameter, diameter}),
ux(0.0),
uy(0.0) {}

void Ball::checkCollision(Ball& ball) {
    float norx = dest.x-ball.dest.x;
    float nory = dest.y-ball.dest.y;
    float norMod = sqr(norx)+sqr(nory);
    if (norMod < sqr(diameter)) {
        // Orthogonathing normal
        norx /= norMod;
        nory /= norMod;

        // Current ball
        float scalar1 = norx*ux + nory*uy;
        float uxProj1 = scalar1*norx;
        float uyProj1 = scalar1*nory;
        ux -= 2*uxProj1;
        uy -= 2*uyProj1;

        // Second ball
        float scalar2 = norx*ball.ux + nory*ball.uy;
        float uxProj2 = scalar2*norx;
        float uyProj2 = scalar2*nory;
        ball.ux -= 2*uxProj2;
        ball.uy -= 2*uyProj2;

        sounds.play(Sounds::Turn);
    }
}

void Ball::set(float X, float Y) {
    dest.x = X;
    dest.y = Y;
    ux = SDL_randf();
    uy = SDL_randf();
}

void Ball::checkWalls(const SDL_FRect _rect) {
    if (dest.x < _rect.x || dest.x+dest.w > _rect.x+_rect.w) {
        ux = -ux;
        sounds.play(Sounds::Turn);
    }
    if (dest.y < _rect.y || dest.y+dest.h > _rect.y+_rect.h) {
        uy = -uy;
        sounds.play(Sounds::Turn);
    }
}

void Ball::update() {
    dest.x += ux;
    dest.y += uy;
}


void Ball::blit(const Window& _window) const {
    _window.blit(_window.getTexture(Textures::Ball), dest);
}
