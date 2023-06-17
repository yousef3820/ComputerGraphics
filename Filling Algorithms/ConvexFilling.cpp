#include <windows.h>
#include "ConvexFillingAlgo.cpp"

class ConvexFilling : public ConvexFillingAlgo {
protected:
    void swap(point &p1,point &p2) {
        point t = p1;
        p1 = p2;
        p2 = t;
    }

    void InitTable(Table r) {
        for(int i = 0 ; i < 1000;i++) {
            r[i].x_left = INT_MAX;
            r[i].x_right = INT_MIN;
        }
    }

    void Edge_To_Table(point p1,point p2,Table t) {
        if(p1.y == p2.y)
            return ;
        if(p1.y > p2.y)
            swap(p1,p2);
        double x = p1.x;
        int y = p1.y;
        double slope = (p2.x - p1.x) / double(p2.y - p1.y);
        while(y < p2.y) {
            if(x < t[y].x_left)
                t[y].x_left = (int)ceil(x);
            if(x > t[y].x_right)
                t[y].x_right = (int)floor(x);
            x += slope;
            y++;
        }
    }

    void polygon_to_Table(vector<point> p,int n,Table t) {
        point v1 = p[n - 1];
        for(int i = 0 ; i < n ;i++) {
            point v2 = p[i];
            Edge_To_Table(v1,v2,t);
            v1 = p[i];
        }
    }

    void Table_TO_Screen(HDC hdc,Table t,COLORREF c)
    {
        for(int i = 0 ; i < 1000 ;i++)
            if(t[i].x_left < t[i].x_right)
                for(int j = t[i].x_left ; j <= t[i].x_right;j++)
                    SetPixel(hdc,j,i,c);
    }

    void Fill(HDC hdc,vector<point> p,int n,COLORREF c) {
        Table t;
        InitTable(t);
        polygon_to_Table(p,n,t);
        Table_TO_Screen(hdc,t,c);
    }

public:
    ConvexFilling(HDC hdc, COLORREF color) : ConvexFillingAlgo(hdc,color) {}

    virtual ~ConvexFilling() {}
};
