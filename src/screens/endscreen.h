#pragma once

#include <aether/aether.h>

class FGJX;

class EndScreen : public aether::core::IScreen
{
public:
    EndScreen(FGJX *game);

    void show() final;
    void hide() final;
    void render() final;
    void update(uint64_t delta) final;

private:
    FGJX* m_game;

    bool m_gameFinished = false;

};
