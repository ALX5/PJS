/* 
 * File:   UserPlane.h
 * Author: bruno
 *
 * Created on February 19, 2014, 4:14 PM
 */

#ifndef USERPLANE_H
#define	USERPLANE_H

#include <opencv2/opencv.hpp>

/**
 * This class represents a plane described by a point in it (position) 
 * and its normal
 */
class UserPlane {
    friend class User;
public:
    UserPlane();
    UserPlane(const UserPlane& orig);
    virtual ~UserPlane();
    
    UserPlane(cv::Point3f &position, cv::Point3f &normal);
    
    cv::Point3f getPosition();
    cv::Point3f getNormal();
    
private:
    cv::Point3f _position;
    cv::Point3f _normal;
    
};

#endif	/* USERPLANE_H */

