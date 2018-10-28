#pragma once

class Constants
{
public:

    static constexpr int LevelsWidth = 13;
    static constexpr int LevelsHeight = 13;
    static constexpr int TileSize = 8;
    static constexpr int ScreenScale = 4;
    static constexpr int TopInfoLines = 2;
    static constexpr int MapYOffset = TopInfoLines * TileSize * ScreenScale;
    static constexpr int ScreenWidth = LevelsWidth * TileSize * ScreenScale;
    static constexpr int ScreenHeight = (LevelsHeight) * TileSize * ScreenScale;

};
