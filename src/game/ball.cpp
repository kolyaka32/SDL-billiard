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

        // Disconnecting objects for correct work
        dest.x += norx*(diameter-norm);
        dest.y += nory*(diameter-norm);
        ball.dest.x -= norx*(diameter-norm);
        ball.dest.y -= nory*(diameter-norm);

        // Current ball
        float scalar1 = norx*ux + nory*uy;
        float uxProj1 = scalar1*norx;
        float uyProj1 = scalar1*nory;
        // Second ball
        float scalar2 = norx*ball.ux + nory*ball.uy;
        float uxProj2 = scalar2*norx;
        float uyProj2 = scalar2*nory;

        float uxDelta = (uxProj1 + uxProj2)/2;
        float uyDelta = (uyProj1 + uyProj2)/2;

        ux -= uxProj1;
        uy -= uyProj1;
        ball.ux -= uxProj2;
        ball.uy -= uyProj2;

        ux += (1-friction) * uxDelta;
        uy += (1-friction) * uyDelta;
        ball.ux += (1-friction) * uxDelta;
        ball.uy += (1-friction) * uyDelta;

        sounds.play(Sounds::Turn);
    }
}

void Ball::set(float X, float Y) {
    dest.x = X;
    dest.y = Y;
    ux = SDL_randf()*10;
    uy = SDL_randf()*10;
}

void Ball::setSpeed(float _ux, float _uy) {
    ux = _ux / 10;
    uy = _uy / 10;
}

bool Ball::isSelected(const Mouse _mouse) {
    return (sqr(_mouse.getX() - dest.x - dest.w/2) + 
        sqr(_mouse.getY() - dest.y - dest.h/2) < diameter*diameter/4);
}

void Ball::checkWalls(const SDL_FRect _rect) {
    if (dest.x < _rect.x) {
        ux = ux*(friction-1);
        dest.x = _rect.x;
        sounds.play(Sounds::Turn);
    } else if (dest.x+dest.w > _rect.x+_rect.w) {
        ux = ux*(friction-1);
        dest.x = _rect.x + _rect.w - dest.w;
        sounds.play(Sounds::Turn);
    }
    if (dest.y < _rect.y) {
        uy = uy*(friction-1);
        dest.y = _rect.y;
        sounds.play(Sounds::Turn);
    } else if (dest.y+dest.h > _rect.y+_rect.h) {
        uy = uy*(friction-1);
        dest.y = _rect.y + _rect.h - dest.h;
        sounds.play(Sounds::Turn);
    }
}

void Ball::update() {
    ux *= speed;
    uy *= speed;

    dest.x += ux;
    dest.y += uy;
}


void Ball::blit(const Window& _window) const {
    _window.blit(_window.getTexture(Textures::Ball), dest);
}
