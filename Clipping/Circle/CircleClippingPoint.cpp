#include "../../Shape.h"

class CircleClippingPoint : public Shape {
protected:
    int xc, yc, R;
    int xp, yp;

    void PointClipping(HDC hdc, int x, int y, COLORREF color) {
        double d = pow((xc-x),2) + pow((yc-y),2) - R*R;
        if (d<=0)
            SetPixel(hdc,x,y,color);
    }

public:
    CircleClippingPoint(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions For Circle Point Clipping:" << endl;
        cout << "\t1.Click The Right Button to get The Center then again To Calculate The Radius" << endl;
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
        int x,y;
        if (index==0) {
            xc = LOWORD(lParam);
            yc = HIWORD(lParam);
            index++;
        }
        else if (index==1) {
            x = LOWORD(lParam);
            y = HIWORD(lParam);
            R = round(sqrt(pow((x-xc),2) + pow((y-yc),2)));
            index++;
        }
    }

    void Draw() {
        this->PointClipping(hdc,xp,yp,color);
    }

    virtual ~CircleClippingPoint() {}
};
