/* 
 * File:   Projection.cpp
 * Author: bruno
 * 
 * Created on January 28, 2014, 2:32 PM
 */

#include <iostream>
#include <algorithm> 
#include "Projection.h"

// This defines a binary predicate that, 
// taking two values of the same type of those 
// contained in the list, returns true if the first 
// argument goes before the second argument

bool pointComparator(cv::Point3f pt1, cv::Point3f pt2) {

    if (pt1.x != pt2.x) {
        if (pt1.x < pt2.x) {
            return true;
        } else {
            return false;
        }
    } else if (pt1.y != pt2.y) {
        if (pt1.y < pt2.y) {
            return true;
        } else {
            return false;
        }
    } else {
        if (pt1.z < pt2.z) {
            return true;
        } else {
            return false;
        }
    }

}

Projection::Projection() {

}

//TODO Move semantics

Projection::Projection(std::vector<Plane3d>& planes) {

    std::vector<cv::Point3f> points;

    std::vector<Plane3d>::iterator planeIt;
    for (planeIt = planes.begin(); planeIt != planes.end(); planeIt++) {
        _planes.push_back(*planeIt);
        points.push_back((*planeIt).getPoint(0));
        points.push_back((*planeIt).getPoint(1));
        points.push_back((*planeIt).getPoint(2));
        points.push_back((*planeIt).getPoint(3));
    }
    
    //Sort
    std::sort(points.begin(), points.end(), pointComparator);

    std::list<cv::Point3f> sortedPoints;

    std::vector<cv::Point3f>::iterator pointIt2;
    for (pointIt2 = points.begin(); pointIt2 != points.end(); pointIt2++) {
        sortedPoints.push_back(*pointIt2);
    }

    //Remove duplicates
    sortedPoints.unique();

    float sumX = 0.0;
    float sumY = 0.0;
    float sumZ = 0.0;
    std::list<cv::Point3f>::iterator pointIt;
    for (pointIt = sortedPoints.begin(); pointIt != sortedPoints.end(); pointIt++) {

        sumX += (*pointIt).x;
        sumY += (*pointIt).y;
        sumZ += (*pointIt).z;
    }
    cv::Point3f center(sumX / sortedPoints.size(), sumY / sortedPoints.size(),
            sumZ / sortedPoints.size());

    _center = center;
}

Projection::Projection(Plane3d& p1, Plane3d& p2) {
    _planes.push_back(p1);
    _planes.push_back(p2);

    //Calculate the center
    std::vector<cv::Point3f> points;
    points.push_back(p1.getPoint(0));
    points.push_back(p1.getPoint(1));
    points.push_back(p1.getPoint(2));
    points.push_back(p1.getPoint(3));
    points.push_back(p2.getPoint(0));
    points.push_back(p2.getPoint(1));
    points.push_back(p2.getPoint(2));
    points.push_back(p2.getPoint(3));

    //Sort
    std::sort(points.begin(), points.end(), pointComparator);

    std::list<cv::Point3f> sortedPoints;

    std::vector<cv::Point3f>::iterator it;
    for (it = points.begin(); it != points.end(); it++) {
        sortedPoints.push_back(*it);
    }

    //Remove duplicates
    sortedPoints.unique();

    float sumX = 0.0;
    float sumY = 0.0;
    float sumZ = 0.0;
    std::list<cv::Point3f>::iterator ii;
    for (ii = sortedPoints.begin(); ii != sortedPoints.end(); ii++) {

        sumX += (*ii).x;
        sumY += (*ii).y;
        sumZ += (*ii).z;
    }
    cv::Point3f center(sumX / sortedPoints.size(), sumY / sortedPoints.size(),
            sumZ / sortedPoints.size());

    _center = center;

}

Projection::~Projection() {
}

cv::Point3f Projection::getCenter() {
    return _center;
}

std::vector<Plane3d> Projection::getPlanes() {
    return _planes;
}

