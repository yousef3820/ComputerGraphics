#include <cmath>
#include <iostream>

using namespace std;

void swap(int& x1, int& y1, int& x2, int& y2) {
    int tmp = x1;
    x1 = x2;
    x2 = tmp;

    tmp = y1;
    y1 = y2;
    y2 = tmp;
}

class FillingCircleWithLines : public Circle {
protected:
    int quarter;
    void DDALine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color) {
        int dx=x2-x1, dy=y2-y1;
        double slope=(double)dy/dx;
        if (abs(slope)<1) {
            if (x1>x2)
                swap(x1,y1,x2,y2);

            int x=x1;
            double y=y1;
            while (x<=x2) {
                SetPixel(hdc,x,round(y),color);
                x++;
                y+=slope;
            }
        }
        else {
            if (y1>y2)
                swap(x1,y1,x2,y2);

            int y=y1;
            double x=x1, islope=1/slope;
            while(y<=y2) {
                SetPixel(hdc,round(x),y,color);
                y++;
                x+=islope;
            }
        }
    }

    void Draw8PointsWithQuarterLines(HDC hdc, int xc, int yc, int a, int b, int quarter, COLORREF color) {
        SetPixel(hdc,xc+a,yc+b,color);
        SetPixel(hdc,xc+b,yc+a,color);
        if (quarter==1) {
            DDALine(hdc,xc,yc,xc+a,yc+b,color);
            DDALine(hdc,xc,yc,xc+b,yc+a,color);
        }


        SetPixel(hdc,xc-a,yc+b,color);
        SetPixel(hdc,xc-b,yc+a,color);
        if (quarter==2) {
            DDALine(hdc,xc,yc,xc-a,yc+b,color);
            DDALine(hdc,xc,yc,xc-b,yc+a,color);
        }

        SetPixel(hdc,xc-a,yc-b,color);
        SetPixel(hdc,xc-b,yc-a,color);
        if (quarter==3) {
            DDALine(hdc,xc,yc,xc-a,yc-b,color);
            DDALine(hdc,xc,yc,xc-b,yc-a,color);
        }

        SetPixel(hdc,xc+a,yc-b,color);
        SetPixel(hdc,xc+b,yc-a,color);
        if (quarter==4) {
            DDALine(hdc,xc,yc,xc+a,yc-b,color);
            DDALine(hdc,xc,yc,xc+b,yc-a,color);
        }
    }

    void DrawCircleWithLines(HDC hdc, int xc, int yc, int R, int quarter, COLORREF color) {
        int x=0, y=R;
        int d = 1-R;
        int c1=3, c2=5-2*R;

        Draw8PointsWithQuarterLines(hdc,xc,yc,x,y,quarter,color);
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

            Draw8PointsWithQuarterLines(hdc,xc,yc,x,y,quarter,color);
        }
    }

    void DrawCircle(HDC hdc, COLORREF color) {
        this->DrawCircleWithLines(hdc,xc,yc,R,quarter,color);
    }

public:
    FillingCircleWithLines(HDC hdc, COLORREF color) : Circle(hdc,color) {}

    void GetLButtonUp(LPARAM lParam) {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        R = round(sqrt(pow((x-xc),2) + pow((y-yc),2)));
        cout << "Enter the number of the quarter: ";
        cin >> this->quarter;
        this->Draw();
    }

    virtual ~FillingCircleWithLines() {}
};
