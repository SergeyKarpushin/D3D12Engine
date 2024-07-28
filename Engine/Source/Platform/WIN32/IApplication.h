#pragma once

#define ENTRYAPP(x) Win32::IApplication* EntryApplication() { return new x; }

namespace Win32 
{

    class ENGINE_API IApplication
    {
        // Application

    public:

        // Constructor of an Application
        IApplication();

        // Destructor of an Application
        virtual ~IApplication() {};

    public:

        // Called to set up PerGameSettings
        virtual VOID SetupPerGameSetting() = 0;

        // Initialize the Application
        virtual VOID Initialize() = 0;

        // Game Loop - called on a loop while Application is running
        virtual VOID Update() = 0;
    };

    IApplication* EntryApplication();
}