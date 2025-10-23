/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../GUI/interface.hpp"
#include "../save.hpp"


// Option to start from new clear field with need size
class StartFields {
 private:
    // Start variants
    static Save startOptions[4];

    // Graphical interface for selecting
    static bool active;
    GUI::RoundedBackplate backplate;
    GUI::TextButton optionButton[4];
    GUI::TextButton closeButton;

 public:
    explicit StartFields(const Window& window);

    void activate();
    bool isActive();
    void reset();

    const Save* click(const Mouse mouse);

    void blit() const;
};
