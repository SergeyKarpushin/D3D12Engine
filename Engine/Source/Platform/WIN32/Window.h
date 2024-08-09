#pragma once

#include "Platform/Win32/SubObject.h"

#define DEFAULT_SIZE_X 800
#define DEFAULT_SIZE_Y 600

namespace Win32 {

#pragma warning(disable : 4275)
    class ENGINE_API Window : public Win32::SubObject, public Win32::Caption
#pragma warning(default : 4275)
    {
    public:
        Window(std::wstring titile, HICON icon, WindowType type = RESIZABLE);
        ~Window();

        virtual VOID Initialize() override;
        virtual	LRESULT	MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;

        VOID OnNonClientCreate();
        VOID OnNonClientActivate(BOOL active);
        VOID OnNonClientPaint(HRGN region);
        VOID OnNonClientLeftMouseButtonDown();
        VOID PaintCaption(HDC hdc);
        VOID RedrawWindow();

    protected:
        SIZE         m_Size;
        WindowType   m_Type;
        BOOL         m_Active;

    public:
        // Getters
        SIZE        Size() const { return m_Size; }
        BOOL        Active() const { return m_Active; }
    public:
        // Setters
        VOID        SetSize(SIZE size) { m_Size = size; }
        VOID        SetSize(LONG cx, LONG cy) { m_Size.cx = cx; m_Size.cy = cy; }
        VOID		Active(BOOL active) { m_Active = active; }
    };
}