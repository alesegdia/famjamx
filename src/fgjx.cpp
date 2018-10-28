
#include "fgjx.h"

FGJX::FGJX(int w, int h)
    : aether::core::Application(w, h),
      menuScreen(this),
      gameplayScreen(this),
      endScreen(this)
{

}

int FGJX::ready(int argc, char **argv)
{
    assets.load();
    setScreen(&menuScreen);
    assets.theme.playmode(aether::audio::PlayMode::Loop);
    assets.theme.play();
    return 0;
}

void FGJX::update(uint64_t delta)
{
    aether::core::Application::update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
    {
        close();
    }
}

void FGJX::dispose()
{
    assets.cleanup();
}
