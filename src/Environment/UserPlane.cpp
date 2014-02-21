/* 
 * File:   UserPlane.cpp
 * Author: bruno
 * 
 * Created on February 19, 2014, 4:14 PM
 */

#include "UserPlane.h"

UserPlane::UserPlane() {
}

UserPlane::UserPlane(const UserPlane& orig) {
}

UserPlane::~UserPlane() {
}

UserPlane::UserPlane(cv::Point3f &position, cv::Point3f &normal):
        _position(position), _normal(normal){
}

cv::Point3f UserPlane::getNormal() {
    return _normal;
}

cv::Point3f UserPlane::getPosition() {
    return _position;
}

