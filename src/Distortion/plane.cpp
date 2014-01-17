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

    for (int i = 0; i < points.size(); i++) {
        points.at(i) = points.at(i) - offset;
    }

}

void Plane::moveToOrigin() {

    Point2f origin(0, 0);
    this->moveTo(origin);
}

//TODO Refactor

void Plane::moveBBToOrigin() {

    Point2f origin(0, 0);
    Point2f offset = this->findBBOffset(origin);

    for (int i = 0; i < points.size(); i++) {
        points.at(i) = points.at(i) - offset;
    }

}

Point2f Plane::findOffset(Point2f& p) {
    Point2f upperLeftCorner = this->getPoint(0);
    float x = upperLeftCorner.x - p.x;
    float y = upperLeftCorner.y - p.y;
    Point2f offset = Point2f(x, y);

    cout << "Offset from origin: " << offset << endl;
    ;


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

    return Point2f(minX - p.x, minY - p.y);

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

//TODO not finished

bool Plane::contains(Point2f& p) {

    //TODO use proper point retrieval
    Point2f upperVector(points.at(2).x - points.at(0).x, points.at(2).y - points.at(0).y);
    Point2f lowerVector(points.at(3).x - points.at(1).x, points.at(3).y - points.at(3).y);
    //    Point2f pointVector(p.x - points.at(0).x, p.y - points.at(3).y);

    bool oddNodes = false;
    int next = 3;


    for (int i = 0; i < 4; i++) {
        Point2f current = this->getPoint(i);
        Point2f last = this->getPoint(next);
        if (current.y < p.y && last.y >= p.y
                || last.y < p.y && current.y >= p.y) {
            if (current.x + (p.y - current.y) /
                    (last.y - current.y)*(last.x - current.x) < p.x) {
                oddNodes = !oddNodes;
            }
        }
        next = i;
    }

    return oddNodes;

}

Size Plane::getSize() {
    Point P1 = this->getPoint(0);
    Point P4 = this->getPoint(3);

    int width = P4.x - P1.x;
    int height = P4.y - P1.y;

    Size size = Size(width, height);
    cout << height << endl;

    return size;
}