#include "Engine.h"
#include "CmdLineArgs.h"
#include <algorithm>

VOID CmdLineArgs::ReadArguments()
{
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    for (int i = 1; i < argc; i++)
    {
        std::wstring key = argv[i];
        if (key[0] == '-')
        {
            key.erase(0, 1);
            std::transform(key.begin(), key.end(), key.begin(), ::tolower);
            ReadArgument(key.c_str());
        }
    }
}

VOID CmdLineArgs::ReadArgument(const WCHAR* arg)
{
    if (wcscmp(arg, L"mtail") == 0)
        Logger::StartMTail();
    if (wcscmp(arg, L"debug") == 0)
        Engine::SetMode(Engine::EngineMode::DEBUG);
    if (wcscmp(arg, L"release") == 0)
        Engine::SetMode(Engine::EngineMode::RELEASE);
    if (wcscmp(arg, L"editor") == 0)
        Engine::SetMode(Engine::EngineMode::EDITOR);
    if (wcscmp(arg, L"server") == 0)
        Engine::SetMode(Engine::EngineMode::SERVER);

}
