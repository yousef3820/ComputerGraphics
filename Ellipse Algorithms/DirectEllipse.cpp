#include <windows.h>
#include "Ellipse.cpp"

class DirectEllipse : public Ellipse {
protected:
    void DrawEllipse(HDC hdc, COLORREF color) {
        double x = A;
        double y = 0;
        double dtheta = A>=B ? 1.0 / A : 1.0/B;
        double theta = 0;
        Draw4Points(hdc,xc,yc,A,0,color);
        while(theta < (6.28 / 4))
        {
            theta +=dtheta;
            x = A * cos(theta);
            y = B * sin(theta);
            Draw4Points(hdc,xc,yc,round(x),round(y),color);
        }
    }

public:
    DirectEllipse(HDC hdc, COLORREF color) : Ellipse(hdc,color) {}

    virtual ~DirectEllipse() {}
};
