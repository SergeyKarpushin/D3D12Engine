#pragma once

#include "Platform/WIN32/IApplication.h"

namespace Engine {

    class ENGINE_API Simulation : public Win32::IApplication {
    public:
        Simulation();
        ~Simulation();

    };
}