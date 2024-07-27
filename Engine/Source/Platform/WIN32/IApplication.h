#pragma once

#define ENTRYAPP(x) IApplication* EntryApplication() { return new x; }

class ENGINE_API IApplication
{
    // Application

public:

    // Constructor of an Application
    IApplication();

    // Destructor of an Application
    virtual ~IApplication() {};

public:

    // Initialize the Application
    virtual VOID Initialize() = 0;

    // Game Loop - called on a loop while Application is running
    virtual VOID Update() = 0;
};

IApplication* EntryApplication();