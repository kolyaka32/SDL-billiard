/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "gameField.hpp"
#include "../data/cycleTemplate.hpp"
#include "menu/selectingMenu.hpp"


// Creating start game field 3 by 3
Board GameField::currentField{};


GameField::GameField(const Window& _window)
: Template(_window) {}

void GameField::restart() {
    currentField.reset();
    //currentField.setState(GameState::CurrentPlay);
}

bool GameField::isGameEnd() const {
    return false; // currentField.getState() >= GameState::CurrentWin;
}

void GameField::setNewField(const Board& field) {
    // Check, if need restart window
    /*if (currentField.width != field->width) {
        currentField = field;
        // Setting new window width, height
        currentField.updateWindow(_window);
        CycleTemplate::restart();
        CycleTemplate::stop();
    }
    currentField = field;
    // Check, if game already started
    if (currentField.isStarted()) {
        music.startFromCurrent(Music::MainCombat);
    }*/
}

const Save GameField::saveField() const {
    // Update save timer
    //currentField.updateSaveInfo();
    return Save{};
}

void GameField::tryClickSingle(const Mouse _mouse) {
    /*if (currentField.isValid(_mouse) && currentField.getState() <= GameState::OpponentPlay) {
        currentField.clickSingle(currentField.getPosition(_mouse));
        checkEnd();
    }*/
}

void GameField::clickCoop(const Mouse _mouse) {
    /*if (currentField.isValid(_mouse) && currentField.getState() <= GameState::OpponentPlay) {
        currentField.clickTwo(currentField.getPosition(_mouse));
        checkEnd();
    }*/
   currentField.click(_mouse);
}

void GameField::unclickCoop(const Mouse _mouse) {
    currentField.unclick(_mouse);
}

bool GameField::tryClickServerCurrent(const Mouse _mouse) {
    /*if (currentField.isValid(_mouse) && currentField.getState() == GameState::CurrentPlay) {
        return currentField.clickMultiplayerCurrent(currentField.getPosition(_mouse));
        checkEnd();
    }*/
    return false;
}

bool GameField::tryClickClientCurrent(const Mouse _mouse) {
    /*if (currentField.isValid(_mouse) && currentField.getState() == GameState::OpponentPlay) {
        return currentField.clickMultiplayerCurrent(currentField.getPosition(_mouse));
        checkEndInverted();
    }*/
    return false;
}

void GameField::clickServerOpponent(Uint8 _p) {
    // No additional checks for correct internet connection
    //currentField.clickMultiplayerOpponent({_p%currentField.width, _p/currentField.width});
    //checkEnd();
}

void GameField::clickClientOpponent(Uint8 _p) {
    // No additional checks for correct internet connection
    //currentField.clickMultiplayerOpponent({_p%currentField.width, _p/currentField.width});
    //checkEndInverted();
}

void GameField::update() {
    currentField.update();
}

void GameField::blit() const {
    currentField.blit(window);
}

void GameField::checkEnd() {
    // Starting main combat music
    //music.startFromCurrent(Music::MainCombat);
    // Making sound depend on state
    /*switch (currentField.getState()) {
    case GameState::CurrentWin:
        sounds.play(Sounds::Win);
        logAdditional("Opponent win");
        break;

    case GameState::OpponentWin:
        sounds.play(Sounds::Loose);
        logAdditional("Current win");
        break;

    case GameState::NobodyWin:
        sounds.play(Sounds::Loose);
        logAdditional("Nobody win");
        break;

    default:
        sounds.play(Sounds::Turn);
        return;
    }*/
    // Setting start menu for next game
    SelectingMenu::open();
}
