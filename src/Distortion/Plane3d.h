/* 
 * File:   Plane3d.h
 * Author: bruno
 *
 * Created on January 27, 2014, 9:47 AM
 */

#ifndef PLANE3D_H
#define	PLANE3D_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "Plane.h"

class Plane3d : public Plane<cv::Point3f>{
    
public:
    Plane3d(cv::Point3f p1, cv::Point3f p2, cv::Point3f p3, cv::Point3f p4);
    Plane3d(std::vector<cv::Point3f> points);
    Plane3d(const Plane3d& orig);
    virtual ~Plane3d();
    
    
private:    
};

#endif	/* PLANE3D_H */

