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

    /**
     * Adds an alpha channel to the image. Pixels outside the given region of 
     * interest are assigned an alpha value of 0. Those inside
     * are assigned an alpha value of 255.
     * @param 
     * @param 
     */
    void addAlphaChannel(cv::Mat& image, Plane2d& roi);
    
    /**
     * Divides the given image by the middle in to equal parts
     * @param img
     * @return Two images, of which each contains one half 
     * of the original image
     */
    std::vector<cv::Mat> divideImageInTwo(cv::Mat& img);
    
    /**
     * Divides the given image in two, at the given point from the middle.
     * e.g: if the image is 500 pixels wide and offset=100, then the image
     * is divided at vertical 350
     * @param img
     * @param offset
     * @return Two images containing their corresponding part
     */
    std::vector<cv::Mat> divideImageInTwo(cv::Mat& img, int offset);
    
    /**
     * Takes two images and joins them at the middle. 
     * i.e: If image 1 is 1234 and image 2 is 5678, the resulting image
     * will be 1278. One half of both images is thus lost. 
     * The images must be equal in size and must have the same number of
     * channels
     * @param img1
     * @param img2
     * @return 
     */
    cv::Mat joinImagesAtMiddle(cv::Mat& img1, cv::Mat& img2);
    
    /**
     * Same as joinImagesAtMiddle(cv::Mat& img1, cv::Mat& img2) but taking
     * surfaces as parameters
     * @param s1
     * @param s2
     * @return 
     */
    cv::Mat joinImagesAtMiddle(Surface& s1 , Surface& s2);
    
    /**
     * Copies src into dst. Note: the purpose of this function is to 
     * have the ability to copy only visible parts of an image (determined 
     * by their alpha value) into another. That functionality is however not
     * present at the moment.
     * @param src
     * @param dst
     */
    void writeToTimage(cv::Mat& src, cv::Mat& dst);
    
    /**
     * Generates an image based on the information available in the
     * given surfaces. Note: for the moment, this is limited to two surfaces
     * @param surfaces
     * @return 
     */
    cv::Mat getImageFromSurfaces(std::vector<Surface*> surfaces);
    
    /**
     * Calculates the size of the bounding box surrounding the given surfaces
     * @param 
     * @return 
     */
    cv::Size getFinalSize(std::vector<Surface*>);
    
    
    
private:

};

namespace pjs{
    cv::Size getScreenSize();
    cv::Point2f average(std::vector<cv::Point2f> points);
}

#endif	/* UTILS_H */

