#ifndef CONVEXFILLINGALGO_H_INCLUDED
#define CONVEXFILLINGALGO_H_INCLUDED

#include "../Shape.h"

class ConvexFillingAlgo : public Shape{
protected:
    vector<point> points;
    COLORREF bColor;
    virtual void Fill(HDC hdc, vector<point> p, int n, COLORREF color) = 0;

public:
    ConvexFillingAlgo(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions For Convex Filling Algorithms:" << endl;
        cout << "\t1.Click The Left Button Anywhere On The Window To Get a Point" << endl;
        cout << "\t2.When You Are Done With The Points, Click The Right Button To Do The Filling" << endl;
    }

    void GetLButtonDown(LPARAM lParam);
    void GetLButtonUp(LPARAM lParam);
    void GetRButtonDown(LPARAM lParam);
    void Draw();

    virtual ~ConvexFillingAlgo();
};

#endif // CONVEXFILLINGALGO_H_INCLUDED
