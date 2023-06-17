#include "../../Shape.h"

union OutCode {
    unsigned All:4;
    struct{unsigned left:1,top:1,right:1,bottom:1;};
};

class RectangleClippingLine : public Shape {
protected:
    int xleft, xright, ytop, ybottom;
    int xs, ys, xe, ye;

    OutCode GetOutCode(double x,double y) {
        OutCode out;
        out.All=0;
        if(x<xleft)
            out.left=1;
        else if(x>xright)
            out.right=1;

        if(y<ytop)
            out.top=1;
        else if(y>ybottom)
            out.bottom=1;

        return out;
    }

    void VIntersect(double x1,double y1,double x2,double y2,int x,double *xi,double *yi) {
        *xi = x;
        *yi = y1+(x-x1)*(y2-y1)/(x2-x1);
    }

    void HIntersect(double x1,double y1,double x2,double y2,int y,double *xi,double *yi) {
        *yi = y;
        *xi = x1+(y-y1)*(x2-x1)/(y2-y1);
    }

    void LineClipping(HDC hdc,int xs,int ys,int xe,int ye, COLORREF color) {
        double x1=xs,y1=ys,x2=xe,y2=ye;
        OutCode out1=GetOutCode(x1,y1);
        OutCode out2=GetOutCode(x2,y2);

        while((out1.All || out2.All) && !(out1.All & out2.All)) {
            double xi,yi;
            if(out1.All) {
                if(out1.left)VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
                else if(out1.top)HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
                else if(out1.right)VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
                else HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
                x1=xi;
                y1=yi;
                out1=GetOutCode(x1,y1);
            }

            else {
                if(out2.left)VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
                else if(out2.top)HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
                else if(out2.right)VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
                else HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
                x2=xi;
                y2=yi;
                out2=GetOutCode(x2,y2);
            }
        }

        if(!out1.All && !out2.All) {
            DDALine* line = new DDALine(hdc,color,false);
            line->setPoints(x1,y1,x2,y2);
            line->Draw();
            delete line;
            line = NULL;
        }
    }

public:
    RectangleClippingLine(HDC hdc, COLORREF color) : Shape(hdc,color) {
        cout << "Instructions For Rectangle Line Clipping:" << endl;
        cout << "\t1.Click The Right Button to get (left,bottom) then again for (right,top)" << endl;
        cout << "\t2.Click And Hold The Left Button To Get The Start Points Of The Line" << endl;
        cout << "\t3.Release The Left Button To Get The End Points And Clip The Line" << endl;
    }

    void GetLButtonDown(LPARAM lParam) {
        xs = LOWORD(lParam);
        ys = HIWORD(lParam);
    }

    void GetLButtonUp(LPARAM lParam) {
        xe = LOWORD(lParam);
        ye = HIWORD(lParam);
        this->Draw();
    }

    void GetRButtonDown(LPARAM lParam) {
        static int index = 0;
        if (index==0) {
            xleft = LOWORD(lParam);
            ybottom = HIWORD(lParam);
            index++;
        } else if (index==1) {
            xright = LOWORD(lParam);
            ytop = HIWORD(lParam);
            index++;
        }
    }

    void Draw() {
        this->LineClipping(hdc,xs,ys,xe,ye,color);
    }

    virtual ~RectangleClippingLine() {}
};
