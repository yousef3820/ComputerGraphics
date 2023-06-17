#ifndef FLOODFILLING_H_INCLUDED
#define FLOODFILLING_H_INCLUDED

#include "../Shape.h"

class FloodFilling : public Shape{
protected:
    int x,y;
    COLORREF bColor;
    virtual void Fill(HDC hdc, int x, int y, COLORREF bgColor, COLORREF bColor) = 0;

public:
    FloodFilling(HDC hdc, COLORREF bgcolor, COLORREF bColor) : Shape(hdc,color) {
        this->bColor=bColor;

        cout << "Instructions For Flood Filling:" << endl;
        cout << "\t1.CLick The Left Button Anywhere Inside The Shape To Fill" << endl;
        cout << "\nPS.Make Sure That This Shape Is Not An Open One" << endl;
    }

    void GetLButtonDown(LPARAM lParam);
    void GetLButtonUp(LPARAM lParam);
    void GetRButtonDown(LPARAM lParam);
    void Draw();

    virtual ~FloodFilling();
};

#endif // FLOODFILLING_H_INCLUDED
