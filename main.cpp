#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Shape.h"

#include "DDALine.cpp"
#include "BresenhamLine.cpp"
#include "ParametricLine.cpp"

#include "Circle Algorithms/DirectCircle.cpp"
#include "Circle Algorithms/PolarCircle.cpp"
#include "Circle Algorithms/IterativePolarCircle.cpp"
#include "Circle Algorithms/MidpointCircle.cpp"
#include "Circle Algorithms/AdvancedMidpointCircle.cpp"
#include "Circle Algorithms/FillingCircleWithLines.cpp"
#include "Circle Algorithms/FillingCircleWithCircles.cpp"

#include "Ellipse Algorithms/DirectEllipse.cpp"
#include "Ellipse Algorithms/PolarEllipse.cpp"
#include "Ellipse Algorithms/MidpointEllipse.cpp"

#include "Curves/FillingSquareWithHermite.cpp"
#include "Curves/FillingRectangleWithBezier.cpp"
#include "Curves/CardinalSpline.cpp"

#include "Filling Algorithms/RecursiveFloodFilling.cpp"
#include "Filling Algorithms/NonRecursiveFloodFilling.cpp"
#include "Filling Algorithms/ConvexFilling.cpp"
#include "Filling Algorithms/NonConvexFilling.cpp"

#include "Clipping/Rectangle/RectangleClippingPoint.cpp"
#include "Clipping/Rectangle/RectangleClippingLine.cpp"
#include "Clipping/Rectangle/RectangleClippingPolygon.cpp"

#include "Clipping/Square/SquareClippingPoint.cpp"
#include "Clipping/Square/SquareClippingLine.cpp"

#include "Clipping/Circle/CircleClippingPoint.cpp"
#include "Clipping/Circle/CircleClippingLine.cpp"

#include "Transformation.cpp"

using namespace std;

#define W_BGWHITE 1
#define W_CURSORSHAPE 2

#define E_CLEAR 11
#define E_SAVE 12
#define E_LOAD 13

#define DL_DDA 21
#define DL_BRESENHAM 22
#define DL_PARAMETRIC 23

#define DC_Direct 31
#define DC_POLAR 32
#define DC_ITERATIVE_POLAR 33
#define DC_MIDPOINT 34
#define DC_ADVANCED_MIDPONT 35
#define DC_QUARTER_LINE 36
#define DC_QUARTER_CIRCLE 37

#define DE_Direct 41
#define DE_POLAR 42
#define DE_MIDPOINT 43

#define DH_SQUARE_HERMITE 51
#define DB_RECTANGLE_BEZIER 52
#define DS_SPLINE 53

#define DF_RECURSIVE_FLOOD 61
#define DF_NON_RECURSIVE_FLOOD 62
#define DF_CONVEX 63
#define DF_NON_CONVEX 64


#define DC_RECTANGLE_POINT 71
#define DC_RECTANGLE_LINE 72
#define DC_RECTANGLE_POLYGON 73

#define DC_SQUARE_POINT 81
#define DC_SQUARE_LINE 82

#define DC_CIRCLE_POINT 91
#define DC_CIRCLE_LINE 92

#define T_TRANSLATE 101
#define T_SCALE 102

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

HMENU CreateWindowMenu() {
    // Create Window Menu
    HMENU hWinMenu = CreatePopupMenu();
    AppendMenu(hWinMenu, MF_STRING, W_BGWHITE, "Change Bg Color");
    AppendMenu(hWinMenu, MF_STRING, W_CURSORSHAPE, "Change Cursor");
    return hWinMenu;
}

HMENU CreateEditMenu() {
    // Create Edit Menu
    HMENU hEditMenu = CreatePopupMenu();
    AppendMenu(hEditMenu, MF_STRING, E_CLEAR, "Clear");
    AppendMenu(hEditMenu, MF_STRING, E_SAVE, "Save");
    AppendMenu(hEditMenu, MF_STRING, E_LOAD, "Load");
    return hEditMenu;
}

HMENU CreateDrawMenu() {
    // Create Draw Menu
    HMENU hDrawMenu = CreatePopupMenu();

    HMENU hLineMenu = CreatePopupMenu();
    AppendMenu(hLineMenu, MF_STRING, DL_DDA, "DDA");
    AppendMenu(hLineMenu, MF_STRING, DL_BRESENHAM, "Bresenham");
    AppendMenu(hLineMenu, MF_STRING, DL_PARAMETRIC, "Parametric");
    AppendMenu(hDrawMenu, MF_POPUP, (UINT_PTR)hLineMenu, "Line");

    HMENU hCircleMenu = CreatePopupMenu();
    AppendMenu(hCircleMenu, MF_STRING, DC_Direct, "Direct");
    AppendMenu(hCircleMenu, MF_STRING, DC_POLAR, "Polar");
    AppendMenu(hCircleMenu, MF_STRING, DC_ITERATIVE_POLAR, "Iterative Polar");
    AppendMenu(hCircleMenu, MF_STRING, DC_MIDPOINT, "Midpoint");
    AppendMenu(hCircleMenu, MF_STRING, DC_ADVANCED_MIDPONT, "Advanced Midpoint");
    HMENU hFillCircleMenu = CreatePopupMenu();
    AppendMenu(hFillCircleMenu, MF_STRING, DC_QUARTER_LINE, "Lines");
    AppendMenu(hFillCircleMenu, MF_STRING, DC_QUARTER_CIRCLE, "Circles");
    AppendMenu(hCircleMenu, MF_POPUP, (UINT_PTR)hFillCircleMenu, "Fill Quarter");
    AppendMenu(hDrawMenu, MF_POPUP, (UINT_PTR)hCircleMenu, "Circle");

    HMENU hEllipseMenu = CreatePopupMenu();
    AppendMenu(hEllipseMenu, MF_STRING, DE_Direct, "Direct");
    AppendMenu(hEllipseMenu, MF_STRING, DE_POLAR, "Polar");
    AppendMenu(hEllipseMenu, MF_STRING, DE_MIDPOINT, "Midpoint");
    AppendMenu(hDrawMenu, MF_POPUP, (UINT_PTR)hEllipseMenu, "Ellipse");

    HMENU hCurvesMenu = CreatePopupMenu();
    AppendMenu(hCurvesMenu, MF_STRING, DH_SQUARE_HERMITE, "Square With Hermite");
    AppendMenu(hCurvesMenu, MF_STRING, DB_RECTANGLE_BEZIER, "Rectangle With Bezier");
    AppendMenu(hCurvesMenu, MF_STRING, DS_SPLINE, "Cardinal Spline");
    AppendMenu(hDrawMenu, MF_POPUP, (UINT_PTR)hCurvesMenu, "Curves");

    HMENU hFillingMenu = CreatePopupMenu();
    HMENU hFloodFillingMenu = CreatePopupMenu();
    AppendMenu(hFloodFillingMenu, MF_STRING, DF_RECURSIVE_FLOOD, "Recursive");
    AppendMenu(hFloodFillingMenu, MF_STRING, DF_NON_RECURSIVE_FLOOD, "Non Recursive");
    AppendMenu(hFillingMenu, MF_POPUP, (UINT_PTR)hFloodFillingMenu, "Flood");
    HMENU hConvexFillingMenu = CreatePopupMenu();
    AppendMenu(hConvexFillingMenu, MF_STRING, DF_CONVEX, "Convex");
    AppendMenu(hConvexFillingMenu, MF_STRING, DF_NON_CONVEX, "Non Convex");
    AppendMenu(hFillingMenu, MF_POPUP, (UINT_PTR)hConvexFillingMenu, "Convex");
    AppendMenu(hDrawMenu, MF_POPUP, (UINT_PTR)hFillingMenu, "Filling");

    HMENU hClippingMenu = CreatePopupMenu();
    HMENU hRectangleMenu = CreatePopupMenu();
    AppendMenu(hRectangleMenu, MF_STRING, DC_RECTANGLE_POINT, "Point");
    AppendMenu(hRectangleMenu, MF_STRING, DC_RECTANGLE_LINE, "Line");
    AppendMenu(hRectangleMenu, MF_STRING, DC_RECTANGLE_POLYGON, "Polygon");
    AppendMenu(hClippingMenu, MF_POPUP, (UINT_PTR)hRectangleMenu, "Rectangle");
    HMENU hSquareMenu = CreatePopupMenu();
    AppendMenu(hSquareMenu, MF_STRING, DC_SQUARE_POINT, "Point");
    AppendMenu(hSquareMenu, MF_STRING, DC_SQUARE_LINE, "Line");
    AppendMenu(hClippingMenu, MF_POPUP, (UINT_PTR)hSquareMenu, "Square");
    HMENU hCircleClippingMenu = CreatePopupMenu();
    AppendMenu(hCircleClippingMenu, MF_STRING, DC_CIRCLE_POINT, "Point");
    AppendMenu(hCircleClippingMenu, MF_STRING, DC_CIRCLE_LINE, "Line");
    AppendMenu(hClippingMenu, MF_POPUP, (UINT_PTR)hCircleClippingMenu, "Circle");

    AppendMenu(hDrawMenu, MF_POPUP, (UINT_PTR)hClippingMenu, "Clipping");

    return hDrawMenu;
}

HMENU CreateTransformationMenu() {
    // Create Transformation Menu
    HMENU hTransformationMenu = CreatePopupMenu();
    AppendMenu(hTransformationMenu, MF_STRING, T_TRANSLATE, "Translate");
    AppendMenu(hTransformationMenu, MF_STRING, T_SCALE, "Scale");
    return hTransformationMenu;
}

HMENU CreateDropDownMenu() {
    // Create menu
    HMENU hMenu = CreateMenu();
    // Create Window Sub Menu
    HMENU hWinMenu = CreateWindowMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hWinMenu, "Window");
    // Create Edit Sub Menu
    HMENU hEditMenu = CreateEditMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, "Edit");
    // Create Draw Sub Menu
    HMENU hDrawMenu = CreateDrawMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hDrawMenu, "Draw");
    // Create Transformation Sub Menu
    HMENU hTransformationMenu = CreateTransformationMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hTransformationMenu, "Transform");
    // Create Color Sub Menu
    HMENU hColorMenu = CreatePopupMenu();
    AppendMenu(hColorMenu, MF_STRING, 1001, "Change Color");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hColorMenu, "Color");

    return hMenu;
}

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    // Create menu
    HMENU hMenu = CreateDropDownMenu();
    SetMenu(hwnd, hMenu);


    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

void ChangeBg(HWND hwnd, bool isWhite)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    if (isWhite)
        hBrush = (HBRUSH) COLOR_BACKGROUND;
    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
    InvalidateRect(hwnd, NULL, TRUE);
}

void ChangeMouseShape(bool isCursorChanged) {
    // Set the cursor shape to a hand cursor
    if (!isCursorChanged)
        SetClassLongPtr(GetActiveWindow(), GCLP_HCURSOR, (LONG_PTR)LoadCursor(NULL, IDC_HAND));
    else
        SetClassLongPtr(GetActiveWindow(), GCLP_HCURSOR, (LONG_PTR)LoadCursor(NULL, IDC_ARROW));
}

void HandleWindowMenu(HWND hwnd, WPARAM wParam) {
    int itemId = LOWORD(wParam);
    static bool isWhite = false;
    static bool isCursorChanged = false;

    switch(itemId) {
        case W_BGWHITE:
            ChangeBg(hwnd,isWhite);
            isWhite = !isWhite;
            break;
        case W_CURSORSHAPE:
            ChangeMouseShape(isCursorChanged);
            isCursorChanged = !isCursorChanged;
            break;
    }
}

void ClearScreen(HWND hwnd) {
    HDC hdc = GetDC(hwnd);
    RECT rect;
    GetClientRect(hwnd, &rect);
    HBRUSH hBrush = (HBRUSH) COLOR_BACKGROUND; // Set the color to transparent
    FillRect(hdc, &rect, hBrush); // Fill the client area with the brush
    DeleteObject(hBrush);
    ReleaseDC(hwnd, hdc);
}

void SaveFile(HWND hwnd) {
    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Bin Files (*.bin)\0*.bin\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "bin";

    if (GetSaveFileName(&ofn))
    {
        RECT rect;
        GetClientRect(hwnd, &rect); // Retrieve the client area of the window

        int width = rect.right - rect.left; // Calculate the width
        int height = rect.bottom - rect.top; // Calculate the height

        // Create a memory device context and a compatible bitmap
        HDC hdcScreen = GetDC(hwnd);
        HDC hdcMem = CreateCompatibleDC(hdcScreen);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
        SelectObject(hdcMem, hBitmap);

        // Copy the window contents to the bitmap
        BitBlt(hdcMem, 0, 0, width, height, hdcScreen, rect.left, rect.top, SRCCOPY);

        // Save the color data to a file
        std::ofstream outFile(ofn.lpstrFile, std::ios::out | std::ios::binary);
        outFile.write(reinterpret_cast<char*>(&width), sizeof(int));
        outFile.write(reinterpret_cast<char*>(&height), sizeof(int));
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                COLORREF color = GetPixel(hdcMem, x, y);
                outFile.write(reinterpret_cast<char*>(&color), sizeof(COLORREF));
            }
        }
        outFile.close();

        // Clean up resources
        DeleteObject(hBitmap);
        DeleteDC(hdcMem);
        ReleaseDC(NULL, hdcScreen);
    }
}

void LoadFile(HWND hwnd) {
    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Bin Files (*.bin)\0*.bin\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "bin";

    if (GetOpenFileName(&ofn))
    {
            // Read the color data from the file
        std::ifstream inFile(ofn.lpstrFile, std::ios::in | std::ios::binary);
        if (!inFile) {
            std::cerr << "Error opening file" << std::endl;
            return;
        }
        int width, height;
        inFile.read(reinterpret_cast<char*>(&width), sizeof(int));
        inFile.read(reinterpret_cast<char*>(&height), sizeof(int));
        std::vector<COLORREF> colors(width * height);
        inFile.read(reinterpret_cast<char*>(colors.data()), colors.size() * sizeof(COLORREF));
        inFile.close();

        // Display the color data in the window
        HDC hdcScreen = GetDC(hwnd);
        HDC hdcMem = CreateCompatibleDC(hdcScreen);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
        SelectObject(hdcMem, hBitmap);

        // Copy the color data to the bitmap
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                COLORREF color = colors[y * width + x];
                SetPixel(hdcMem, x, y, color);
            }
        }

        // Copy the bitmap to the window
        RECT rect;
        GetClientRect(hwnd, &rect);
        BitBlt(hdcScreen, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdcMem, 0, 0, SRCCOPY);

        // Clean up resources
        DeleteObject(hBitmap);
        DeleteDC(hdcMem);
        ReleaseDC(NULL, hdcScreen);
    }
}


void HandleEditMenu(WPARAM wParam, HWND hwnd) {
    int itemId = LOWORD(wParam);

    switch(itemId) {
        case E_CLEAR:
            ClearScreen(hwnd);
            break;
        case E_SAVE:
            SaveFile(hwnd);
            break;
        case E_LOAD:
            LoadFile(hwnd);
            break;
    }
}

COLORREF ChooseColor(HWND hWnd, COLORREF crInitial) {
    CHOOSECOLOR cc = { 0 };
    static COLORREF acrCustClr[16];
    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.hwndOwner = hWnd;
    cc.rgbResult = crInitial;
    cc.lpCustColors = acrCustClr;
    cc.Flags = CC_FULLOPEN | CC_RGBINIT;
    if (ChooseColor(&cc))
    {
        return cc.rgbResult;
    }
    return crInitial;
}

Shape* HandleDrawMenu(HWND hwnd, WPARAM wParam, COLORREF color) {
    int itemId = LOWORD(wParam);
    Shape* shape = NULL;
    HDC hdc = GetDC(hwnd);

    switch(itemId) {
        case DL_DDA:
            shape = new DDALine(hdc,color);
            break;
        case DL_BRESENHAM:
            shape = new BresenhamLine(hdc,color);
            break;
        case DL_PARAMETRIC:
            shape = new ParametricLine(hdc,color);
            break;

        case DC_Direct:
            shape = new DirectCircle(hdc,color);
            break;
        case DC_POLAR:
            shape = new PolarCircle(hdc,color);
            break;
        case DC_ITERATIVE_POLAR:
            shape = new IterativePolarCircle(hdc,color);
            break;
        case DC_MIDPOINT:
            shape = new MidpointCircle(hdc,color);
            break;
        case DC_ADVANCED_MIDPONT:
            shape = new AdvancedMidpointCircle(hdc,color);
            break;
        case DC_QUARTER_LINE:
            shape = new FillingCircleWithLines(hdc,color);
            break;
        case DC_QUARTER_CIRCLE:
            shape = new FillingCircleWithCircles(hdc,color);
            break;

        case DE_Direct:
            shape = new DirectEllipse(hdc,color);
            break;
        case DE_POLAR:
            shape = new PolarEllipse(hdc,color);
            break;
        case DE_MIDPOINT:
            shape = new MidpointEllipse(hdc,color);
            break;

        case DH_SQUARE_HERMITE:
            shape = new FillingSquareWithHermite(hdc,color);
            break;
        case DB_RECTANGLE_BEZIER:
            shape = new FillingRectangleWithBezier(hdc,color);
            break;
        case DS_SPLINE:
            shape = new CardinalSpline(hdc,color);
            break;

        case DF_RECURSIVE_FLOOD:
            shape = new RecursiveFloodFilling(hdc,color,color);
            break;
        case DF_NON_RECURSIVE_FLOOD:
            shape = new NonRecursiveFloodFilling(hdc,color,color);
            break;
        case DF_CONVEX:
            shape = new ConvexFilling(hdc,color);
            break;
        case DF_NON_CONVEX:
            shape = new NonConvexFilling(hdc,color);
            break;

        case DC_RECTANGLE_POINT:
            shape = new RectangleClippingPoint(hdc,color);
            break;
        case DC_RECTANGLE_LINE:
            shape = new RectangleClippingLine(hdc,color);
            break;
        case DC_RECTANGLE_POLYGON:
            shape = new RectangleClippingPolygon(hdc,color);
            break;

        case DC_SQUARE_POINT:
            shape = new SquareClippingPoint(hdc,color);
            break;
        case DC_SQUARE_LINE:
            shape = new SquareClippingLine(hdc,color);
            break;

        case DC_CIRCLE_POINT:
            shape = new CircleClippingPoint(hdc,color);
            break;
        case DC_CIRCLE_LINE:
            shape = new CircleClippingLine(hdc,color);
            break;
    }

    return shape;
}

void HandleTransformationMenu(Line* line, WPARAM wParam) {
    Transformation* transformation = new Transformation(line);
    int itemId = LOWORD(wParam);

    switch (itemId) {
        case T_TRANSLATE:
            transformation->TranslateLine();
            break;
        case T_SCALE:
            transformation->ScaleLine();
            break;
    }

    delete transformation;
    transformation = NULL;
}

Shape* HandleAllMenus(HWND hwnd, WPARAM wParam) {
    int wmId = LOWORD(wParam);
    int wmEvent = HIWORD(wParam);

    static COLORREF shapeColor = RGB(255,0,0);
    static Shape* shape = NULL;

    HMENU mainMenu = GetMenu(hwnd);
    HMENU windowMenu = GetSubMenu(mainMenu, 0);
    HMENU editMenu = GetSubMenu(mainMenu, 1);
    HMENU drawMenu = GetSubMenu(mainMenu, 2);
    HMENU TransformationMenu = GetSubMenu(mainMenu, 3);
    HMENU colorMenu = GetSubMenu(mainMenu, 4);

    if (wmEvent!=0 || wmId==0)
        return NULL;

    if (mainMenu==NULL || windowMenu==NULL || editMenu==NULL || drawMenu==NULL || colorMenu==NULL)
        return NULL;

    if (GetMenuState(windowMenu, wmId, MF_BYCOMMAND)!=-1)
        HandleWindowMenu(hwnd,wParam);

    if (GetMenuState(editMenu, wmId, MF_BYCOMMAND)!=-1)
        HandleEditMenu(wParam,hwnd);

    if (GetMenuState(drawMenu, wmId, MF_BYCOMMAND)!=-1) {
        system("cls");
        shape = HandleDrawMenu(hwnd,wParam,shapeColor);
    }

    if (GetMenuState(TransformationMenu, wmId, MF_BYCOMMAND)!=-1) {
        if (dynamic_cast<Line*>(shape) != nullptr) {
            Line* line = dynamic_cast<Line*>(shape);
            HandleTransformationMenu(line,wParam);
        }
        else
            cout << "To Transform a Shape, It Must Be Line" << endl;
    }

    if (GetMenuState(colorMenu, wmId, MF_BYCOMMAND)!=-1) {
        shapeColor = ChooseColor(hwnd,shapeColor);
        if (shape!=NULL)
            shape->ChangeCOlor(shapeColor);
    }

    return shape;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static Shape* shape = NULL;
    static Shape* newShape = NULL;

    switch (message)                  /* handle the messages */
    {
        // Handle menu item selection
        case WM_COMMAND:
            newShape = HandleAllMenus(hwnd,wParam);
            if (newShape!=NULL) {
                shape = newShape;
                newShape = NULL;
            }
            break;
        case WM_LBUTTONDOWN:
            if (shape!=NULL)
                shape->GetLButtonDown(lParam);
            break;
        case WM_LBUTTONUP:
            if (shape!=NULL)
                shape->GetLButtonUp(lParam);
            break;
        case WM_RBUTTONDOWN:
            if (shape!=NULL)
                shape->GetRButtonDown(lParam);
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't  deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

