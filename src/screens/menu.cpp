#include "menu.h"

#include "../fgjx.h"


MenuScreen::MenuScreen(FGJX *game)
{
    m_game = game;
}

void MenuScreen::show()
{
    m_status = 0;
}

void MenuScreen::hide()
{

}

void MenuScreen::render()
{
    ALLEGRO_TRANSFORM tr;
    al_identity_transform(&tr);
    al_build_transform(&tr, 0, 0, Constants::ScreenScale, Constants::ScreenScale, 0);
    al_use_transform(&tr);

    aether::graphics::clear(1, 0, 0);
    m_game->assets.fluxus.draw(33, 35);
    m_game->assets.font.print("Fluxus Adventures", 14, 10, aether::graphics::Color(255, 0, 0));
    m_game->assets.font.print("in HalloXmas", 27, 20, aether::graphics::Color(255, 0, 0));

    if( m_status == 0 )
    {
        m_game->assets.font.print("<ARROWS> to move!", 12, 70, aether::graphics::Color(255, 255, 255));
        m_game->assets.font.print("<ENTER> to accept!", 14, 80, aether::graphics::Color(255, 255, 255));
        m_game->assets.font.print("<K> to suicide!", 22, 90, aether::graphics::Color(255, 255, 255));
    }
    else if( m_status == 1 )
    {
        m_game->assets.font.print("Fluxus ship crashed in", 6, 70, aether::graphics::Color(255, 255, 255));
        m_game->assets.font.print("the land of HalloXmas", 6, 80, aether::graphics::Color(255, 255, 255));
    }
    else
    {
        m_game->assets.alltiles_sheet.getFrame(6).draw(14, 70);
        m_game->assets.font.print("Collect these to", 26, 70, aether::graphics::Color(255, 255, 255));
        m_game->assets.font.print("repair the ship and", 12, 80, aether::graphics::Color(255, 255, 255));
        m_game->assets.font.print("return to FluxLand!", 14, 90, aether::graphics::Color(255, 255, 255));
    }


}


void MenuScreen::update(uint64_t delta)
{
    if( aether::core::is_key_just_pressed(aether::core::KeyCode::Enter) )
    {
        m_status++;
        if( m_status == 3 )
        {
            m_game->setScreen(&m_game->gameplayScreen);
        }
    }
}
