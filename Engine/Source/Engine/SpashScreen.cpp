#include "Engine.h"
#include "SpashScreen.h"

namespace SplashScreen
{
    SplashWindow* m_SplashWindow;

    VOID Open()
    {
        if (m_SplashWindow == nullptr) {
            m_SplashWindow = new SplashWindow();
        }
    }

    VOID Close()
    {
        delete m_SplashWindow;
    }

    VOID AddMessage(const WCHAR* message)
    {
        return VOID ENGINE_API();
    }
}

SplashWindow::SplashWindow()
    : Win32::Window(L"SplashScreen", L"SplashScreen", NULL, 500, 600)
{
    wcscpy_s(m_OutputMessage, L"SplashScreen starting...");
    Win32::Window::RegisterNewClass();
    Win32::Window::Initialize();
}

SplashWindow::~SplashWindow()
{
}
