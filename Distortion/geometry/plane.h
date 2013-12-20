#ifndef PLANE_H
#define PLANE_H

#include <opencv2/opencv.hpp>

using namespace cv;
class Plane {
private:    
    vector<Point2f> points;
public:
    Plane();
    Plane(Point2f, Point2f, Point2f, Point2f);
    Point2f* getPoints();
    Point2f getPoint(int n);
    void setPoints(Point2f, Point2f, Point2f, Point2f);
};

#endif // PLANE_H
