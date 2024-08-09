#include "Engine.h"
#include "Window.h"

#include "Uxtheme.h"
#pragma comment(lib, "Uxtheme.lib")

#define DCX_USERSTYLE 0x00010000

namespace Win32
{
    Window::Window(std::wstring title, HICON icon, WindowType type)
        : SubObject(title, title, icon), m_Type(type)
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

        RECT R = { 0, 0, Size().cx, Size().cy };
        AdjustWindowRect(&R, m_Type, false);
        int width = R.right - R.left;
        int height = R.bottom - R.top;

        INT x = Size().cx;
        INT y = Size().cy;

        m_Handle = CreateWindow(m_Class.c_str(), m_Title.c_str(), m_Type,
            (desktop.right - x) / 2, (desktop.bottom - y) / 2, x, y, 0, 0, HInstance(), (void*)this);
        if (!m_Handle) {
            MessageBox(0, L"Failed to Create Window!", 0, 0);
            PostQuitMessage(0);
        }

        ShowWindow(m_Handle, SW_SHOW);
        UpdateWindow(m_Handle);
    }

    LRESULT Window::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_NCCREATE: { OnNonClientCreate(); } return TRUE;
        case WM_NCACTIVATE: { OnNonClientActivate((BOOL)wParam != WA_INACTIVE); } return TRUE;
        case WM_NCPAINT: { OnNonClientPaint((HRGN)wParam); } return FALSE;
        case WM_NCLBUTTONDOWN: { OnNonClientLeftMouseButtonDown(); } break;
        case WM_NCLBUTTONDBLCLK: { Win32::Utils::MaximizeWindow(Handle()); } return 0;
        case WM_GETMINMAXINFO: { OnGetMinMaxInfo((MINMAXINFO*)lParam); } return 0;
        case WM_EXITSIZEMOVE: { OnExitSizeMove(); } break;
        case WM_PAINT: { OnPaint(); } return 0;
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

        Win32::Caption::AddCaptionButton(new CaptionButton(L"X", CB_CLOSE));
        Win32::Caption::AddCaptionButton(new CaptionButton(L"🗖", CB_MAXIMIZE));
        Win32::Caption::AddCaptionButton(new CaptionButton(L"🗕", CB_MINIMIZE));
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

        PaintCaption(hdc);

        // End draw
        DeleteObject(brush);

        BitBlt(hdc, 0, 0, size.cx, size.cy, hdc, 0, 0, SRCCOPY);

        SelectObject(hdc, hOld);
        DeleteObject(hbmMem);

        ReleaseDC(Handle(), hdc);
    }

    VOID Window::OnNonClientLeftMouseButtonDown()
    {
        POINT pt;
        GetCursorPos(&pt);

        RECT rect;
        GetWindowRect(Handle(), &rect);

        pt.x -= rect.left;
        pt.y -= rect.top;

        int offset = 0;
        for (auto& btn : CaptionButtons())
        {
            if (btn->rect.left <= pt.x && btn->rect.right >= pt.x && btn->rect.top <= pt.y && btn->rect.bottom >= pt.y)
            {
                switch (btn->command)
                {
                case CB_CLOSE: { SendMessage(Handle(), WM_CLOSE, 0, 0); } break;
                case CB_MAXIMIZE: { Win32::Utils::MaximizeWindow(Handle()); } break;
                case CB_MINIMIZE: { SendMessage(Handle(), WM_SYSCOMMAND, SC_MINIMIZE, 0); } break;
                }
            }
        }

    }

    VOID Window::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
    {
        RECT workarea;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &workarea, 0);
        lpMMI->ptMaxPosition.x = workarea.left;
        lpMMI->ptMaxPosition.y = workarea.top;
        lpMMI->ptMaxSize.x = workarea.right - workarea.left;
        lpMMI->ptMaxSize.y = workarea.bottom - workarea.top;
        lpMMI->ptMinTrackSize.x = 400;
        lpMMI->ptMinTrackSize.y = 300;
    }


    VOID Window::PaintCaption(HDC hdc)
    {
        RECT rect;
        GetWindowRect(Handle(), &rect);

        SIZE size = { rect.right - rect.left, rect.bottom - rect.top };

        if (ShowTitle()) {
            rect = { 0, 0, size.cx, 30 };

            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, Active() ? RGB(255, 255, 255) : RGB(92, 92, 92));

            DrawText(hdc, m_Title.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }

        POINT pt;
        GetCursorPos(&pt);

        GetWindowRect(Handle(), &rect);

        pt.x -= rect.left;
        pt.y -= rect.top;

        int offset = 0;
        for (auto& btn : CaptionButtons()) {
            offset += btn->width;
            btn->rect = RECT{ size.cx - offset, 0, size.cx - offset + btn->width, 30 };

            if (btn->rect.left <= pt.x && btn->rect.right >= pt.x && btn->rect.top <= pt.y && btn->rect.bottom >= pt.y) {
                HBRUSH brush = CreateSolidBrush(RGB(92, 92, 92));
                FillRect(hdc, &btn->rect, brush);
                DeleteObject(brush);
            }

            if (btn->text.compare(L"🗖") == 0 && Win32::Utils::IsWindowFullscreen(Handle()))
            {
                btn->text = L"🗗";
            }
            else if (btn->text.compare(L"🗗") == 0 && !Win32::Utils::IsWindowFullscreen(Handle()))
            {
                btn->text = L"🗖";
            }

            DrawText(hdc, btn->text.c_str(), -1, &btn->rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }

    }

    VOID Window::OnExitSizeMove() {
        RECT rect;
        GetWindowRect(Handle(), &rect);
        RECT WorkArea;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
        if (rect.top < WorkArea.top + 10 && !Win32::Utils::IsWindowFullscreen(Handle())) {
            Win32::Utils::MaximizeWindow(Handle());
        }
    }

    VOID Window::OnPaint() {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(Handle(), &ps);

        RECT rect;
        GetClientRect(Handle(), &rect);
        HBRUSH brush = CreateSolidBrush(RGB(36, 36, 36));
        FillRect(hdc, &rect, brush);
        DeleteObject(brush);

        EndPaint(Handle(), &ps);
    }
}
