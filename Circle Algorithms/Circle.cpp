#include "Circle.h"

void Circle::Draw8Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color) {
    SetPixel(hdc,xc+a,yc+b,color);
    SetPixel(hdc,xc-a,yc+b,color);
    SetPixel(hdc,xc-a,yc-b,color);
    SetPixel(hdc,xc+a,yc-b,color);

    SetPixel(hdc,xc+b,yc+a,color);
    SetPixel(hdc,xc-b,yc+a,color);
    SetPixel(hdc,xc-b,yc-a,color);
    SetPixel(hdc,xc+b,yc-a,color);
}

void Circle::GetLButtonDown(LPARAM lParam) {
    xc = LOWORD(lParam);
    yc = HIWORD(lParam);
}

void Circle::GetLButtonUp(LPARAM lParam) {
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    R = round(sqrt(pow((x-xc),2) + pow((y-yc),2)));
    this->Draw();
}

void Circle::Draw() {
    this->DrawCircle(hdc,color);
}

void Circle::GetRButtonDown(LPARAM lParam) {}

Circle::~Circle() {}

