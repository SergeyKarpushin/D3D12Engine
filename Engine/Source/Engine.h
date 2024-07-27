#pragma once

#ifdef WIN32

#include <Windows.h>

#endif

#ifdef BUILD_DLL
    #define ENGINE_API __declspec(dllexport)
#else
    #define ENGINE_API __declspec(dllimport)
#endif

#define MAX_NAME_STRING 256

#include "Common/Logger.h"
#include "Core/PerGameSettings.h"