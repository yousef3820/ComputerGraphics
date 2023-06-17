#include <cmath>
#include <iostream>

using namespace std;

class FillingCircleWithCircles : public Circle {
protected:
    int quarter;

    void FillWithCircles(HDC hdc, int xc, int yc, int R, int quarter, COLORREF color) {
        double dtheta = 1/(double)R;
        double x, y;
        double thetaStart;

        if (quarter==1)
            thetaStart = 0;
        else if (quarter==2)
            thetaStart = 1.57;
        else if (quarter==3)
            thetaStart = 3.14;
        else if (quarter==4)
            thetaStart = 4.71;

        double thetaEnd = thetaStart + 1.57;
        for (int r=1; r<R; r+=3) {
            double thetaTmp = thetaStart;
            while (thetaTmp<thetaEnd) {
                x = r * cos(thetaTmp);
                y = r * sin(thetaTmp);
                SetPixel(hdc,xc+x,yc+y,color);
                thetaTmp+=dtheta;
            }
        }
    }

    void DrawCircleWithCircles(HDC hdc, int xc, int yc, int R, int quarter, COLORREF color) {
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
        FillWithCircles(hdc,xc,yc,R,quarter,color);
    }

    void DrawCircle(HDC hdc, COLORREF color) {
        this->DrawCircleWithCircles(hdc,xc,yc,R,quarter,color);
    }

public:
    FillingCircleWithCircles(HDC hdc, COLORREF color) : Circle(hdc,color) {}

    void GetLButtonUp(LPARAM lParam) {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        R = round(sqrt(pow((x-xc),2) + pow((y-yc),2)));
        cout << "Enter the number of the quarter: ";
        cin >> this->quarter;
        this->Draw();
    }

    virtual ~FillingCircleWithCircles() {}
};
