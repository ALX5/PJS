/* 
 * File:   User.cpp
 * Author: bruno
 * 
 * Created on January 28, 2014, 2:37 PM
 */
#include <cmath>
#include <iostream>
#include "User.h"

User::User(Projection& projection) {
    _projection = projection;
}

User::User(const User& orig) {
}

User::~User() {
}

void User::updatePosition(double &x, double &y, double &z) {
    //Update the position
    _position.x = x;
    _position.y = y;
    _position.z = z;

    cv::Point3f projectionCenter = _projection.getCenter();
    std::vector<Plane3d> planes = _projection.getPlanes();

    //Compute the projection plane normal
    cv::Point3f normal = _position - projectionCenter;
    
    std::vector<Plane3d> projectedPlanes;    
    //Iterate over projected surfaces
    std::vector<Plane3d>::iterator ii;    
    for (ii = planes.begin(); ii != planes.end(); ii++) {        
        //Get the points of the current surface
        std::vector<cv::Point3f> points = (*ii).getPoints();
        std::vector<cv::Point3f>::iterator jj;              
        
        //This list will contain the resulting intersections
        std::vector<cv::Point3f> intersections;
        
        //Calculate the intersection between the user's projection plane
        //and the ray from the user to each corner of the projection surface
        for (jj = points.begin(); jj != points.end(); jj++) {
            
            //Express the point in user space (only considering location)
            cv::Point3f p = *jj - _position;

            double num = -_position.dot(projectionCenter);
            double den = _position.dot(p);
            
            //Scalar that indicates the point of intersection
            double t = num / den;
            
            //The intersection
            cv::Point3f intersection(t*p.x, t*p.y, t*p.z);
            
            //Return the intersection from user space to world space
            intersection = intersection + _position;
            
            //And add it to the list
            intersections.push_back(intersection);
                       
        }
        Plane3d projectedPlane(intersections);
        projectedPlanes.push_back(projectedPlane);
        
    }
    std::cout << projectedPlanes.at(0) << std::endl;
    
    
    
    //TODO Get projectedPlanes according to projection center basis ()
    
    
    
    /*
     * ****************************
     * Temporary
     * ****************************
     */
    
    double normalLength = std::pow(_position.x, 2) + std::pow(_position.y, 2) 
    + std::pow(_position.z, 2);
    cv::Point3f normalized(_position.x/normalLength, 
            _position.y/normalLength, 
            _position.z/normalLength);
    
    

}
