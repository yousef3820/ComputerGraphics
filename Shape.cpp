class Shape {
public:
    virtual void GetLButtonDown(LPARAM lParam);
    virtual void GetLButtonUp(LPARAM lParam);
    virtual void Draw(HDC hdc, COLORREF color);
};
