/* 
 * File:   User.h
 * Author: bruno
 *
 * Created on January 28, 2014, 2:37 PM
 */

#ifndef USER_H
#define	USER_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Projection.h"

class User {
public:
    User();
    User(Projection &projection);
    User(const User& orig);
    virtual ~User();
    
    void updatePosition(double &x, double &y, double &z);
    
    std::vector<Plane3d> getProjectedPlanes();
    
    void print();
    
private:
    //The position of the user's head. This varies constantly.
    cv::Point3f _position;
    
    //A representation of the surface projected by the projector    
    Projection _projection;
    
    //The projected surface as viewed by the user
    std::vector<Plane3d> _projectedPlanes;
    
};

#endif	/* USER_H */

