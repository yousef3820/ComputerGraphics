#ifndef CARDINALSPLINE_H_INCLUDED
#define CARDINALSPLINE_H_INCLUDED

#include "../Shape.h"

class CardinalSpline : public Shape {
protected:
    vector<point> points;
    void Draw_Hermite_Curve(HDC hdc,point& p1, point& T1, point& p2, point& T2, COLORREF c);
    void Draw_Cardinal_Spline(HDC hdc,vector<point> P,int n,int C,COLORREF c);

public:
    CardinalSpline(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions For Cardinal Spline:" << endl;
        cout << "\t1.Click The Left Button Anywhere On The Window To Get a Point" << endl;
        cout << "\t2.When You Are Done With The Points, Click The Right Button Draw The Curve" << endl;
    }

    void GetLButtonDown(LPARAM lParam);
    void GetLButtonUp(LPARAM lParam);
    void GetRButtonDown(LPARAM lParam);
    void Draw();

    virtual ~CardinalSpline();
};

#endif // CARDINALSPLINE_H_INCLUDED
