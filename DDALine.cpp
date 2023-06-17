#include "Line.cpp"

class DDALine : public Line {
protected:
    virtual void DrawLine(HDC hdc, COLORREF color) {
        int dx=xe-xs, dy=ye-ys;
        double slope=(double)dy/dx;
        if (abs(slope)<1) {
            if (xs>xe)
                swap(xs,ys,xe,ye);

            int x=xs;
            double y=ys;
            while (x<=xe) {
                SetPixel(hdc,x,round(y),color);
                x++;
                y+=slope;
            }
        }
        else {
            if (ys>ye)
                swap(xs,ys,xe,ye);

            int y=ys;
            double x=xs, islope=1/slope;
            while(y<=ye) {
                SetPixel(hdc,round(x),y,color);
                y++;
                x+=islope;
            }
        }
    }

public:
    void setPoints(int x1, int y1, int x2, int y2) {
        this->xs = x1;
        this->ys = y1;

        this->xe = x2;
        this->ye = y2;
    }

    DDALine(HDC hdc, COLORREF color) : Line(hdc,color) {};

    DDALine(HDC hdc, COLORREF color, bool instruction) : Line(hdc,color,instruction) {};

    virtual ~DDALine() {}
};
