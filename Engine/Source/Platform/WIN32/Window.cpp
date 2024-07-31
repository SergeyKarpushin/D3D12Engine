#include "Engine.h"
#include "Window.h"

#include "Uxtheme.h"
#pragma comment(lib, "Uxtheme.lib")

#define DCX_USERSTYLE 0x00010000

namespace Win32
{
    Window::Window(std::wstring title, HICON icon, WindowType type)
        : SubObject(title, title, icon), m_type(type)
    {
        SetSize(DEFAULT_SIZE_X, DEFAULT_SIZE_Y);
    }

    Window::~Window()
    {
    }

    VOID Window::Initialize()
    {
        RECT desktop;
        const HWND hWnd = GetDesktopWindow();
        GetWindowRect(hWnd, &desktop);

        INT x = Size().cx;
        INT y = Size().cy;

        m_hWnd = CreateWindow(m_Class.c_str(), m_Title.c_str(), m_type,
            (desktop.right - x) / 2, (desktop.bottom - y) / 2, x, y, 0, 0, HInstance(), (void*)this);
        if (!m_hWnd) {
            MessageBox(0, L"Failed to Create Window!", 0, 0);
            PostQuitMessage(0);
        }

        ShowWindow(m_hWnd, SW_SHOW);
        UpdateWindow(m_hWnd);
    }

    LRESULT Window::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_NCCREATE: { OnNonClientCreate(); } return TRUE;
        case WM_NCACTIVATE: { OnNonClientActivate((BOOL)wParam != m_Active); } return TRUE;
        case WM_NCPAINT: { OnNonClientPaint((HRGN)wParam); } return FALSE;
        case WM_TIMER: { RedrawWindow(); } break;
        }
        return SubObject::MessageHandler(hwnd, message, wParam, lParam);
    }

    VOID Window::RedrawWindow()
    {
        SetWindowPos(Handle(), NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_DRAWFRAME | SWP_FRAMECHANGED);
        SendMessage(Handle(), WM_PAINT, 0, 0);
    }

    VOID Window::OnNonClientCreate()
    {
        SetTimer(Handle(), 1, 100, NULL);
        SetWindowTheme(Handle(), L"", L"");
    }

    VOID Window::OnNonClientActivate(BOOL active)
    {
        m_Active = active;
    }

    VOID Window::OnNonClientPaint(HRGN region)
    {
        HDC hdc = GetDCEx(Handle(), region, DCX_WINDOW | DCX_INTERSECTRGN | DCX_USERSTYLE);

        RECT rect;
        GetWindowRect(Handle(), &rect);

        SIZE size = { rect.right - rect.left, rect.bottom - rect.top };

        HBITMAP hbmMem = CreateCompatibleBitmap(hdc, size.cx, size.cy);
        HANDLE hOld = SelectObject(hdc, hbmMem);

        RECT newRect = { 0, 0, size.cx, size.cy };
        HBRUSH brush = CreateSolidBrush(RGB(46, 46, 46));

        FillRect(hdc, &newRect, brush);
        DeleteObject(brush);

        BitBlt(hdc, 0, 0, size.cx, size.cy, hdc, 0, 0, SRCCOPY);

        SelectObject(hdc, hOld);
        DeleteObject(hbmMem);

        ReleaseDC(Handle(), hdc);
    }
}
