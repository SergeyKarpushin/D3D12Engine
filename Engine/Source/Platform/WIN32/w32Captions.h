#pragma once

namespace Win32
{
    class Caption
    {
    public:
        struct CaptionButton {
            WSTRING text = L"X";
            INT width = 50;
            RECT rect;

            CaptionButton(WSTRING text, INT width = 50) : text(text), width(width) {};
        };

    private:
        BOOL m_ShowTitle;
        std::list<CaptionButton*> m_CaptionButtons;

    public:
        VOID ShowTitle(BOOL show) { m_ShowTitle = show; }
        BOOL ShowTitle() { return m_ShowTitle; }
        std::list<CaptionButton*> CaptionButtons() { return m_CaptionButtons; }
        VOID AddCaptionButton(CaptionButton* button);
    };
}