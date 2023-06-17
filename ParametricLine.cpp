class ParametricLine : public Line {
protected:
    virtual void DrawLine(HDC hdc, COLORREF color) {
        int dx = xe - xs;
        int dy = ye - ys;
        double mal = dy / double(dx);
        if(abs(dx) > abs(dy)) {
            if(xs > xe)
                swap(xs,ys,xe,ye);

            int x = xs;
            while(x <= xe) {
                double y = mal * (x - xs) + ys;
                SetPixel(hdc,x,round(y),color);
                x++;
            }
        }
        else {
            if(ys > ye)
                swap(xs,ys,xe,ye);

            int y = ys;
            while(y <= ye) {
                double x = 1 / mal * (y - ys) + xs;
                SetPixel(hdc,round(x),y,color);
                y++;
            }
        }
    }

public:
    ParametricLine(HDC hdc, COLORREF color) : Line(hdc,color) {};

    virtual ~ParametricLine() {}
};
