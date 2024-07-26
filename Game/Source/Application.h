#pragma once

class Application
{
    // Application

public:

    // Constructor of an Application
    Application();


    // Destructor of an Application
    ~Application();

public:

    // Initialize the Application
    VOID Initialize();

    // Game Loop - called on a loop while Application is running
    VOID Update();
};