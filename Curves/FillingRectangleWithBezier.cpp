#include "FillingRectangleWithBezier.h"

int FillingRectangleWithBezier::BinomialCoeff(int n, int k) {
    int res = 1;
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; i++) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

void FillingRectangleWithBezier::Draw_Bezier_Curve(HDC hdc, POINT *pt, int n,COLORREF c) {
    POINT curvePt;
    double t = 0;
    while (t <= 1) {
        curvePt.x = 0;
        curvePt.y = 0;
        for (int i = 0; i < n; i++) {
            double b = BinomialCoeff(n - 1, i) * pow(t, i) * pow(1 - t, n - 1 - i);
            curvePt.x += b * pt[i].x;
            curvePt.y += b * pt[i].y;
        }
        SetPixel(hdc, curvePt.x, curvePt.y,c);
        t += 0.001;
    }
}

void FillingRectangleWithBezier::Filling_Rectangle(HDC hdc,int xc,int yc,int width,int length,COLORREF c) {
    double slope =  0.0001;
    double x  = xc - 0.5 * width;
    int y = yc - 0.5 * length;
    int y_end = yc + 0.5 * length;
    POINT p[2];
    while(y <= y_end) {
        x +=slope;
        y++;
        p[0].x = round(x);
        p[0].y = y;
        p[1].x = round(x) + width;
        p[1].y = y;
        Draw_Bezier_Curve(hdc,p,2,c);
    }
}


void FillingRectangleWithBezier::GetLButtonDown(LPARAM lParam) {
    x = LOWORD(lParam);
    y = HIWORD(lParam);
}

void FillingRectangleWithBezier::GetLButtonUp(LPARAM lParam) {
    int x2 = LOWORD(lParam);
    int y2 = HIWORD(lParam);
    W = round(sqrt(pow((x2-x),2) + pow((y2-y),2)));
}

void FillingRectangleWithBezier::GetRButtonDown(LPARAM lParam) {
    int x3 = LOWORD(lParam);
    int y3 = HIWORD(lParam);
    L = round(sqrt(pow((x3-x),2) + pow((y3-y),2)));
    x += W/2;
    y += L/2;
    this->Draw();
}

void FillingRectangleWithBezier::Draw() {
    this->Filling_Rectangle(hdc,x,y,W,L,color);
}
