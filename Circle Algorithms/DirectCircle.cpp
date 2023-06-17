#include <cmath>
#include "Circle.cpp"

class DirectCircle : public Circle {
protected:
    void DrawCircle(HDC hdc, COLORREF color) {
        int x=0;
        double y=R;
        int squared_R = R*R;
        Draw8Points(hdc,xc,yc,x,round(y),color);
        while (x<y) {
            y = sqrt(squared_R - x*x);
            x++;
            Draw8Points(hdc,xc,yc,x,round(y),color);
        }
    }

public:
    DirectCircle(HDC hdc, COLORREF color) : Circle(hdc,color) {};

    virtual ~DirectCircle() {}
};
