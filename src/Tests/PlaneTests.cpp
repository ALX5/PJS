/* 
 * File:   PlaneTests.cpp
 * Author: bruno
 * 
 * Created on January 17, 2014, 2:13 PM
 */

#include "PlaneTests.h"
#include <iostream>
#include "../Distortion/plane.h"
using namespace std;

PlaneTests::PlaneTests() {
}

PlaneTests::PlaneTests(const PlaneTests& orig) {
}

PlaneTests::~PlaneTests() {
}

void PlaneTests::testContains() {
    Plane p1(Point2f(25.0, 0.0), Point2f(0.0, 100.0), Point2f(100.0, 10.0), Point2f(91.0, 110.0));
    Point2f point1(0.0, 0.0);
    Point2f point2(26.0, 2.0);
    Point2f point3(1000.0, 0.0);
    Point2f point4(50.0, 50.0);
    
    assert(!p1.contains(point1));
    assert(p1.contains(point2));
    assert(!p1.contains(point3));
    assert(p1.contains(point4));
    
    cout << "Tests OK" << endl;
    
}


