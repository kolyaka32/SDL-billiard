/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "ball.hpp"


Ball::Ball()
: dest({0, 0, diameter, diameter}),
ux(0.0),
uy(0.0) {}

Ball::Normal Ball::getNormal(const Ball& _other) {
    Normal norm;
    norm.x = (dest.x-_other.dest.x);
    norm.y = (dest.y-_other.dest.y);
    norm.sqr = sqr(norm.x)+sqr(norm.y);
    norm.abs = SDL_sqrtf(norm.sqr);

    // Orthogonathing normal
    norm.x /= norm.abs;
    norm.y /= norm.abs;

    return norm;
}

void Ball::applyGravity(Ball& _other, const Normal _norm) {
    ux -= G*_norm.x/_norm.sqr;
    uy -= G*_norm.y/_norm.sqr;
    _other.ux += G*_norm.x/_norm.sqr;
    _other.uy += G*_norm.y/_norm.sqr;
}

void Ball::checkCollision(Ball& _other, const Normal _norm) {
    if (_norm.sqr < sqr(diameter)) {
        // Disconnecting objects for correct work
        dest.x += _norm.x*(diameter-_norm.abs);
        dest.y += _norm.y*(diameter-_norm.abs);
        _other.dest.x -= _norm.x*(diameter-_norm.abs);
        _other.dest.y -= _norm.y*(diameter-_norm.abs);

        // Current ball
        float scalar1 = _norm.x*ux + _norm.y*uy;
        float uxProj1 = scalar1*_norm.x;
        float uyProj1 = scalar1*_norm.y;
        // Second ball
        float scalar2 = _norm.x*_other.ux + _norm.y*_other.uy;
        float uxProj2 = scalar2*_norm.x;
        float uyProj2 = scalar2*_norm.y;

        float uxDelta = (uxProj1 + uxProj2)/2;
        float uyDelta = (uyProj1 + uyProj2)/2;

        ux -= uxProj1;
        uy -= uyProj1;
        _other.ux -= uxProj2;
        _other.uy -= uyProj2;

        ux += (1-friction) * uxDelta;
        uy += (1-friction) * uyDelta;
        _other.ux += (1-friction) * uxDelta;
        _other.uy += (1-friction) * uyDelta;

        audio.sounds.play(Sounds::Turn);
    }
}

void Ball::checkCollision2(Ball& _other, const Normal _norm) {
    ux += collison*_norm.x/_norm.sqr/_norm.sqr;
    uy += collison*_norm.y/_norm.sqr/_norm.sqr;
    _other.ux -= collison*_norm.x/_norm.sqr/_norm.sqr;
    _other.uy -= collison*_norm.y/_norm.sqr/_norm.sqr;
}

void Ball::checkCollisionBilliard(Ball& _other) {
    Normal norm = getNormal(_other);
    checkCollision(_other, norm);
}

void Ball::checkCollisionGravity(Ball& _other) {
    Normal norm = getNormal(_other);
    applyGravity(_other, norm);
    checkCollision(_other, norm);
}

void Ball::set(SDL_FPoint _point) {
    dest.x = _point.x;
    dest.y = _point.y;
    ux = 0;
    uy = 0;
}

void Ball::setSpeed(float _ux, float _uy) {
    ux = _ux / 10;
    uy = _uy / 10;
}

void Ball::pull(SDL_FPoint _point) {
    float norx = (dest.x-_point.x);
    float nory = (dest.y-_point.y);
    float norMod = sqr(norx)+sqr(nory);
    float norm = SDL_sqrtf(norMod);
    norx /= norm;
    nory /= norm;

    if (norm < 1) {
        return;
    }
    ux -= 10000*norx/norMod;
    uy -= 10000*nory/norMod;
}

void Ball::push(SDL_FPoint _point) {
    float norx = (dest.x-_point.x);
    float nory = (dest.y-_point.y);
    float norMod = sqr(norx) + sqr(nory);
    float norm = SDL_sqrtf(norMod);
    norx /= norm;
    nory /= norm;

    if (norm < 1) {
        return;
    }
    ux += 1000*norx/norMod;
    uy += 1000*nory/norMod;
}

bool Ball::isSelected(const SDL_FPoint _point) const {
    return (sqr(_point.x - dest.x - dest.w/2) + 
        sqr(_point.y - dest.y - dest.h/2) < diameter*diameter/4);
}

void Ball::checkWalls(const SDL_FRect _rect) {
    if (dest.x < _rect.x) {
        ux = ux*(friction-1);
        dest.x = _rect.x;
        audio.sounds.play(Sounds::Turn);
    } else if (dest.x+dest.w > _rect.x+_rect.w) {
        ux = ux*(friction-1);
        dest.x = _rect.x + _rect.w - dest.w;
        audio.sounds.play(Sounds::Turn);
    }
    if (dest.y < _rect.y) {
        uy = uy*(friction-1);
        dest.y = _rect.y;
        audio.sounds.play(Sounds::Turn);
    } else if (dest.y+dest.h > _rect.y+_rect.h) {
        uy = uy*(friction-1);
        dest.y = _rect.y + _rect.h - dest.h;
        audio.sounds.play(Sounds::Turn);
    }
}

void Ball::update() {
    //ux *= speed;
    //uy *= speed;

    dest.x += ux;
    dest.y += uy;
}

void Ball::blit(const Window& _window, const Grid _grid) const {
    _window.blit(_window.getTexture(Textures::Ball), _grid.absolute(dest));
}
