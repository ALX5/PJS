/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#ifndef PLANE3D_H
#define	PLANE3D_H

#include <vector>
#include <opencv2/opencv.hpp>
#include "Plane.h"
#include "Plane2d.h"

class Plane3d : public Plane<cv::Point3f>{
    
public:
    Plane3d(cv::Point3f p1, cv::Point3f p2, cv::Point3f p3, cv::Point3f p4);
    Plane3d(std::vector<cv::Point3f> points);
    Plane3d(const Plane3d& orig);
    virtual ~Plane3d();
    
    /**
     * Returns the projection of this plane onto 2D space
     * @return
     */
    Plane2d to2d();
    
private:    
};

#endif	/* PLANE3D_H */

