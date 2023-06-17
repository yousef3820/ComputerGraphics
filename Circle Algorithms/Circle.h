#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "../Shape.h"

class Circle : public Shape{
protected:
    int xc,yc;
    int R;
    void Draw8Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color);
    virtual void DrawCircle(HDC hdc, COLORREF color) = 0;

public:
    Circle(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions For Circle:" << endl;
        cout << "\t1.Click And Hold Left Button To Get The Center" << endl;
        cout << "\t2.Release The Button To Calculate The Radius And Draw The Circle" << endl;
    };

    void GetLButtonDown(LPARAM lParam);
    virtual void GetLButtonUp(LPARAM lParam);
    void GetRButtonDown(LPARAM lParam);
    void Draw();

    virtual ~Circle();
};

#endif // CIRCLE_H_INCLUDED
