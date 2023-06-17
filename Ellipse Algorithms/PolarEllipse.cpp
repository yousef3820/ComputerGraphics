#include <windows.h>

class PolarEllipse : public Ellipse {
protected:
    void DrawEllipse(HDC hdc, COLORREF color) {
        double x = A;
        double y = 0;
        double dtheta = A>=B ? 1.0 / A : 1.0/B;;
        double theta = 0;
        double cos_theta = cos(dtheta);
        double sin_theta = sin(dtheta);
        Draw4Points(hdc,xc,yc,A,0,color);
        while(x > 0)
        {
            theta +=dtheta;
            double temp =x;
            x = (B * x * cos_theta - A * y * sin_theta) / B;
            y = ( B * temp * sin_theta + A * y * cos_theta) / A;
            Draw4Points(hdc,xc,yc,round(x),round(y),color);
        }
    }

public:
    PolarEllipse(HDC hdc, COLORREF color) : Ellipse(hdc,color) {}

    virtual ~PolarEllipse() {}
};
