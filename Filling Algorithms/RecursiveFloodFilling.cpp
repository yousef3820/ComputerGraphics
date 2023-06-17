#include <windows.h>
#include "FloodFilling.cpp"

class RecursiveFloodFilling : public FloodFilling {
protected:
    void Fill(HDC hdc, int x, int y, COLORREF bgColor, COLORREF bColor) {
        COLORREF f = GetPixel(hdc, x, y);
        if (f == bgColor || f == bColor)
            return;

        SetPixel(hdc, x, y, bgColor);
        Fill(hdc, x + 1, y, bgColor, bColor);
        Fill(hdc, x - 1, y, bgColor, bColor);
        Fill(hdc, x, y + 1, bgColor, bColor);
        Fill(hdc, x, y - 1, bgColor, bColor);
    }

public:
    RecursiveFloodFilling(HDC hdc, COLORREF bgColor, COLORREF bColor) : FloodFilling(hdc,bgColor,bColor) {}

    virtual ~RecursiveFloodFilling() {}
};
