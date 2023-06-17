#include <cmath>

class PolarCircle : public Circle {
protected:
    void DrawCircle(HDC hdc, COLORREF color) {
        double dtheta = 1/(double)R;
        double x=R, y=0;
        double theta = 0;
        while (x>y) {
            x = R * cos(theta);
            y = R * sin(theta);
            Draw8Points(hdc,xc,yc,x,y,color);
            theta+=dtheta;
        }
    }

public:
    PolarCircle(HDC hdc, COLORREF color) : Circle(hdc,color) {}

    virtual ~PolarCircle() {}
};
