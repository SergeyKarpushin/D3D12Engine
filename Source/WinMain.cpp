#include "pch.h"
/* --------------------------------------------------------------- */
/*  Filename: WinMain.cpp                                          */
/*  Author: Sergey Karpushin                                       */
/*  Licence: MIT Licence                                           */
/* --------------------------------------------------------------- */

#pragma region Global Variables
/* --------------------------------------------------------------- */
/* Global Variables                                                */
/* --------------------------------------------------------------- */
WCHAR	WindowClass[MAX_NAME_STRING];
WCHAR	WindowTitle[MAX_NAME_STRING];

INT		WindowHeight;
INT		WindowWidth;

HICON   hIcon;
/* --------------------------------------------------------------- */
#pragma endregion

#pragma region Pre-Declarations
/* --------------------------------------------------------------- */
/* Pre-Declarations                                                */
/* --------------------------------------------------------------- */
VOID InitializeVariables();
VOID CreateWindowClass();
VOID InitializeWindow();
VOID MessageLoop();
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
/* --------------------------------------------------------------- */
#pragma endregion

#pragma region Operations
/* --------------------------------------------------------------- */
/* Operations                                                      */
/* --------------------------------------------------------------- */
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
    InitializeVariables();
    CreateWindowClass();
    InitializeWindow();
    MessageLoop();

    return 0;
}
/* --------------------------------------------------------------- */
#pragma endregion

#pragma region Functions
/* --------------------------------------------------------------- */
/* Functions                                                       */
/* --------------------------------------------------------------- */
VOID InitializeVariables()
{
    LoadString(HInstance(), IDS_PERGAMENAME, WindowTitle, MAX_NAME_STRING);
    LoadString(HInstance(), IDS_WINDOWCLASS, WindowClass, MAX_NAME_STRING);

    WindowWidth = 1366;
    WindowHeight = 768;
    hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));
}

VOID CreateWindowClass()
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

    wcex.hIcon = hIcon;
    wcex.hIconSm = hIcon;

    wcex.lpszClassName = WindowClass;
    wcex.lpszMenuName = nullptr;

    wcex.hInstance = HInstance();

    wcex.lpfnWndProc = WindowProcess;

    RegisterClassEx(&wcex);
}

VOID InitializeWindow() {
    HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);
    if (!hWnd) {
        MessageBox(0, L"Failed to Create Window!", 0, 0);
        PostQuitMessage(0);
    }

    ShowWindow(hWnd, SW_SHOW);
}

VOID MessageLoop()
{
    MSG msg = { 0 };
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
/* --------------------------------------------------------------- */
#pragma endregion