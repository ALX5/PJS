/* 
 * File:   Utils.h
 * Author: bruno
 *
 * Created on January 16, 2014, 1:29 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "Plane2d.h"
#include "Surface.h"

#define IMG_UNIT CV_8UC3

class Utils {
public:
    Utils();
    Utils(const Utils& orig);
    virtual ~Utils();

    void addAlphaChannel(cv::Mat&, Plane2d&);
    std::vector<cv::Mat> divideImageInTwo(cv::Mat& img);
    cv::Mat joinImagesAtMiddle(cv::Mat& img1, cv::Mat& img2);
    cv::Mat joinImagesAtMiddle(Surface& s1 , Surface& s2);
    void writeToTimage(cv::Mat& src, cv::Mat& dst);
    cv::Mat getImageFromSurfaces(std::vector<Surface*> surfaces);
    cv::Size getFinalSize(std::vector<Surface*>);
    
private:

};

#endif	/* UTILS_H */

