#ifndef FILLINGRECTANGLEWITHBEZIER_H_INCLUDED
#define FILLINGRECTANGLEWITHBEZIER_H_INCLUDED

#include "../Shape.h"

class FillingRectangleWithBezier : public Shape {
protected:
    int x,y;
    int W,L;
    int BinomialCoeff(int n, int k);
    void Draw_Bezier_Curve(HDC hdc, POINT *pt, int n,COLORREF c);
    void Filling_Rectangle(HDC hdc,int xc,int yc,int width,int length,COLORREF c);

public:
    FillingRectangleWithBezier(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions To Fill A Rectangle With Bezier:" << endl;
        cout << "\t1.Click And Hold The Left Button" << endl;
        cout << "\t2.Drag And Release To Calculate The Width Of The Rectangle" << endl;
        cout << "\t3.CLick The Right Button Below The Previous Edge To Calculate The Length And Fill With Bezier" << endl;
    }

    void GetLButtonDown(LPARAM lParam);
    void GetLButtonUp(LPARAM lParam);
    void GetRButtonDown(LPARAM lParam);
    void Draw();

    virtual ~FillingRectangleWithBezier() {}
};

#endif // FILLINGRECTANGLEWITHBEZIER_H_INCLUDED
