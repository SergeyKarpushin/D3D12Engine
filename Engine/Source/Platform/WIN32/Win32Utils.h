#pragma once

namespace Win32 
{
    enum WindowType {
        STATIC = WS_OVERLAPPEDWINDOW,
        RESIZABLE = WS_SIZEBOX,
        POPUP = WS_POPUP
    };

    namespace Utils 
    {
        BOOL ENGINE_API AddBitmap(const WCHAR* szFileName, HDC hWinDC, INT x = 0, INT y = 0);
    }
}