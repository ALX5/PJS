#include "plane.h"
#include <iostream>
using namespace std;

Plane::Plane() {
}

Plane::Plane(Point2f p1, Point2f p2, Point2f p3, Point2f p4) {
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
}

Plane::Plane(vector<Point2f> pts) {
    points.push_back(pts.at(0));
    points.push_back(pts.at(1));
    points.push_back(pts.at(2));
    points.push_back(pts.at(3));
}

Point2f Plane::getPoint(int n) {
    return points.at(n);
}

vector<Point2f> Plane::getPoints() {
        return points;
}



std::ostream &operator<<(std::ostream& os, Plane& m) {
    os << m.getPoints();
//    os << "(" << m.getPoint(0) << ", " 
//            << m.getPoint(1) << ", "
//            << m.getPoint(2) << ", "
//            << m.getPoint(3) << ")" ;
    return os;
}

void Plane::moveTo(Point2f &p) {
 
    Point2f offset = this->findOffset(p);
    
    for(int i = 0; i < points.size(); i++){
        points.at(i) = points.at(i) - offset;
    }
    
}


void Plane::moveToOrigin() {

    Point2f origin(0,0);
    this->moveTo(origin);    
}

//TODO Refactor
void Plane::moveBBToOrigin() {

    Point2f origin(0,0);
    Point2f offset = this->findBBOffset(origin);
    
    for(int i = 0; i < points.size(); i++){
        points.at(i) = points.at(i) - offset;
    }
    
}


Point2f Plane::findOffset(Point2f& p) {
    Point2f upperLeftCorner = this->getPoint(0);
    float x = upperLeftCorner.x - p.x;
    float y = upperLeftCorner.y - p.y;
    Point2f offset = Point2f(x, y);
    
    return offset;
}

Point2f Plane::findBBOffset(Point2f& p) {

    vector<float> xCoords;
    xCoords.push_back(this->getPoint(0).x);
    xCoords.push_back(this->getPoint(1).x);
    xCoords.push_back(this->getPoint(2).x);
    xCoords.push_back(this->getPoint(3).x);
    
    vector<float> yCoords;
    yCoords.push_back(this->getPoint(0).y);
    yCoords.push_back(this->getPoint(1).y);
    yCoords.push_back(this->getPoint(2).y);
    yCoords.push_back(this->getPoint(3).y);
    
    float minX = *std::min_element(xCoords.begin(), xCoords.end());
    float minY = *std::min_element(yCoords.begin(), yCoords.end());
    
    return Point2f(minX-p.x, minY-p.y);
    
}


//TODO refactor
Plane Plane::getBoundingBox() {
    vector<float> xCoords;
    xCoords.push_back(this->getPoint(0).x);
    xCoords.push_back(this->getPoint(1).x);
    xCoords.push_back(this->getPoint(2).x);
    xCoords.push_back(this->getPoint(3).x);
    
    vector<float> yCoords;
    yCoords.push_back(this->getPoint(0).y);
    yCoords.push_back(this->getPoint(1).y);
    yCoords.push_back(this->getPoint(2).y);
    yCoords.push_back(this->getPoint(3).y);
    
    float minX = *std::min_element(xCoords.begin(), xCoords.end());
    float minY = *std::min_element(yCoords.begin(), yCoords.end());
    float maxX = *std::max_element(xCoords.begin(), xCoords.end());
    float maxY = *std::max_element(yCoords.begin(), yCoords.end());

    
    Plane p(Point2f(minX, minY), Point2f(minX, maxY), Point2f(maxX, minY), Point2f(maxX, maxY)); 

    return p;
}

Plane Plane::getBoundingBox(Plane &p2, Plane &p1) {
    vector<float> xCoords;
    
    xCoords.push_back(p1.getPoint(0).x);
    xCoords.push_back(p1.getPoint(1).x);
    xCoords.push_back(p1.getPoint(2).x);
    xCoords.push_back(p1.getPoint(3).x);
    xCoords.push_back(p2.getPoint(0).x);
    xCoords.push_back(p2.getPoint(1).x);
    xCoords.push_back(p2.getPoint(2).x);
    xCoords.push_back(p2.getPoint(3).x);
    
    
    vector<float> yCoords;
    yCoords.push_back(p1.getPoint(0).y);
    yCoords.push_back(p1.getPoint(1).y);
    yCoords.push_back(p1.getPoint(2).y);
    yCoords.push_back(p1.getPoint(3).y);
    yCoords.push_back(p2.getPoint(0).y);
    yCoords.push_back(p2.getPoint(1).y);
    yCoords.push_back(p2.getPoint(2).y);
    yCoords.push_back(p2.getPoint(3).y);
    
    
    float minX = *std::min_element(xCoords.begin(), xCoords.end());
    float minY = *std::min_element(yCoords.begin(), yCoords.end());
    float maxX = *std::max_element(xCoords.begin(), xCoords.end());
    float maxY = *std::max_element(yCoords.begin(), yCoords.end());
    
    Plane p(Point2f(minX, minY), Point2f(minX, maxY), Point2f(maxX, minY), Point2f(maxX, maxY)); 
    
    return p;
}


Size Plane::getSize()
{
    Point P1 = this->getPoint(0);
    Point P4 = this->getPoint(3);

    int width = P4.x - P1.x;
    int height = P4.y - P1.y;

    Size size = Size(width, height);cout << height << endl;

    return size;
}
