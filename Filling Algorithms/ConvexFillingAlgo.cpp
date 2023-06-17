#include "ConvexFillingAlgo.h"

void ConvexFillingAlgo::GetLButtonDown(LPARAM lParam) {
    point point;
    point.x = LOWORD(lParam);
    point.y = HIWORD(lParam);
    this->points.push_back(point);
}

void ConvexFillingAlgo::GetLButtonUp(LPARAM lParam) {}

void ConvexFillingAlgo::GetRButtonDown(LPARAM lParam) {
    this->Draw();
    this->points.clear();
}

void ConvexFillingAlgo::Draw() {
    Fill(hdc,this->points,this->points.size(),color);
}

ConvexFillingAlgo::~ConvexFillingAlgo() {}
