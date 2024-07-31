#pragma once

namespace Win32
{
    class Caption
    {

    private:
        BOOL m_ShowTitle;

    public:
        VOID ShowTitle(BOOL show) { m_ShowTitle = show; }
    public:
        BOOL ShowTitle() { return m_ShowTitle; }
    };
}