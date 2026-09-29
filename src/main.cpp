/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"


// Main function
int main(int argv, char **args) {
    // Creating main window
    Window window{600, 600, {"Billiard", "Бильярд", "Billardkugel", "Більярд"}};

    // Running menu
    App::run(window);

    // Successful end of program
    return 0;
}
