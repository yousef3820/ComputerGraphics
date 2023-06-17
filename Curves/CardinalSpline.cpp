#include "CardinalSpline.h"

void CardinalSpline::Draw_Hermite_Curve(HDC hdc,point& p1, point& T1, point& p2, point& T2, COLORREF c) {
	double a0 = p1.x;
	double a1 = T1.x;
    double a2 = -3 * p1.x - 2 * T1.x + 3 * p2.x - T2.x;
    double a3 = 2 * p1.x + T1.x - 2 * p2.x + T2.x;
	double b0 = p1.y;
	double b1 = T1.y;
    double b2 = -3 * p1.y - 2 * T1.y + 3 * p2.y - T2.y;
    double b3 = 2 * p1.y + T1.y - 2 * p2.y + T2.y;
	for (double t = 0; t <= 1; t += 0.001)
	{
		double t2 = t*t,
		 t3 = t2*t;
		double x = a0 + a1*t + a2*t2 + a3*t3;
		double y = b0 + b1*t + b2*t2 + b3*t3;
		SetPixel(hdc, round(x), round(y), c);
	}
}

void CardinalSpline::Draw_Cardinal_Spline(HDC hdc,vector<point> P,int n,int C,COLORREF c) {
    point T[n];
    for(int i = 1 ;i < n - 1 ;i++) {
        T[i].x = C * (P[i + 1].x - P[i].x);
        T[i].y = C * (P[i + 1].y - P[i].y);
    }

    T[0] = T[1];
    T[n - 1] = T[n - 2];
    for(int i = 0;i < n - 1; i++)
        Draw_Hermite_Curve(hdc,P[i],T[i],P[i+1],T[i+1],c);
}

void CardinalSpline::GetLButtonDown(LPARAM lParam) {
    point point;
    point.x = LOWORD(lParam);
    point.y = HIWORD(lParam);
    this->points.push_back(point);
}

void CardinalSpline::GetLButtonUp(LPARAM lParam) {}

void CardinalSpline::Draw() {
    this->Draw_Cardinal_Spline(hdc,this->points,this->points.size(),3,color);
}

void CardinalSpline::GetRButtonDown(LPARAM lParam) {
    this->Draw();
    this->points.clear();
}

CardinalSpline::~CardinalSpline() {}
