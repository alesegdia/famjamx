#pragma once

#include <aether/aether.h>
#include <queue>
#include <algorithm>

#include "constants.h"
#include "levels.h"
#include "../assets.h"

enum class TileType
{
    Walkable,
    Solid,
    Hazard /* magma or ice */
};

enum class TileContents
{
    None,
    DimensionShifter,
    GoalItem
};

struct Tile
{
    TileType tileType;
    TileContents tileContents;
};

typedef aether::math::Matrix2D<Tile> TileMap;


class Scene
{
public:

    static constexpr size_t Width = 16;
    static constexpr size_t Height = 15;
    static constexpr size_t TileSize = 8;

    enum Status
    {
        Running,
        Lost,
        Won
    };

    Scene(aether::graphics::Spritesheet* sheet, const LevelConstructionData& lcd, Assets& assets);
    ~Scene();

    void render();
    void update(uint64_t delta);
    Status status();

private:

    aether::graphics::Texture getTileTexture(const Tile& tile)
    {
        auto base = 0u;
        auto offset = (m_isHalloween ? 8u : 0u);
        switch( tile.tileType )
        {
        case TileType::Walkable: base = 0; break;
        case TileType::Solid: base = 2; break;
        case TileType::Hazard: base = 1; break;
        }
        return m_sheet->getFrame(base + offset);
    }

    Tile& getPlayerTile()
    {
        return m_tileMap.get(m_playerPos.x(), m_playerPos.y());
    }

    bool canWalkTo( int x, int y )
    {
        return x >= 0 && x < Constants::LevelsWidth &&
               y >= 0 && y < Constants::LevelsHeight &&
               m_tileMap.get(x, y).tileType != TileType::Solid;
    }

    bool canWalkTo( const aether::math::Vec2i& v )
    {
        return canWalkTo(v.x(), v.y());
    }

    Status m_sceneStatus = Status::Running;
    TileMap m_tileMap;
    aether::graphics::Spritesheet* m_sheet;
    bool m_isHalloween = false;
    aether::math::Vec2i m_playerPos;
    int m_numGoalItems = 0;
    int m_totalGoalItems = 0;
    bool m_playerLockedInIce = false;
    aether::math::Vec2i m_playerMovementDirection;
    aether::math::Vec2i m_lastPlayerMovementDirection;
    Assets& m_assets;

};
