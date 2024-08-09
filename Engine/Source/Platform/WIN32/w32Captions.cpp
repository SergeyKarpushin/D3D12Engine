#include "Engine.h"
#include "w32Captions.h"

namespace Win32 {
    VOID Caption::AddCaptionButton(CaptionButton* button)
    {
        m_CaptionButtons.push_back(button);
    }
}