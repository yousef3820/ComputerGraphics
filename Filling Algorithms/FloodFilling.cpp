#include "FloodFilling.h"

void FloodFilling::GetLButtonDown(LPARAM lParam) {
    x = LOWORD(lParam);
    y = HIWORD(lParam);
}

void FloodFilling::GetLButtonUp(LPARAM lParam) {
    Draw();
}

void FloodFilling::GetRButtonDown(LPARAM lParam) {}

void FloodFilling::Draw() {
    Fill(hdc,x,y,color,bColor);
}

FloodFilling::~FloodFilling() {}
