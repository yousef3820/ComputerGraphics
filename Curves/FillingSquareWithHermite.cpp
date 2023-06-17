#include "FillingSquareWithHermite.h"

void FillingSquareWithHermite::Draw_Hermite_Curve(HDC hdc,point& p1, point& T1, point& p2, point& T2, COLORREF c)
{
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
void FillingSquareWithHermite::Filling_Square(HDC hdc,int xc,int yc,int length,COLORREF c)
{
    double slope =  0.0001;
    double x  = xc - 0.5 * length;
    int y = yc - 0.5 * length;
    int x_end = xc + 0.5 * length;
    while(x <= x_end)
    {
        x++;
        y+=slope;
        point p1(x,y);
        point p2(x,round(y)+length);
        point p3(5,5);
        Draw_Hermite_Curve(hdc,p1,p3,p2,p3,c);
    }

}

void FillingSquareWithHermite::GetLButtonDown(LPARAM lParam) {
    xs = LOWORD(lParam);
    ys = HIWORD(lParam);
}

void FillingSquareWithHermite::GetLButtonUp(LPARAM lParam) {
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    L = round(sqrt(pow((x-xs),2) + pow((y-ys),2)));
    xs += L/2;
    ys += L/2;
    this->Draw();
}

void FillingSquareWithHermite::Draw() {
    this->Filling_Square(hdc,xs,ys,L,color);
}

void FillingSquareWithHermite::GetRButtonDown(LPARAM lParam) {}

FillingSquareWithHermite::~FillingSquareWithHermite() {}
