#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <Windows.h>
#include <iostream>

using namespace std;

class Shape {
protected:
    COLORREF color;
    HDC hdc;
public:
    virtual ~Shape() {}
    Shape(HDC hdc, COLORREF color) {this->hdc=hdc; this->color=color;}

    virtual void ChangeCOlor(COLORREF color) {this->color=color;}
    virtual void GetLButtonDown(LPARAM lParam) = 0;
    virtual void GetLButtonUp(LPARAM lParam) = 0;
    virtual void GetRButtonDown(LPARAM lParam) = 0;
    virtual void Draw() = 0;
};

#endif // SHAPE_H_INCLUDED
