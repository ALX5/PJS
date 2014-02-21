/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#ifndef PROJECTION_H
#define	PROJECTION_H

#include <vector>
#include "Plane3d.h"

#include <opencv2/opencv.hpp>

class Projection {
public:
    Projection();
    Projection(std::vector<Plane3d> &planes);
    virtual ~Projection();
    
    cv::Point3f getCenter();
    std::vector<Plane3d> getPlanes();
    
    void print();
    
private:
    std::vector<Plane3d> _planes;
    cv::Point3f _center;

};

#endif	/* PROJECTION_H */

