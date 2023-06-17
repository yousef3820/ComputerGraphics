#include "../../Shape.h"

class SquareClippingPoint : public Shape {
protected:
    int xleft, xright, ytop, ybottom;
    int xp, yp;
    void PointClipping(HDC hdc, int x, int y, COLORREF color) {
        if(x>=xleft && x<= xright && y>=ytop && y<=ybottom)
            SetPixel(hdc,x,y,color);
    }

public:
    SquareClippingPoint(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions For Square Point Clipping:" << endl;
        cout << "\t1.Click And Hold The Left Button" << endl;
        cout << "\t2.Drag To The Right and Release The Left Button To Get The Length Of The Square" << endl;
        cout << "\t2.Click The Right Button To Get The Point To Clip" << endl;
    }

    void GetLButtonDown(LPARAM lParam) {
        xleft = LOWORD(lParam);
        ybottom = HIWORD(lParam);
    }

    void GetLButtonUp(LPARAM lParam) {
        xright = LOWORD(lParam);
        ytop = HIWORD(lParam);
        int L = round(sqrt(pow((xleft-xright),2) + pow((ybottom-ytop),2)));
        xleft = xright - L;
        ybottom = ytop + L;
        this->Draw();
    }

    void GetRButtonDown(LPARAM lParam) {
        xp = LOWORD(lParam);
        yp = HIWORD(lParam);
        this->Draw();
    }

    void Draw() {
        this->PointClipping(hdc,xp,yp,color);
    }

    virtual ~SquareClippingPoint() {}
};
