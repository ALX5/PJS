/* 
 * File:   TestProjection.cpp
 * Author: bruno
 * 
 * Created on January 28, 2014, 3:33 PM
 */

#include <opencv2/opencv.hpp>
#include "TestProjection.h"
#include "Projection.h"
#include "User.h"
#include <iostream>


TestProjection::TestProjection() {
}

TestProjection::TestProjection(const TestProjection& orig) {
}

TestProjection::~TestProjection() {
}

void TestProjection::test() {
    
    cv::Point3f p11(-250, 100, 250);
    cv::Point3f p12(0, 50, 0);
    cv::Point3f p13(0, 400, 0);
    cv::Point3f p14(-250, 450, 250);
    
    cv::Point3f p21(0, 50, 0);
    cv::Point3f p22(250, 50, 250);
    cv::Point3f p23(250, 380, 250);
    cv::Point3f p24(0, 400, 0);
    
    Plane3d p1(p11, p12, p13, p14);
    
    Plane3d p2(p21, p22, p23, p24);
    
    std::vector<Plane3d> planes;
    planes.push_back(p1);
    planes.push_back(p2);
    
    Projection proj(planes);

    User u(proj);
    double x = 0.0;
    double y = 250.0;
    double z = 1000.0;
    u.updatePosition(x, y, z);
    
    
}
