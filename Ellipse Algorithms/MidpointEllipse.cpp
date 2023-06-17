#include <windows.h>

class MidpointEllipse : public Ellipse {
protected:
    void DrawEllipse(HDC hdc, COLORREF color) {
        int x = 0;
        int y = B;
        double d = 0;
        Draw4Points(hdc,xc,yc,0,B,color);
        while(x * B * B < y * A * A)
        {
            d = ((pow(x + 1,2) / pow(A,2)) + (pow(y - 0.5,2) / pow(B,2)) - 1);
            if(d <= 0)
            {
                x++;
            }
            else
            {
                x++;
                y--;
            }
            Draw4Points(hdc,xc,yc,x,y,color);
        }
        x = A;
        y = 0;
        Draw4Points(hdc,xc,yc,A,0,color);
        while(x * B *B > y * A * A)
        {
            double d = (pow(x - 0.5,2) / pow(A,2)) + (pow(y + 1,2) / pow(B,2)) - 1;
            if(d < 0)
            {
                y++;
            }
            else
            {
                y++;
                x--;
            }
            Draw4Points(hdc,xc,yc,x,y,color);
        }
    }

public:
    MidpointEllipse(HDC hdc, COLORREF color) : Ellipse(hdc,color) {}

    virtual ~MidpointEllipse() {}
};
