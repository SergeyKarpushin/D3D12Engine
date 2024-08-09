#pragma once

#define CB_CLOSE 0
#define CB_MINIMIZE 1
#define CB_MAXIMIZE 2

namespace Win32
{
    class Caption
    {
    public:
        struct CaptionButton {
            WSTRING text = L"";
            INT command;
            INT width = 40;
            RECT rect;

            CaptionButton(WSTRING text, INT command, INT width = 40) : text(text), command(command), width(width) {};
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