#include "GameProject.h"
#include "Platform/WIN32/WinEntry.h"
#include "Engine/Simulation.h"

class GameProject : public Simulation
{
public:
    GameProject() {};
    ~GameProject() {};

public:

    // Called to set up PerGameSettings
    VOID SetupPerGameSetting();

    // Initialize the Application
    VOID Initialize() {};

    // Game Loop - called on a loop while Application is running
    VOID Update() {};
};

ENTRYAPP(GameProject)

VOID GameProject::SetupPerGameSetting()
{
    PerGameSettings::SetGameName(IDS_PERGAMENAME);
    PerGameSettings::SetShortName(IDS_SHORTNAME);
    PerGameSettings::SetMainIcon(IDI_MAINICON);
    PerGameSettings::SetSplashURL(IDS_SPLASHURL);
}
