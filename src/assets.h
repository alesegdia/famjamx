#pragma once

#include <aether/aether.h>

class Assets
{
public:
    void load()
    {
        fluxus.load("assets/fluxus.png");

        alltiles_texture.load("assets/tiles.png");
        alltiles_sheet.load(4, 4, alltiles_texture);

        font.load("assets/04B_03__.TTF", 8);
        bigFont.load("assets/04B_03__.TTF", 16);

        theme.load("assets/waves.ogg");

        select.load("assets/move.wav");
        died.load("assets/died.wav");
        pickup.load("assets/pickup.wav");
        shift.load("assets/shift.wav");
    }

    void cleanup()
    {
        alltiles_texture.destroy();
        font.destroy();
        bigFont.destroy();
        theme.destroy();

        select.destroy();
        pickup.destroy();
        died.destroy();
        shift.destroy();
    }



    aether::graphics::Texture fluxus;

    aether::graphics::Texture alltiles_texture;
    aether::graphics::Spritesheet alltiles_sheet;

    aether::graphics::Font font;
    aether::graphics::Font bigFont;

    aether::audio::Stream theme;

    aether::audio::Sample select;
    aether::audio::Sample died;
    aether::audio::Sample pickup;
    aether::audio::Sample shift;

};
