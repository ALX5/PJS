/* 
 * File:   TestPlanes.cpp
 * Author: bruno
 * 
 * Created on January 27, 2014, 10:12 AM
 */

#include "TestPlanes.h"
#include "Plane3d.h"
#include <opencv2/opencv.hpp>

TestPlanes::TestPlanes() {
}

TestPlanes::TestPlanes(const TestPlanes& orig) {
}

TestPlanes::~TestPlanes() {
}

void TestPlanes::test() {
    cv::Point3f p1(0.1, 0.3, 0.2);
    cv::Point3f p2(0.1, 0.3, 0.2);
    cv::Point3f p3(0.1, 0.3, 0.2);
    cv::Point3f p4(0.1, 0.3, 0.2);
    Plane3d p(p1, p2, p3, p4);
}
