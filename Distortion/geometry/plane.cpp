#include "plane.h"

Plane::Plane()
{
}

Plane::Plane(Point2f p1, Point2f p2, Point2f p3, Point2f p4){
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
}

Point2f Plane::getPoint(int n) {
    return points.at(n);
}
