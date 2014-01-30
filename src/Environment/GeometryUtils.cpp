/* 
 * File:   GeometryUtils.cpp
 * Author: bruno
 * 
 * Created on January 30, 2014, 10:33 AM
 */

#include <opencv2/opencv.hpp>
#include "GeometryUtils.h"

GeometryUtils::GeometryUtils() {
}

GeometryUtils::GeometryUtils(const GeometryUtils& orig) {
}

GeometryUtils::~GeometryUtils() {
}

//TODO optimize
cv::Point3f GeometryUtils::rotateAroundAxis(const cv::Point3f &vect, const cv::Point3f &axis, 
        const double &theta) {
    //Build the rotation matrix
    double u = axis.x;
    double v = axis.y;
    double w = axis.z;

    cv::Mat rotMatrix(4, 4, CV_64F);
    rotMatrix.at<double>(0) = (u * u + (1 - u * u) * std::cos(theta));
    rotMatrix.at<double>(1) = (u * v * (1 - std::cos(theta)) + w * std::sin(theta));
    rotMatrix.at<double>(2) = (u * w * (1 - std::cos(theta)) - v * std::sin(theta));
    rotMatrix.at<double>(3) = (0);

    rotMatrix.at<double>(4) = (u * v * (1 - std::cos(theta)) - w * std::sin(theta));
    rotMatrix.at<double>(5) = (v * v + (1 - v * v) * std::cos(theta));
    rotMatrix.at<double>(6) = (v * w * (1 - std::cos(theta)) + u * std::sin(theta));
    rotMatrix.at<double>(7) = (0);

    rotMatrix.at<double>(8) = (u * w * (1 - std::cos(theta)) + v * std::sin(theta));
    rotMatrix.at<double>(9) = (v * w * (1 - std::cos(theta)) - u * std::sin(theta));
    rotMatrix.at<double>(10) = (w * w + (1 - w * w) * std::cos(theta));
    rotMatrix.at<double>(11) = (0);

    rotMatrix.at<double>(12) = (0);
    rotMatrix.at<double>(13) = (0);
    rotMatrix.at<double>(14) = (1);
    rotMatrix.at<double>(15) = (0);


    cv::Point3f result;
    result.x = rotMatrix.at<double>(0) * vect.x +
            rotMatrix.at<double>(1) * vect.y +
            rotMatrix.at<double>(2) * vect.z +
            rotMatrix.at<double>(3);
    result.y = rotMatrix.at<double>(4) * vect.x +
            rotMatrix.at<double>(5) * vect.y +
            rotMatrix.at<double>(6) * vect.z +
            rotMatrix.at<double>(7);
    result.z = rotMatrix.at<double>(8) * vect.x +
            rotMatrix.at<double>(9) * vect.y +
            rotMatrix.at<double>(10) * vect.z +
            rotMatrix.at<double>(11);

    return result;
    
}

//TODO optimize
cv::Point3f GeometryUtils::normalizeVector(const cv::Point3f& vect) {
    
    double normalLength = std::pow(vect.x, 2) + std::pow(vect.y, 2) 
    + std::pow(vect.z, 2);
    
    cv::Point3f normalized(vect.x/normalLength, 
            vect.y/normalLength, 
            vect.z/normalLength);
    
    return normalized;    
}

cv::Point3f GeometryUtils::crossProduct(const cv::Point3f& vectA, const cv::Point3f& vectB) {
    
    cv::Point3f cross;
    cross.x = vectA.y*vectB.z - vectB.y*vectA.z;
    cross.y = vectB.x*vectA.z - vectA.x*vectB.z;
    cross.z = vectA.x*vectB.y - vectA.y*vectB.x; 

    return cross;
}


