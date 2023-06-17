class BresenhamLine : public Line {
protected:
    void DrawLine(HDC hdc, COLORREF color) {
        int dx=xe-xs, dy=ye-ys;
        double slope = (double)dy/dx;
        if (abs(slope)<1) {
            if (xs>xe) {
                swap(xs,ys,xe,ye);
            }

            int x=xs, y=ys;
            int d = dx - 2*dy;
            int c1 = 2*dx - 2*dy;
            int c2 = -2*dy;
            int c3 = -2*dx - 2*dy;
            SetPixel(hdc,x,y,color);
            while (x<xe) {
                if (dy>0) {
                    if (d<0) {
                        d+=c1;
                        y++;
                    } else
                        d+=c2;
                } else {
                    if (d>0) {
                        d+=c2;
                        y--;
                    } else
                        d+=c3;
                }
                x++;
                SetPixel(hdc,x,y,color);
            }
            SetPixel(hdc,xe,ye,color);
        }
        else {

        }
    }

public:
    BresenhamLine(HDC hdc, COLORREF color) : Line(hdc,color) {};

    virtual ~BresenhamLine() {}
};
