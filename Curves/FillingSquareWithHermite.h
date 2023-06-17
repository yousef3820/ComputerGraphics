#ifndef FILLINGSQUAREWITHHERMITE_H_INCLUDED
#define FILLINGSQUAREWITHHERMITE_H_INCLUDED

#include "../Shape.h"

typedef struct {
   int x_left,x_right;
}Table[1000];

struct point {
public :
    int x;
    int y;
    point(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }
};

class FillingSquareWithHermite : public Shape {
protected:
    int xs,ys;
    int L;

    void Draw_Hermite_Curve(HDC hdc,point& p1, point& T1, point& p2, point& T2, COLORREF c);
    void Filling_Square(HDC hdc,int xc,int yc,int length,COLORREF c);

public:
    FillingSquareWithHermite(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions To Fill A Square With Hermite:" << endl;
        cout << "\t1.Click And Hold The Left Button" << endl;
        cout << "\t2.Drag And Release To Calculate The Length Of The Square" << endl;
    }

    void GetLButtonDown(LPARAM lParam);
    void GetLButtonUp(LPARAM lParam);
    void GetRButtonDown(LPARAM lParam);
    void Draw();

    virtual ~FillingSquareWithHermite();
};

#endif // FILLINGSQUAREWITHHERMITE_H_INCLUDED
