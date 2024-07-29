#include "Engine.h"
#include "Window.h"

namespace Win32
{
    Window::Window(std::wstring className, std::wstring classTitile, HICON icon, INT width, INT height)
        : SubObject(className, classTitile, icon), m_Width(width), m_Height(height)
    {
    }

    Window::~Window()
    {
    }

    VOID Window::Initialize()
    {
        RECT desktop;
        const HWND hWnd = GetDesktopWindow();
        GetWindowRect(hWnd, &desktop);

        m_hWnd = CreateWindow(m_Class.c_str(), m_Title.c_str(), WS_POPUP,
            (desktop.right - m_Width) / 2, (desktop.bottom - m_Height) / 2, m_Width, m_Height, 0, 0, HInstance(), (void*)this);
        if (!m_hWnd) {
            MessageBox(0, L"Failed to Create Window!", 0, 0);
            PostQuitMessage(0);
        }

        ShowWindow(m_hWnd, SW_SHOW);

    }

    LRESULT Window::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        return CommonMessageHandler(hwnd, message, wParam, lParam);
    }
}
