#include "Plane2d.h"
#include <iostream>
using namespace std;

Plane2d::Plane2d() {
}

Plane2d::Plane2d(cv::Point2f p1, cv::Point2f p2, cv::Point2f p3, cv::Point2f p4)
: Plane(p1, p2, p3, p4) {

}

Plane2d::Plane2d(vector<cv::Point2f> pts) : Plane(pts) {
}

void Plane2d::moveTo(cv::Point2f &p) {

    cv::Point2f offset = this->findOffset(p);
    for (int i = 0; i < points.size(); i++) {
        points.at(i) = points.at(i) - offset;
    }
}

void Plane2d::moveToOrigin() {

    cv::Point2f origin(0, 0);
    this->moveTo(origin);
}

//TODO Refactor

void Plane2d::moveBBToOrigin() {

    cv::Point2f origin(0, 0);
    cv::Point2f offset = this->findBBOffset(origin);

    for (int i = 0; i < points.size(); i++) {
        points.at(i) = points.at(i) - offset;
    }
}

void Plane2d::moveBBTo(cv::Point2f& p) {

    cv::Point2f offset = this->findBBOffset(p);

    for (int i = 0; i < points.size(); i++) {
        points.at(i) = points.at(i) - offset;
    }
}

cv::Point2f Plane2d::findOffset(cv::Point2f& p) {
    cv::Point2f upperLeftCorner = this->getUpperLeftCorner();

    float x = upperLeftCorner.x - p.x;
    float y = upperLeftCorner.y - p.y;
    cv::Point2f offset = cv::Point2f(x, y);



    return offset;
}

cv::Point2f Plane2d::findBBOffset(cv::Point2f& p) {

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

    return cv::Point2f(minX - p.x, minY - p.y);

}


//TODO refactor

Plane2d Plane2d::getBoundingBox() {
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

    Plane2d p(cv::Point2f(minX, minY), cv::Point2f(minX, maxY),
            cv::Point2f(maxX, minY), cv::Point2f(maxX, maxY));

    return p;
}

//TODO remove

Plane2d Plane2d::getBoundingBox(Plane2d &p2, Plane2d &p1) {
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

    Plane2d p(cv::Point2f(minX, minY), cv::Point2f(minX, maxY), cv::Point2f(maxX, minY), cv::Point2f(maxX, maxY));

    return p;
}

bool Plane2d::contains(cv::Point2f& p) {

    bool oddNodes = false;
    int next = 3;

    vector<cv::Point2f> sortedPoints;
    sortedPoints.push_back(this->getUpperLeftCorner());
    sortedPoints.push_back(this->getUpperRightCorner());
    sortedPoints.push_back(this->getLowerRightCorner());
    sortedPoints.push_back(this->getLowerLeftCorner());

    for (int i = 0; i < 4; i++) {
        cv::Point2f current = sortedPoints.at(i);
        cv::Point2f last = sortedPoints.at(next);
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

cv::Size Plane2d::getSize() {
    cv::Point p1 = this->getPoint(0);
    cv::Point p4 = this->getPoint(3);

    int width = p4.x - p1.x;
    int height = p4.y - p1.y;

    cv::Size size = cv::Size(width, height);
    //cout << height << endl;

    return size;
}

//TODO REFACTOR

cv::Point2f Plane2d::getUpperLeftCorner() {
    cv::Point2f p1 = this->getPoint(0);
    cv::Point2f p2 = this->getPoint(1);
    cv::Point2f aux;
    if (p2.x < p1.x) {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }

    cv::Point2f p3 = this->getPoint(2);
    if (p3.x < p2.x) {
        p2 = p3;
        if (p2.x < p1.x) {
            aux = p1;
            p1 = p2;
            p2 = aux;
        }
    }

    p3 = this->getPoint(3);
    if (p3.x < p2.x) {
        p2 = p3;
    }

    if (p2.y < p1.y) {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }

    return p1;
}

cv::Point2f Plane2d::getUpperRightCorner() {
    cv::Point2f p1 = this->getPoint(0);
    cv::Point2f p2 = this->getPoint(1);
    cv::Point2f aux;

    if (p2.y < p1.y) {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }

    cv::Point2f p3 = this->getPoint(2);
    if (p3.y < p2.y) {
        p2 = p3;
        if (p2.y < p1.y) {
            aux = p1;
            p1 = p2;
            p2 = aux;
        }
    }

    p3 = this->getPoint(3);
    if (p3.y < p2.y) {
        p2 = p3;
    }

    if (p2.x > p1.x) {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }

    return p1;
}

cv::Point2f Plane2d::getLowerRightCorner() {
    cv::Point2f p1 = this->getPoint(0);
    cv::Point2f p2 = this->getPoint(1);
    cv::Point2f aux;
    if (p2.x > p1.x) {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }

    cv::Point2f p3 = this->getPoint(2);
    if (p3.x > p2.x) {
        p2 = p3;
    }

    if (p2.x > p1.x) {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }

    p3 = this->getPoint(3);
    if (p3.x > p2.x) {
        p2 = p3;
    }

    if (p2.y > p1.y) {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }

    return p1;
}

cv::Point2f Plane2d::getLowerLeftCorner() {
    cv::Point2f p1 = this->getPoint(0);
    cv::Point2f p2 = this->getPoint(1);
    cv::Point2f aux;
    if (p2.y > p1.y) {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }

    cv::Point2f p3 = this->getPoint(2);
    if (p3.y > p2.y) {
        p2 = p3;
    }

    if (p2.y > p1.y) {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }

    p3 = this->getPoint(3);
    if (p3.y > p2.y) {
        p2 = p3;
    }

    if (p2.x < p1.x) {
        aux = p1;
        p1 = p2;
        p2 = aux;
    }

    return p1;
}

bool Plane2d::boxContains(cv::Point2f &p) {

    Plane2d box = this->getBoundingBox();
    return ( p.x >= box.getUpperLeftCorner().x
            && p.x <= box.getUpperRightCorner().x
            && p.y >= box.getUpperRightCorner().y
            && p.y <= box.getLowerRightCorner().y);
}

//TODO inner box

bool Plane2d::innerBoxContains(cv::Point2f&) {
    return true;
}

//TODO Look for algorithm to find inner box

Plane2d Plane2d::getInnerBox() {
    Plane2d p(cv::Point2f(0.0, 0.0), cv::Point2f(0.0, 0.0), cv::Point2f(0.0, 0.0), cv::Point2f(0.0, 0.0));
    return p;
}

int Plane2d::getWidth() {
    return this->getBoundingBox().getUpperRightCorner().x - this->getBoundingBox().getUpperLeftCorner().x;
}

int Plane2d::getHeight() {
    return this->getBoundingBox().getLowerRightCorner().y - this->getBoundingBox().getUpperRightCorner().y;
}

//TODO Generic implementation

cv::Point2f Plane2d::getCenter() {

    std::vector<cv::Point2f>::iterator ii;

    float sumX = 0.0;
    float sumY = 0.0;

    for (ii = points.begin(); ii != points.end(); ii++) {

        sumX += (*ii).x;
        sumY += (*ii).y;

    }

    cv::Point2f center(sumX / points.size(), sumY / points.size());
    return center;
}

namespace pjs {

    cv::Vec2f distance(Plane2d &p1, Plane2d &p2) {
        cv::Point2f c1 = p1.getCenter();
        cv::Point2f c2 = p2.getCenter();
        cv::Vec2f distance(c1.x - c2.x, c1.y - c2.y);
        return distance;
    }
}

Plane2d Plane2d::yInverted() {
    Plane2d p(cv::Point2f(this->getPoint(0).x, -this->getPoint(0).y),
            cv::Point2f(this->getPoint(1).x, -this->getPoint(1).y),
            cv::Point2f(this->getPoint(2).x, -this->getPoint(2).y),
            cv::Point2f(this->getPoint(3).x, -this->getPoint(3).y));

    return p;
}
