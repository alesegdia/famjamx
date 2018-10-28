#include <aether/aether.h>

#include "screens/menu.h"
#include "screens/gameplayscreen.h"
#include "screens/endscreen.h"
#include "assets.h"

class FGJX : public aether::core::Application
{
public:
    FGJX(int w, int h);

    int ready(int argc, char **argv) override;

    void update(uint64_t delta) override;

    void dispose() override;

    LevelConstructionData getCurrentLevel()
    {
        return levels.getLevel(currentLevel);
    }

    MenuScreen menuScreen;
    GameplayScreen gameplayScreen;
    EndScreen endScreen;

    Assets assets;

    int currentLevel = 0;
    Levels levels;

};

