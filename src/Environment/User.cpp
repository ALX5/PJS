/* 
 * File:   User.cpp
 * Author: bruno
 * 
 * Created on January 28, 2014, 2:37 PM
 */
#include <cmath>
#include <iostream>
#include "User.h"
#include "GeometryUtils.h"

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

    //Get the projection center and surfaces
    cv::Point3f projectionCenter = _projection.getCenter();
    std::vector<Plane3d> planes = _projection.getPlanes();    
    
    GeometryUtils gUtils;

    //Compute the projection plane normal
    cv::Point3f normal = gUtils.normalizeVector(_position - projectionCenter);

    //This vector will store the projection of the projected surfaces
    //onto the viewers orthogonal plane
    std::vector<Plane3d> projectedPlanes;

    //Iterate over projected surfaces
    std::vector<Plane3d>::iterator ii;
    for (ii = planes.begin(); ii != planes.end(); ii++) {

        //Get the points of the current surface
        std::vector<cv::Point3f> points = (*ii).getPoints();
        std::vector<cv::Point3f>::iterator jj;

        //This list will contain the resulting intersections
        std::vector<cv::Point3f> intersections;

        //Iterate over the points of the surface to find the intersection
        //of each corresponding ray
        for (jj = points.begin(); jj != points.end(); jj++) {

            std::cout << "Calculating inter for: " << *jj << std::endl;

            //TODO Shit semantics. Use vectors when necessary.

            //Express the point and the projection center       
            //in user space (only considering location)
            //to obtain the corresponding ray and plane
            cv::Vec3f p = *jj - _position;
            cv::Point3f center = projectionCenter - _position;                    

            //Calculate the intersection
            cv::Point3f intersection = gUtils.intersection(p, normal, center);
            
            //Return the intersection from user space to world space
            //TODO verify the correctness of this transformation
            intersection = -intersection + _position;

            std::cout << intersection << std::endl;
            std::cout << "In plane?" << std::endl;
            std::cout << "Epsilon = " << (intersection - projectionCenter).dot(normal) 
            << std::endl;

            //And add it to the list
            intersections.push_back(intersection);

        }
        Plane3d projectedPlane(intersections);
        projectedPlanes.push_back(projectedPlane);

    }

    //Rotate the obtained intersections to align them to the orthogonal plane

    //Normalize the plane normal (equivalent to the user's position from
    //the projection center)
    cv::Vec3f normalized = gUtils.normalizeVector(normal);

    //Get the rotation axis
    cv::Vec3f zed(0, 0, -1);
    cv::Vec3f axis = gUtils.crossProduct(normalized, zed);

    cv::Point3f normalAxis = gUtils.normalizeVector(axis);

    double angle = std::acos(normalized[0] * zed[0] +
            normalized[1] * zed[1] +
            normalized[2] * zed[2]);
    
    std::cout << "Angle: " << angle << std::endl;
    
    //TODO Not sure if this works properly
    //Rotate all intersections to align them with the plane
    for (ii = projectedPlanes.begin(); ii != projectedPlanes.end(); ii++) {
        //Get the points of the current surface
        std::vector<cv::Point3f> points = (*ii).getPoints();
        std::vector<cv::Point3f>::iterator jj;

        std::vector<cv::Point3f> rotatedPoints;
        
        std::cout << "Non-Rotated plane" << std::endl;
        std::cout << *ii << std::endl;

        for (jj = points.begin(); jj != points.end(); jj++) {
            cv::Point3f p = *jj;
            p = p - projectionCenter;
            cv::Point3f rotated = gUtils.rotateAroundAxis(p, normalAxis, -angle);
            rotatedPoints.push_back(rotated);
        }
        
        Plane3d plane(rotatedPoints);
        std::cout << "Rotated plane" << std::endl;
        std::cout << plane << std::endl;
        _projectedPlanes.push_back(plane);
    }
}

std::vector<Plane3d> User::getProjectedPlanes() {
    return _projectedPlanes;
}
