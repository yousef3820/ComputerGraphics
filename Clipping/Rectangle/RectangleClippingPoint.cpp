#include "../../Shape.h"

class RectangleClippingPoint : public Shape {
protected:
    int xleft, xright, ytop, ybottom;
    int xp, yp;
    void PointClipping(HDC hdc, int x, int y, COLORREF color) {
        if(x>=xleft && x<= xright && y>=ytop && y<=ybottom)
            SetPixel(hdc,x,y,color);
    }

public:
    RectangleClippingPoint(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions For Rectangle Point Clipping:" << endl;
        cout << "\t1.Click The Right Button to get (left,bottom) then again for (right,top)" << endl;
        cout << "\t2.Click The Left Button To Get The Point To Clip" << endl;
    }

    void GetLButtonDown(LPARAM lParam) {
        xp = LOWORD(lParam);
        yp = HIWORD(lParam);
    }

    void GetLButtonUp(LPARAM lParam) {
        this->Draw();
    }

    void GetRButtonDown(LPARAM lParam) {
        static int index = 0;
        if (index==0) {
            xleft = LOWORD(lParam);
            ybottom = HIWORD(lParam);
            index++;
        } else if (index==1) {
            xright = LOWORD(lParam);
            ytop = HIWORD(lParam);
            index++;
        }
    }

    void Draw() {
        this->PointClipping(hdc,xp,yp,color);
    }

    virtual ~RectangleClippingPoint() {}
};
