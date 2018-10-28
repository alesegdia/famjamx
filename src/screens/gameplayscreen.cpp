#include "gameplayscreen.h"

#include "../fgjx.h"


GameplayScreen::GameplayScreen(FGJX *game)
    : m_game(game)
{

}

void GameplayScreen::show()
{
    m_scene.reset(new Scene(&m_game->assets.alltiles_sheet, m_game->getCurrentLevel()));
}

void GameplayScreen::hide()
{

}

void GameplayScreen::render()
{
    aether::graphics::clear(1, 0, 0);

    m_scene->render();

}


void GameplayScreen::update(uint64_t delta)
{
    m_scene->update(delta);

    if( m_scene->status() != Scene::Status::Running )
    {
        m_game->setScreen(&m_game->endScreen);
    }

}
