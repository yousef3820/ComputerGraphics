#include <cmath>

class AdvancedMidpointCircle : public Circle {
protected:
    void DrawCircle(HDC hdc, COLORREF color) {
        int x=0, y=R;
        int d = 1-R;
        int c1=3, c2=5-2*R;
        Draw8Points(hdc,xc,yc,x,y,color);
        while (x<y) {
            if (d>0) {
                d+=c2;
                c2+=4;
                y--;
            }
            else {
                d+=c1;
                c2+=2;
            }

            c1+=2;
            x++;
            Draw8Points(hdc,xc,yc,x,y,color);
        }
    }

public:
    AdvancedMidpointCircle(HDC hdc, COLORREF color) : Circle(hdc,color) {}

    virtual ~AdvancedMidpointCircle() {}
};
