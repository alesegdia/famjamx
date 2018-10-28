#include "endscreen.h"

#include "../fgjx.h"


EndScreen::EndScreen(FGJX *game)
{
    m_game = game;
}

void EndScreen::show()
{
    if( m_game->gameplayScreen.status() == Scene::Status::Won )
    {
        m_game->currentLevel++;
    }
    m_gameFinished = m_game->levels.numLevels() == m_game->currentLevel;
    if( m_gameFinished )
    {
        m_game->currentLevel = 0;
    }
}

void EndScreen::hide()
{

}

void EndScreen::render()
{
    aether::graphics::clear(1, 0, 0);

    m_game->gameplayScreen.scene()->render();

    aether::graphics::draw_filled_rectangle(
                0, 10, Constants::ScreenWidth, 10 + 20,
                aether::graphics::Color(0,0,0));

    std::string txt;
    if( m_gameFinished )
    {
        txt = "Game Finished!";
    }
    else if( m_game->gameplayScreen.status() == Scene::Status::Won )
    {
        txt = "Stage clear!";
    }
    else if( m_game->gameplayScreen.status() == Scene::Status::Lost )
    {
        txt = "You Died...";
    }

    m_game->assets.font.print(txt.c_str(), 10, 15, aether::graphics::Color(255, 255, 255));
}


void EndScreen::update(uint64_t delta)
{
    if( aether::core::is_key_just_pressed(aether::core::KeyCode::Enter) )
    {
        if( m_gameFinished )
        {
            m_game->setScreen(&m_game->menuScreen);
        }
        else
        {
            m_game->setScreen(&m_game->gameplayScreen);
        }
    }
}
