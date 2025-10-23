/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../save.hpp"
#include "../../GUI/interface.hpp"


// Information of one concrete save (date and picture for load)
class SaveInfo : public GUI::Template {
 private:
    // Backplate
    GUI::RoundedBackplate backplate;
    // Picture of game field
    SDL_Texture* texture;
    SDL_FRect dest;
    // Save parameters
    //GUI::StaticText saveNameText;
    GUI::HighlightedStaticText lastModifiedText;

 public:
    explicit SaveInfo(const Window& window, const Save& field, int position);
    ~SaveInfo();
    void moveUp();
    void moveDown();
    void blit() const override;
    bool in(Mouse mouse) const;
};
