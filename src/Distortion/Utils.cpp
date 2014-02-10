/* 
 * File:   Utils.cpp
 * Author: bruno
 * 
 * Created on January 16, 2014, 1:29 PM
 */

#include <iostream>
#include <algorithm>
#include "Utils.h"
#include <stdio.h>
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/date_time/posix_time/posix_time_types.hpp>

//using namespace boost::posix_time;

Utils::Utils() {
}

Utils::Utils(const Utils& orig) {
}

Utils::~Utils() {
}

void Utils::addAlphaChannel(cv::Mat& image, Plane2d& plane) {

//    std::cout << "Adding alpha channel..." << std::endl;
    //ptime initTime = microsec_clock::local_time();
//    std::cout << plane << std::endl;

    int height = image.rows;
    int width = image.cols;
//    std::cout << width << ", " << height << std::endl;
    cv::Mat transparent(height, width, CV_8UC4);
    cv::Mat alphaMask(height, width, CV_8U, cv::Scalar(0.0));
    uchar *alphaPtr = alphaMask.ptr();

    //Get BB
    Plane2d bb = plane.getBoundingBox();
    int bbX = bb.getUpperLeftCorner().x;
    int bbY = bb.getUpperLeftCorner().y;
    int bbW = bb.getWidth();
    int bbH = bb.getHeight();

    //Initialize all alpha values to 0
    for (int row = 0; row < alphaMask.rows; row++) {
        for (int col = 0; col < alphaMask.cols; col++) {
            cv::Point2f p(col, row);
            *alphaPtr = 0;
            alphaPtr++;
        }
    }

    //***********************************************************
    //Assign an alpha value of 255 to the points inside the plane
    //***********************************************************
    
    //Initialize the pointer to the alpha mask
    alphaPtr = alphaMask.ptr();
    //Make it point to the top left corner of the bounding box of the plane
    alphaPtr += bbY * width + bbX;
    
    for (int row = bbY; row < bbH + bbY; row++) {
        for (int col = bbX; col < bbW + bbX; col++) {
            cv::Point2f p(col, row);
//                std::cout << row << ", " << col << std::endl;        
            if (plane.contains(p)) {
//                std::cout << "Doing it" << std::endl;
                *alphaPtr = 255;             
//                std::cout << "Did it" << std::endl;
            }

            alphaPtr++;
            
        }
        alphaPtr += (width - bbW);
    }

    cv::Mat srcImg[] = {image, alphaMask};
    int from_to[] = {0, 0, 1, 1, 2, 2, 3, 3};
    cv::mixChannels(srcImg, 2, &transparent, 1, from_to, 4);

    image = transparent;

    //ptime endTime = microsec_clock::local_time();

    //cout << "Total time: " << endTime - initTime << endl;

}

std::vector<cv::Mat> Utils::divideImageInTwo(cv::Mat& img) {

    std::vector<cv::Mat> images;

    int cols = img.cols;
    int firstHalfCols = (img.cols / 2);
    int rows = img.rows;

   cv:: Mat firstHalf(img.rows, firstHalfCols, IMG_UNIT);
    cv::Mat secondHalf(img.rows, img.cols - firstHalfCols, IMG_UNIT);

    uchar *fhPtr = firstHalf.ptr();
    uchar *shPtr = secondHalf.ptr();
    uchar *imgPtr = img.ptr();
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < firstHalfCols; col++) {
            for (int i = 0; i < img.channels(); i++) {
                *fhPtr++ = *imgPtr++;
            }

        }
        for (int col = 0; col < cols - firstHalfCols; col++) {
            for (int i = 0; i < img.channels(); i++) {
                *shPtr++ = *imgPtr++;
            }
        }
    }

    images.push_back(firstHalf);
    images.push_back(secondHalf);

    return images;
}

cv::Mat Utils::joinImagesAtMiddle(cv::Mat& img1, cv::Mat& img2) {

    assert(img1.rows == img2.rows && img1.cols == img2.cols);
    assert(img1.channels() == img2.channels());
    int cols = img1.cols;
    int halfCols = cols / 2;
    int rows = img1.rows;
    int channels = img1.channels();

    cv::Mat finalImage(img1.rows, img1.cols, CV_8UC4);
    uchar *fPtr = img1.ptr();
    uchar *sPtr = img2.ptr();
    uchar *iPtr = finalImage.ptr();

    sPtr += (img1.cols - halfCols) * channels;
    for (int row = 0; row < rows; row++) {
        int sw;
        for (int col = 0; col < halfCols; col++) {
            for (int i = 0; i < channels; i++) {
                *iPtr = *fPtr;
                iPtr++;
                fPtr++;
            }
            sw = col;
        }

        fPtr += halfCols*channels;
        for (int col = 0; col < cols - halfCols; col++) {
            for (int i = 0; i < channels; i++) {
                *iPtr = *sPtr;
                iPtr++;
                sPtr++;
            }
            sw = col;
        }

        sPtr += (img1.cols - halfCols) * channels;
    }

    return finalImage;
}

cv::Mat Utils::joinImagesAtMiddle(Surface &s1, Surface &s2) {
    cv::Mat im1 = s1.transformedImage;
    cv::Mat im2 = s2.transformedImage;

    return this->joinImagesAtMiddle(im1, im2);
}

//TODO Decouple this. This method demands a 4 channel image,
//but it might be useful for others
void Utils::writeToTimage(cv::Mat& src, cv::Mat& dst) {

    //The source image must fit into the destination image
    assert(src.cols <= dst.cols && src.rows <= dst.rows);

    //Source and destination must have the same number of channels
    //assert(src.channels() == 4 && dst.channels() == 4);


    uchar *srcPtr = src.ptr();
    uchar *dstPtr = dst.ptr();

    int diffCols = dst.cols - src.cols;
    int diffRows = dst.rows - src.rows;

    int rows = src.rows;
    int cols = src.cols;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
           // int alphaValue = src.at<cv::Vec4b>(row, col)[3];
            for (int i = 0; i < src.channels(); i++) {
                //if (alphaValue > 0) {
                    *dstPtr = *srcPtr;
               // }
                dstPtr++;
                srcPtr++;
            }
        }
        dstPtr += diffCols * src.channels();
    }

}

//TODO remove pointer syntax

cv::Mat Utils::getImageFromSurfaces(std::vector<Surface*> surfaces) {

    cv::Mat image(surfaces.at(0)->transformedImage.rows,
            surfaces.at(0)->transformedImage.cols, CV_8UC3);

    std::vector<Surface*>::iterator ii;
    for (ii = surfaces.begin(); ii != surfaces.end(); ii++) {
        this->writeToTimage((*ii)->transformedImage, image);
    }

    return image;
}

cv::Size Utils::getFinalSize(std::vector<Surface*> surfaces) {
    
    Plane2d p1 = surfaces.at(0)->transformedRegion;
    Plane2d p2 = surfaces.at(1)->transformedRegion;

    Plane2d bb = pjs::getBoundingBox(p1, p2);

    int maxWidth = bb.getWidth();
    int maxHeight = bb.getHeight();

    cv::Size size(maxWidth, maxHeight);

    return size;
}

namespace pjs{
    
    //TODO Incomplete
    cv::Size getScreenSize(){
        
        char *command="xrandr | grep '*'";
        FILE *fpipe = (FILE*)popen(command,"r");
        char line[256];
        while ( fgets( line, sizeof(line), fpipe))
        {
            std::cout << line << std::endl;
        }
        pclose(fpipe);

        cv::Size();
        
    }
}
