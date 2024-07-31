#pragma once

namespace Win32 {

    class ENGINE_API SubObject {
    public:
        SubObject(std::wstring className, std::wstring classTitile, HICON icon);
        ~SubObject();

        virtual VOID RegisterNewClass();
        virtual VOID Initialize() = 0;

    protected:
        static			LRESULT CALLBACK	SetupMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        static			LRESULT				AssignMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        virtual			LRESULT				MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


    protected:
#pragma warning(disable: 4251)
        std::wstring	m_Class;
        std::wstring	m_Title;
#pragma warning(default: 4251)
        HICON           m_hIcon;
        HWND            m_Handle;
    public:
        HWND Handle() { return m_Handle; }
        VOID SetHandle(HWND hWnd) { m_Handle = hWnd; }
    };
}