#include "Ellipse.h"

void Ellipse::Draw4Points(HDC hdc,int xc,int yc, int a, int b,COLORREF color)
{
    SetPixel(hdc, xc+a, yc+b, color);
    SetPixel(hdc, xc-a, yc+b, color);
    SetPixel(hdc, xc-a, yc-b, color);
    SetPixel(hdc, xc+a, yc-b, color);
}

void Ellipse::GetLButtonDown(LPARAM lParam) {
    xc = LOWORD(lParam);
    yc = HIWORD(lParam);
}

void Ellipse::GetLButtonUp(LPARAM lParam) {
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    A = round(sqrt(pow((x-xc),2) + pow((y-yc),2)));
}

void Ellipse::GetRButtonDown(LPARAM lParam) {
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    B = round(sqrt(pow((x-xc),2) + pow((y-yc),2)));
    Draw();
}

void Ellipse::Draw() {
    this->DrawEllipse(hdc,color);
}

Ellipse::~Ellipse() {}
