#pragma once

#include <aether/aether.h>

class FGJX;

class MenuScreen : public aether::core::IScreen
{
public:
    MenuScreen(FGJX* game);

    void show() final;
    void hide() final;
    void render() final;
    void update(uint64_t delta) final;

private:
    FGJX* m_game;
    aether::graphics::AnimationData m_animData;
    int m_status = 0;

};
