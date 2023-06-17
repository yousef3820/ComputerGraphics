#include <windows.h>
#include <stack>
#include "FloodFilling.h"

using namespace std;

class NonRecursiveFloodFilling : public FloodFilling {
protected:
    void Fill(HDC hdc, int x, int y, COLORREF bgColor, COLORREF bColor) {
        stack<point> s;
        s.push(point(x,y));
        while(!s.empty())
        {
            point p = s.top();
            s.pop();
            COLORREF c = GetPixel(hdc,p.x,p.y);
            if(c == bgColor || c == bColor)
                continue;
            SetPixel(hdc,p.x,p.y,bgColor);
            s.push(point(p.x + 1,p.y));
            s.push(point(p.x - 1,p.y));
            s.push(point(p.x,p.y + 1));
            s.push(point(p.x,p.y - 1));
        }
    }

public:
    NonRecursiveFloodFilling(HDC hdc, COLORREF bgColor, COLORREF bColor) : FloodFilling(hdc,bgColor,bColor) {}

    virtual ~NonRecursiveFloodFilling() {}
};
