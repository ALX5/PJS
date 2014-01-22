/* 
 * File:   Utils.cpp
 * Author: bruno
 * 
 * Created on January 16, 2014, 1:29 PM
 */

#include "Utils.h"
#include <iostream>

using namespace std;
using namespace cv;

Utils::Utils() {
}

Utils::Utils(const Utils& orig) {
}

Utils::~Utils() {
}

void Utils::addAlphaChannel(Mat& image, Plane& plane) {

    int height = image.rows;
    int width = image.cols;

    Mat transparent(height, width, CV_8UC4);
    Mat alphaMask(height, width, CV_8U, Scalar(0.0));
    uchar *alphaPtr = alphaMask.ptr();

    //TODO Too slow! Find a faster method for adding an alpha channel
    //Hint: use BB. Everything outside it is left blank
    //Hint: crop before doing this
    for (int row = 0; row < alphaMask.rows; row++) {
        for (int col = 0; col < alphaMask.cols; col++) {
            uchar alphaValue;
            Point2f p(col, row);
            if (plane.contains(p)) {
                alphaValue = 255;
            } else {
                alphaValue = 0;
            }

            *alphaPtr = alphaValue;
            alphaPtr++;
        }
    }

    Mat srcImg[] = {image, alphaMask};
    int from_to[] = {0, 0, 1, 1, 2, 2, 3, 3};
    mixChannels(srcImg, 2, &transparent, 1, from_to, 4);

    image = transparent;        

}

vector<Mat> Utils::divideImageInTwo(cv::Mat& img) {

    vector<Mat> images;

    int cols = img.cols;
    int firstHalfCols = img.cols / 2;
    int rows = img.rows;

    Mat firstHalf(img.rows, firstHalfCols, IMG_UNIT);
    Mat secondHalf(img.rows, img.cols - firstHalfCols, IMG_UNIT);

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

    Mat finalImage(img1.rows, img1.cols, CV_8UC4);
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
    Mat im1 = s1.transformedImage;
    Mat im2 = s2.transformedImage;

    return this->joinImagesAtMiddle(im1, im2);
}

void Utils::writeToTimage(cv::Mat& src, cv::Mat& dst) {

    //The source image must fit into the destination image
    assert(src.cols <= dst.cols && src.rows <= dst.rows);
    
    //Source and destination must have the same number of channels
    assert(src.channels() == 4 && dst.channels() == 4);           

    
    uchar *srcPtr = src.ptr();
    uchar *dstPtr = dst.ptr();

    int diffCols = dst.cols - src.cols;
    int diffRows = dst.rows - src.rows;

    int rows = src.rows;
    int cols = src.cols;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int alphaValue = src.at<Vec4b>(row, col)[3];
            for (int i = 0; i < src.channels(); i++) {
                if (alphaValue > 0) {
                    *dstPtr = *srcPtr;
                }
                dstPtr++;
                srcPtr++;
            }
        }
        dstPtr += diffCols * 4;
    }

}

cv::Mat Utils::getImageFromSurfaces(std::vector<Surface*> surfaces) {
    
    Mat image(surfaces.at(0)->transformedImage.rows, 
            surfaces.at(0)->transformedImage.cols, CV_8UC4);
    
    for(int i = 0; i < surfaces.size(); i++){
        this->writeToTimage(surfaces.at(i)->transformedImage, image);        
    }
    
    return image;
    
}
