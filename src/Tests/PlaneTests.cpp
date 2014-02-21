/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#include "PlaneTests.h"
#include <iostream>
#include "../Distortion/Plane2d.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


PlaneTests::PlaneTests() {
}

PlaneTests::PlaneTests(const PlaneTests& orig) {
}

PlaneTests::~PlaneTests() {
}

void PlaneTests::testContains() {
    Plane2d p1(Point2f(25.0, 0.0), Point2f(0.0, 100.0), Point2f(100.0, 10.0), Point2f(91.0, 110.0));
    Point2f point1(0.0, 0.0);
    Point2f point2(26.0, 2.0);
    Point2f point3(1000.0, 0.0);
    Point2f point4(50.0, 50.0);
    Point2f point5(50.0, 90.0);

    
    assert(!p1.contains(point1));
    assert(p1.contains(point2));
    assert(!p1.contains(point3));
    assert(p1.contains(point4));
    assert(p1.contains(point5));
    
    Plane2d p2(Point2f(25.0, 0.0), Point2f(0.0, 100.0), Point2f(100.0, 10.0), Point2f(91.0, 110.0));
    
    p2.getCenter();
    
    cout << "Tests OK" << endl;
    
}


