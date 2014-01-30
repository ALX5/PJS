/* 
 * File:   Projection.h
 * Author: bruno
 *
 * Created on January 28, 2014, 2:32 PM
 */

#ifndef PROJECTION_H
#define	PROJECTION_H

#include <vector>
#include "Plane3d.h"

#include <opencv2/opencv.hpp>

class Projection {
public:
    Projection();
    Projection(Plane3d &p1, Plane3d &p2);
    Projection(std::vector<Plane3d> &planes);
    virtual ~Projection();
    
    cv::Point3f getCenter();
    std::vector<Plane3d> getPlanes();
    
private:
    std::vector<Plane3d> _planes;
    cv::Point3f _center;

};

#endif	/* PROJECTION_H */

