#pragma once

#include "Platform/Win32/SubObject.h"

namespace Win32 {

    class ENGINE_API Window : public Win32::SubObject {
    public:
        Window(std::wstring className, std::wstring classTitile, HICON icon, INT width, INT height);
        ~Window();

        virtual VOID Initialize() override;
        virtual	LRESULT	MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) override;


    private:
        INT     m_Width;
        INT     m_Height;
    };
}