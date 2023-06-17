#include "../../Shape.h"

struct Vertex {
    double x,y;
    Vertex(int x1=0,int y1=0) { x=x1; y=y1; }
};

typedef vector<Vertex> VertexList;

typedef bool (*IsInFunc)(Vertex& v,int edge);

bool InLeft(Vertex& v,int edge) { return v.x>=edge; }
bool InRight(Vertex& v,int edge) { return v.x<=edge; }
bool InTop(Vertex& v,int edge) { return v.y>=edge; }
bool InBottom(Vertex& v,int edge) { return v.y<=edge; }

typedef Vertex (*IntersectFunc)(Vertex& v1,Vertex& v2,int edge);

Vertex VIntersect(Vertex& v1,Vertex& v2,int xedge) {
    Vertex res;
    res.x=xedge;
    res.y=v1.y+(xedge-v1.x)*(v2.y-v1.y)/(v2.x-v1.x);
    return res;
}

Vertex HIntersect(Vertex& v1,Vertex& v2,int yedge) {
    Vertex res;
    res.y=yedge;
    res.x=v1.x+(yedge-v1.y)*(v2.x-v1.x)/(v2.y-v1.y);
    return res;
}

class RectangleClippingPolygon : public Shape {
protected:


    int xleft, xright, ytop, ybottom;
    vector<POINT> points;
    int index;

    VertexList ClipWithEdge(VertexList p,int edge,IsInFunc In,IntersectFunc Intersect) {
        VertexList OutList;
        Vertex v1=p[p.size()-1];
        bool v1_in=In(v1,edge);
        for(int i=0;i<(int)p.size();i++) {
            Vertex v2=p[i];
            bool v2_in=In(v2,edge);
            if(!v1_in && v2_in) {
                OutList.push_back(Intersect(v1,v2,edge));
                OutList.push_back(v2);
            }
            else if(v1_in && v2_in)
                OutList.push_back(v2);
            else if(v1_in)
                OutList.push_back(Intersect(v1,v2,edge));
            v1=v2;
            v1_in=v2_in;
        }
        return OutList;
    }

    void PolygonClip(HDC hdc,vector<POINT> p,int n,COLORREF color) {
        VertexList vlist;
        DDALine* line = new DDALine(hdc,color,false);
        for(int i=0;i<n;i++)
            vlist.push_back(Vertex(p[i].x,p[i].y));

        vlist = ClipWithEdge(vlist,xleft,InLeft,VIntersect);
        vlist = ClipWithEdge(vlist,ytop,InTop,HIntersect);
        vlist = ClipWithEdge(vlist,xright,InRight,VIntersect);
        vlist = ClipWithEdge(vlist,ybottom,InBottom,HIntersect);

        Vertex v1=vlist[vlist.size()-1];
        for(int i=0;i<(int)vlist.size();i++) {
            Vertex v2=vlist[i];
            line->setPoints(v1.x,v1.y,v2.x,v2.y);
            line->Draw();
            v1=v2;
        }
        delete line;
        line = NULL;
    }

public:
    RectangleClippingPolygon(HDC hdc, COLORREF color) : Shape(hdc,color) {
        index = 0;
        cout << "Instructions For Rectangle Polygon Clipping:" << endl;
        cout << "\t1.Click The Left Button to get (left,bottom) then again for (right,top)" << endl;
        cout << "\t2.Click anywhere on the window To Get a Point" << endl;
        cout << "\t3.When You Are Done With The Points, Click The Right Button To Do The Clipping" << endl;
    }

    void GetLButtonDown(LPARAM lParam) {
        if (index==0) {
            xleft = LOWORD(lParam);
            ybottom = HIWORD(lParam);
            index++;
           } else if (index==1) {
            xright = LOWORD(lParam);
            ytop = HIWORD(lParam);
            index++;
           } else if (index>1) {
            POINT point;
            point.x = LOWORD(lParam);
            point.y = HIWORD(lParam);
            points.push_back(point);
            index++;
           }
    }

    void GetLButtonUp(LPARAM lParam) {
    }

    void GetRButtonDown(LPARAM lParam) {
        index = 0;
        this->Draw();
        this->points.clear();
    }

    void Draw() {
        this->PolygonClip(hdc,points,points.size(),color);
    }

    virtual ~RectangleClippingPolygon() {}
};
