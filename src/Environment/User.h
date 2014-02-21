/* 
 * File:   User.h
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Created on January 28, 2014, 2:37 PM
 */

#ifndef USER_H
#define	USER_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Projection.h"
#include "UserPlane.h"

class User {
public:
    User();
    User(Projection &projection);
    User(const User& orig);
    virtual ~User();

    /**
     * This function updates the user's position and recalculates all
     * necessary values
     * @param x
     * @param y
     * @param z
     */
    void updatePosition(double &x, double &y, double &z);

    /**
     * Casts rays from the user's position to the given points, then finds
     * the intersections between them and the given plane
     * @param points
     * @param plane
     * @return 
     */
    std::vector<cv::Point3f> findIntersections(std::vector<cv::Point3f> &points,
            UserPlane &plane);

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

