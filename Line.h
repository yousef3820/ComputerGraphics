#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include "Shape.h"

class Line : public Shape{
protected:
    void swap(int& x1, int& y1, int& x2, int& y2);
    int round(double num);
    virtual void DrawLine(HDC hdc, COLORREF color) = 0;

public:
    int xs,ys;
    int xe,ye;

    Line(HDC hdc, COLORREF color, bool instruction) : Shape(hdc,color) {}

    Line(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions For Line:" << endl;
        cout << "\t1.Click And Hold the Left Button To Get The Start Points" << endl;
        cout << "\t2.Release The Button To Get The End Points" << endl;
    };

    void GetLButtonDown(LPARAM lParam);
    void GetLButtonUp(LPARAM lParam);
    void GetRButtonDown(LPARAM lParam);
    void Draw();

    virtual ~Line();
};

#endif // LINE_H_INCLUDED
