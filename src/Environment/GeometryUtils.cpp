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

cv::Point3f GeometryUtils::rotateAroundAxis(const cv::Vec3f &vect, const cv::Vec3f &axis,
        const double &theta) {
    //Build the rotation matrix
    double u = axis[0];
    double v = axis[1];
    double w = axis[2];

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
    rotMatrix.at<double>(14) = (0);
    rotMatrix.at<double>(15) = (1);


    cv::Point3f result;
    result.x = rotMatrix.at<double>(0) * vect[0] +
            rotMatrix.at<double>(1) * vect[1] +
            rotMatrix.at<double>(2) * vect[2] +
            rotMatrix.at<double>(3);
    result.y = rotMatrix.at<double>(4) * vect[0] +
            rotMatrix.at<double>(5) * vect[1] +
            rotMatrix.at<double>(6) * vect[2] +
            rotMatrix.at<double>(7);
    result.z = rotMatrix.at<double>(8) * vect[0] +
            rotMatrix.at<double>(9) * vect[1] +
            rotMatrix.at<double>(10) * vect[2] +
            rotMatrix.at<double>(11);

    return result;

}

//TODO optimize

cv::Vec3f GeometryUtils::normalizeVector(const cv::Vec3f& vect) {

    double normalLength = std::sqrt(std::pow(vect[0], 2) + std::pow(vect[1], 2)
            + std::pow(vect[2], 2));

    cv::Point3f normalized(vect[0] / normalLength,
            vect[1] / normalLength,
            vect[2] / normalLength);

    return normalized;
}

//TODO optimize

cv::Vec3f GeometryUtils::crossProduct(const cv::Vec3f& vectA, const cv::Vec3f& vectB) {

    cv::Vec3f cross;
    cross[0] = vectA[1] * vectB[2] - vectB[1] * vectA[2];
    cross[1] = vectB[0] * vectA[2] - vectA[0] * vectB[2];
    cross[2] = vectA[0] * vectB[1] - vectA[1] * vectB[0];

    return cross;
}

//TODO optimize

cv::Point3f GeometryUtils::intersection(const cv::Vec3f &ray,
        const cv::Point3f& normal, const cv::Point3f& point) {
    double num = -normal.dot(point);
    double den = normal.dot(ray);
    double t = num / den;
    cv::Point3f intersection(t * ray[0], t * ray[1], t * ray[2]);

    return intersection;
}
