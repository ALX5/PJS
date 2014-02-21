/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
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
