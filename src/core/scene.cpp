#include "scene.h"


Scene::Scene(aether::graphics::Spritesheet *sheet, const LevelConstructionData &level)
    : m_tileMap(Constants::LevelsWidth, Constants::LevelsHeight),
      m_sheet(sheet)
{
    m_playerPos.set(
                level.playerSpawn().x(),
                level.playerSpawn().y());
    for( size_t y = 0; y < level.rows(); y++ )
    {
        for( size_t x = 0; x < level.cols(); x++ )
        {
            Tile tile;
            switch(level.get(x, y))
            {
            case 0: /* WALKABLE */
                tile = {TileType::Walkable, TileContents::None};
                break;
            case 1: /* SOLID */
                tile = {TileType::Solid, TileContents::None};
                break;
            case 2: /* HAZARD */
                tile = {TileType::Hazard, TileContents::None};
                break;
            case 3: /* WALKABLE WITH SHIFTER */
                tile = {TileType::Walkable, TileContents::DimensionShifter};
                break;
            case 4: /* HAZARD WITH SHIFTER */
                tile = {TileType::Hazard, TileContents::DimensionShifter};
                break;
            case 5: /* WALKABLE WITH GOAL */
                tile = {TileType::Walkable, TileContents::GoalItem};
                break;
            case 6: /* HAZARD WITH GOAL */
                tile = {TileType::Hazard, TileContents::GoalItem};
                break;
            }
            if( tile.tileContents == TileContents::GoalItem )
            {
                m_totalGoalItems++;
            }
            m_tileMap.set(x, y, tile);
        }
    }
}

Scene::~Scene()
{

}

void Scene::render()
{
    ALLEGRO_TRANSFORM tr;
    al_identity_transform(&tr);
    al_build_transform(&tr, 0, 0, Constants::ScreenScale, Constants::ScreenScale, 0);
    al_use_transform(&tr);

    for( size_t y = 0; y < m_tileMap.rows(); y++ )
    {
        for( size_t x = 0; x < m_tileMap.cols(); x++ )
        {
            auto tile = m_tileMap.get(x, y);
            auto texture = getTileTexture(tile);
            auto px = x * Constants::TileSize;
            auto py = y * Constants::TileSize;
            texture.draw(px, py);

            aether::graphics::Texture contents;
            switch(tile.tileContents)
            {
            case TileContents::DimensionShifter:
                contents = m_sheet->getFrame(5 + (m_isHalloween ? 8u : 0u));
                break;
            case TileContents::GoalItem:
                contents = m_sheet->getFrame(6);
                break;
            case TileContents::None:
                break;
            }

            if( contents.valid() )
            {
                contents.draw( px, py );
            }
        }
    }

    auto player_tex = (m_isHalloween ? m_sheet->getFrame(4) : m_sheet->getFrame(12));

    if( m_sceneStatus == Status::Won )
    {
        player_tex = m_sheet->getFrame(15);
    }
    else if( m_sceneStatus == Status::Lost )
    {
        player_tex = m_sheet->getFrame(14);
    }

    player_tex.draw(
                m_playerPos.x() * Constants::TileSize,
                m_playerPos.y() * Constants::TileSize);
}

void Scene::update(uint64_t delta)
{
    if( aether::core::is_key_just_pressed(aether::core::KeyCode::O) )
    {
        m_isHalloween = !m_isHalloween;
    }

    if( aether::core::is_key_just_pressed(aether::core::KeyCode::K) )
    {
        m_sceneStatus = Status::Lost;
    }

    m_playerMovementDirection.set(0, 0);
    if( aether::core::is_key_just_pressed(aether::core::KeyCode::Right) )
    {
        m_playerMovementDirection.x(1);
    }
    else if( aether::core::is_key_just_pressed(aether::core::KeyCode::Left) )
    {
        m_playerMovementDirection.x(-1);
    }
    else if( aether::core::is_key_just_pressed(aether::core::KeyCode::Up) )
    {
        m_playerMovementDirection.y(-1);
    }
    else if( aether::core::is_key_just_pressed(aether::core::KeyCode::Down) )
    {
        m_playerMovementDirection.y(1);
    }

    bool wants_movement = m_playerMovementDirection.x() + m_playerMovementDirection.y() != 0;

    if( wants_movement && m_playerLockedInIce )
    {
        auto new_player_tile = m_playerPos + m_lastPlayerMovementDirection;
        if( canWalkTo(new_player_tile) )
        {
            m_playerMovementDirection = m_lastPlayerMovementDirection;
        }
    }

    auto new_player_pos = m_playerPos + m_playerMovementDirection;

    bool moved = false;

    if( m_playerPos != new_player_pos && canWalkTo(new_player_pos) )
    {
        m_playerPos = new_player_pos;
        moved = true;
    }

    if( moved )
    {
        Tile& new_player_tile = getPlayerTile();
        switch(new_player_tile.tileContents)
        {
        case TileContents::DimensionShifter:
            m_isHalloween = !m_isHalloween;
            break;
        case TileContents::GoalItem:
            m_numGoalItems++;
            if( m_totalGoalItems == m_numGoalItems )
            {
                m_sceneStatus = Status::Won;
            }
            break;
        case TileContents::None:
            break;
        }
        new_player_tile.tileContents = TileContents::None;

        if( new_player_tile.tileType == TileType::Hazard )
        {
            if( m_isHalloween )
            {
                m_sceneStatus = Status::Lost;
            }
            else
            {
                m_playerLockedInIce = true;
                m_lastPlayerMovementDirection = m_playerMovementDirection;
            }
        }
        else
        {
            m_playerLockedInIce = false;
        }
    }

}

Scene::Status Scene::status()
{
    return m_sceneStatus;
}
