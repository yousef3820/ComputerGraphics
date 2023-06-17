#include <cmath>

class IterativePolarCircle : public Circle {
protected:
    void DrawCircle(HDC hdc, COLORREF color) {
        double dtheta = 1/(double)R;
        double cos_dtheta=cos(dtheta), sin_dtheta=sin(dtheta);
        double x=R, y=0;
        Draw8Points(hdc,xc,yc,x,y,color);
        while (x>y) {
            double x_prev = x;
            x = x_prev*cos_dtheta - y*sin_dtheta;
            y = x_prev*sin_dtheta + y*cos_dtheta;
            Draw8Points(hdc,xc,yc,x,y,color);
        }
    }

public:
    IterativePolarCircle(HDC hdc, COLORREF color) : Circle(hdc,color) {}

    virtual ~IterativePolarCircle() {}
};
