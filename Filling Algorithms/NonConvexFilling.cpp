#include <list>

#define MAXENTRIES 600

struct EdgeRec {
    double x;
    double minv;
    int ymax;
    bool operator<(EdgeRec r) { return x<r.x; }
};

typedef list<EdgeRec> EdgeList;

class NonConvexFilling : public ConvexFillingAlgo {
protected:
    EdgeRec InitEdgeRec(point& v1,point& v2) {
        if(v1.y>v2.y)swap(v1,v2);
        EdgeRec rec;
        rec.x=v1.x;
        rec.ymax=v2.y;
        rec.minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
        return rec;
    }

    void InitEdgeTable(vector<point> polygon,int n,EdgeList table[]) {
        point v1=polygon[n-1];
        for(int i=0; i<n; i++) {
            point v2=polygon[i];
            if(v1.y==v2.y) {
                v1=v2;
                continue;
            }
            EdgeRec rec=InitEdgeRec(v1, v2);
            table[v1.y].push_back(rec);
            v1=polygon[i];
        }
    }

    void Fill(HDC hdc,vector<point> polygon,int n,COLORREF c) {
        EdgeList *table=new EdgeList [MAXENTRIES];
        InitEdgeTable(polygon,n,table);
        int y=0;
        while(y<MAXENTRIES && table[y].size()==0)y++;
        if(y==MAXENTRIES)return;
        EdgeList ActiveList=table[y];
        while (ActiveList.size()>0) {
            ActiveList.sort();
            for(EdgeList::iterator it=ActiveList.begin(); it!=ActiveList.end(); it++) {
                int x1=(int)ceil(it->x);
                it++;
                int x2=(int)floor(it->x);
                for(int x=x1; x<=x2; x++)SetPixel(hdc,x,y,c);
            }
            y++;
            EdgeList::iterator it=ActiveList.begin();
            while(it!=ActiveList.end())
                if(y==it->ymax) it=ActiveList.erase(it);
                else it++;
            for(EdgeList::iterator it=ActiveList.begin(); it!=ActiveList.end(); it++)
                it->x+=it->minv;
            ActiveList.insert(ActiveList.end(),table[y].begin(),table[y].end());
        }
        delete[] table;
    }

public:
    NonConvexFilling(HDC hdc, COLORREF color) : ConvexFillingAlgo(hdc,color) {}

    virtual ~NonConvexFilling() {}
};
