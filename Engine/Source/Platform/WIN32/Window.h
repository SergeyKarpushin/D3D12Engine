#pragma once

#include "Platform/Win32/SubObject.h"

#define DEFAULT_SIZE_X 800
#define DEFAULT_SIZE_Y 600

namespace Win32 {

    class ENGINE_API Window : public Win32::SubObject
    {
    public:
        Window(std::wstring titile, HICON icon, WindowType type = RESIZABLE);
        ~Window();

        virtual VOID Initialize() override;
        virtual	LRESULT	MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

        VOID OnNonClientCreate();
        VOID OnNonClientPaint(HRGN region);
        VOID RedrawWindow();

    protected:
        SIZE         m_Size;
        WindowType   m_type;

    public:
        SIZE        Size() const { return m_Size; }
        VOID        SetSize(SIZE size) { m_Size = size; }
        VOID        SetSize(LONG cx, LONG cy) { m_Size.cx = cx; m_Size.cy = cy; }
    };
}