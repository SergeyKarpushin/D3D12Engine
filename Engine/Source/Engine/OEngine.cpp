#include "Engine.h"

namespace Engine {
    OEngine g_OEngine;

    EngineMode ENGINE_API GetMode()
    {
        return g_OEngine.GetEngineMode();
    }

    VOID ENGINE_API SetMode(EngineMode mode)
    {
        g_OEngine.SetEngineMode(mode);
    }

    std::wstring ENGINE_API EngineModeToString()
    {
        switch (GetMode()) {
        case Engine::DEBUG:      return L"Debug";
        case Engine::RELEASE:    return L"Release";
        case Engine::EDITOR:     return L"Editor";
        case Engine::SERVER:     return L"Server";
        default: return L"None";
        }
    }
}

OEngine::OEngine()
{
#ifdef _DEBUG
    m_EngineMode = EngineMode::DEBUG;
#else
    m_EngineMode = EngineMode::RELEASE;
#endif
}

OEngine::~OEngine()
{
}

EngineMode OEngine::GetEngineMode()
{
    return m_EngineMode;
}

VOID OEngine::SetEngineMode(EngineMode mode)
{
    m_EngineMode = mode;
}
