#include <cmath>

class MidpointCircle : public Circle {
protected:
    void DrawCircle(HDC hdc, COLORREF color) {
        int x=0, y=R;
        Draw8Points(hdc,xc,yc,x,y,color);
        while (x<y) {
            double d = pow(x+1,2) + pow(y-1/2,2) - R*R;
            if (d>0)
                y--;
            x++;
            Draw8Points(hdc,xc,yc,x,y,color);
        }
    }

public:
    MidpointCircle(HDC hdc, COLORREF color) : Circle(hdc,color) {}

    virtual ~MidpointCircle() {}
};
