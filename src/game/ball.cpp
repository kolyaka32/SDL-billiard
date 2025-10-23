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
    float norx = (dest.x-ball.dest.x);
    float nory = (dest.y-ball.dest.y);
    float norMod = sqr(norx)+sqr(nory);
    float norm = SDL_sqrtf(norMod);

    // Collisions
    if (norMod < sqr(diameter)) {
        // Orthogonathing normal
        norx /= norm;
        nory /= norm;

        // Current ball
        float scalar1 = norx*ux + nory*uy;
        float uxProj1 = scalar1*norx;
        float uyProj1 = scalar1*nory;
        // Second ball
        float scalar2 = norx*ball.ux + nory*ball.uy;
        float uxProj2 = scalar2*norx;
        float uyProj2 = scalar2*nory;

        ux -= (2-friction)*uxProj1;
        uy -= (2-friction)*uyProj1;
        ball.ux -= (2-friction)*uxProj2;
        ball.uy -= (2-friction)*uyProj2;

        dest.x += norx;
        dest.y += nory;
        ball.dest.x -= norx;
        ball.dest.y -= nory;

        sounds.play(Sounds::Turn);
    }
}

void Ball::set(float X, float Y) {
    dest.x = X;
    dest.y = Y;
    ux = SDL_randf()*10;
    uy = SDL_randf()*10;
}

void Ball::checkWalls(const SDL_FRect _rect) {
    if (dest.x < _rect.x) {
        ux = ux*(friction-1);
        dest.x += 1;
        sounds.play(Sounds::Turn);
    } else if (dest.x+dest.w > _rect.x+_rect.w) {
        ux = ux*(friction-1);
        dest.x -= 1;
        sounds.play(Sounds::Turn);
    }
    if (dest.y < _rect.y) {
        uy = uy*(friction-1);
        dest.y += 1;
        sounds.play(Sounds::Turn);
    } else if (dest.y+dest.h > _rect.y+_rect.h) {
        uy = uy*(friction-1);
        dest.y -= 1;
        sounds.play(Sounds::Turn);
    }
}

void Ball::update() {
    ux *= 0.99;
    uy *= 0.99;

    dest.x += ux;
    dest.y += uy;
}


void Ball::blit(const Window& _window) const {
    _window.blit(_window.getTexture(Textures::Ball), dest);
}
