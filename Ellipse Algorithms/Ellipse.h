#ifndef ELLIPSE_H_INCLUDED
#define ELLIPSE_H_INCLUDED

#include "../Shape.h"

class Ellipse : public Shape{
protected:
    int xc,yc;
    int A, B;
    void Draw4Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color);
    virtual void DrawEllipse(HDC hdc, COLORREF color) = 0;

public:
    Ellipse(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions For Ellipse:" << endl;
        cout << "\t1.Click And Hold The Left Button To Get The Center" << endl;
        cout << "\t2.Release The Left Button To Calculate A" << endl;
        cout << "\t3.Click The Right Button To Calculate B And Draw The Ellipse" << endl;
    };

    void GetLButtonDown(LPARAM lParam);
    void GetLButtonUp(LPARAM lParam);
    void GetRButtonDown(LPARAM lParam);
    void Draw();

    virtual ~Ellipse();
};


#endif // ELLIPSE_H_INCLUDED
