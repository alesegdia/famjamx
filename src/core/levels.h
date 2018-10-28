#pragma once

#include <aether/aether.h>
#include "constants.h"

class LevelConstructionData : public aether::math::Matrix2D<uint8_t>
{
public:
    LevelConstructionData(size_t playerSpawnX, size_t playerSpawnY)
        : aether::math::Matrix2D<uint8_t>(
              Constants::LevelsWidth,
              Constants::LevelsHeight)
        , m_playerSpawn(playerSpawnX, playerSpawnY)
    {

    }

    const aether::math::Vec2<size_t>& playerSpawn() const
    {
        return m_playerSpawn;
    }

private:
    aether::math::Vec2<size_t> m_playerSpawn;
};

class Levels
{
public:
    Levels();

    /*

    {




        // LEVEL 2
        addLevel(10, 1).data({
            1,1,1,1,1,1,0,0,0,0,0,0,
            1,1,1,1,1,1,0,0,0,0,0,0,
            1,1,0,1,1,1,0,0,0,0,0,0,
            1,0,0,0,0,3,0,0,0,0,0,0,
            0,0,0,0,1,1,1,1,0,0,0,0,
            0,0,0,0,0,1,1,1,1,0,0,1,
            0,0,0,0,0,0,0,0,1,1,1,1,
            0,0,0,0,0,0,0,0,1,1,1,1,
            0,0,0,0,0,0,0,0,0,1,1,1,
            0,0,5,0,0,0,0,0,0,0,1,1,
            0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0
        });

        /*
        // LEVEL 3
        addLevel(4, 1).data({
            0,1,1,0,0,0,1,1,0,
            0,0,1,0,0,1,1,0,0,
            0,0,1,1,0,1,1,0,0,
            0,0,0,1,2,1,0,0,0,
            0,0,0,1,2,1,0,0,0,
            0,0,2,2,2,2,2,0,0,
            0,0,0,2,2,2,0,0,0,
            0,0,0,0,5,0,0,0,0,
            0,0,0,0,0,0,0,0,0
        });

    }
        */

    const LevelConstructionData& getLevel( size_t level_index )
    {
        assert(level_index < m_levels.size());
        return m_levels[level_index];
    }

    size_t numLevels()
    {
        return m_levels.size();
    }

private:

    LevelConstructionData& addLevel(size_t psx, size_t psy)
    {
        m_levels.push_back(LevelConstructionData(psx, psy));
        return m_levels.back();
    }

    std::vector<LevelConstructionData> m_levels;

};
