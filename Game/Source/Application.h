#pragma once

#include "Engine/Simulation.h"

class Application : public Engine::Simulation
{
    // Application

public:

    // Constructor of an Application
    Application();


    // Destructor of an Application
    ~Application();

public:

    // Called to set up PerGameSettings
    VOID SetupPerGameSetting();

    // Initialize the Application
    VOID Initialize();

    // Game Loop - called on a loop while Application is running
    VOID Update();
};