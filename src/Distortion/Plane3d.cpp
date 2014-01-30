/* 
 * File:   Plane3d.cpp
 * Author: bruno
 * 
 * Created on January 27, 2014, 9:47 AM
 */

#include "Plane3d.h"

Plane3d::Plane3d(cv::Point3f p1, cv::Point3f p2, cv::Point3f p3, cv::Point3f p4) :
            Plane(p1, p2, p3, p4){
}

Plane3d::Plane3d(std::vector<cv::Point3f> pts) : Plane(pts){
    
}

Plane3d::Plane3d(const Plane3d& orig) : Plane(orig){
}

Plane3d::~Plane3d() {
}

