#include <windows.h>
#include "Line.h"

void Line::swap(int& x1, int& y1, int& x2, int& y2) {
    int tmp = x1;
    x1 = x2;
    x2 = tmp;

    tmp = y1;
    y1 = y2;
    y2 = tmp;
}

int Line::round(double num) {return (int)num+0.5;}

void Line::GetLButtonDown(LPARAM lParam) {
    xs = LOWORD(lParam);
    ys = HIWORD(lParam);
}

void Line::GetLButtonUp(LPARAM lParam) {
    xe = LOWORD(lParam);
    ye = HIWORD(lParam);
    this->Draw();
}

void Line::Draw() {
    this->DrawLine(hdc,color);
}

void Line::GetRButtonDown(LPARAM lParam) {
}

Line::~Line() {}
