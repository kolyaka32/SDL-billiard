/*
 * Copyright (C) 2025-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "musicNames.hpp"

// Check, if use mixer and preload music
#if (USE_SDL_MIXER) && (PRELOAD_MUSIC)

// File names of the corresponding music
const char* musicFilesNames[unsigned(Music::Count)] = {
    // Menu part
    "mus/menu.mp3",

    // Game part
    "mus/main-calm.mp3",
    "mus/main-combat.mp3",
};

#endif  // (USE_SDL_MIXER) && (PRELOAD_MUSIC)
