#include <iostream>
#include <unordered_map>
#include <vector>

#include "bitmap_image.hpp"

static bool pixel_is_color(rgb_t pixel, uint32_t color)
{
    return pixel.red    == (color & 0xFF0000) >> 16 &&
           pixel.green  == (color & 0x00FF00) >> 8  &&
           pixel.blue   == (color & 0x0000FF);
}

static std::unordered_map<std::string, uint32_t> colors
({
     {"DarkGray",   0x7d7d7d},
     {"LightGray",  0xd4d4d4},
     {"Red",        0xff0000},
     {"Green",      0x00ff00},
     {"Blue",       0x0000ff},
     {"Cyan",       0x00ffff},
     {"Fucsia",     0xff00ff},
     {"Yellow",     0xffff00},
     {"White",      0xffffff},
     {"Black",      0x000000},
     {"Marine",     0x6294ff},
});

struct Item
{
    std::string color;
    int num;
    bool spawn;
    std::string desc;
};

static std::vector<Item> items
{
    {"White",       0, false, "Walkable"},
    {"LightGray",   5, false, "Walkable with goal"},
    {"Cyan",        3, false, "Walkable with shifter"},
    {"Yellow",      0, true,  "Walkable with SPAWN"},

    {"Blue",        2, false, "Hazard"},
    {"DarkGray",    6, false, "Hazard with goal"},
    {"Black",       4, false, "Hazard with shifter"},
    {"Marine",      2, true,  "Hazard with SPAWN"},

    {"Green",       1, false, "Solid"},
};

int main(int argc, char** argv)
{
    if( argc != 2 )
    {
        std::cerr << "Wrong args num\n";
        exit(1);
    }

    bitmap_image bitmap(argv[1]);

    if( !bitmap )
    {
        std::cerr << "Couldn't load bitmap\n";
        exit(1);
    }

    int spawnx, spawny;
    spawnx = spawny = -1;
    std::string outstr = "        ";
    for( int i = 0; i < bitmap.height(); i++ )
    {
        for( int j = 0; j < bitmap.width(); j++ )
        {
            rgb_t pixel;
            bitmap.get_pixel(j, i, pixel);
            for( auto item : items )
            {
                if( pixel_is_color(pixel, colors[item.color]) )
                {
                    if( item.spawn )
                    {
                        spawnx = j; spawny = i;
                    }
                    outstr += std::to_string(item.num) + ",";
                    break;
                }
            }
        }

        if( i + 1 != bitmap.height() )
        {
            outstr += "\n        ";
        }
        else
        {
            outstr.pop_back();
        }
    }

    if( spawnx == -1 )
    {
        std::cerr << "No SPAWN point!\n";
    }

    std::cout << "    addLevel("
              << spawnx
              << ", "
              << spawny
              << ").data({\n"
              << outstr
              << "});"
              << std::endl << std::endl;


    return 0;
}
