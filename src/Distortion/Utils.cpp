/* 
 * File:   Utils.cpp
 * Author: bruno
 * 
 * Created on January 16, 2014, 1:29 PM
 */

#include "Utils.h"

using namespace cv;

Utils::Utils() {
}

Utils::Utils(const Utils& orig) {
}

Utils::~Utils() {
}

void Utils::addAlphaChannel(Mat& image) {

    int height = image.rows;
    int width = image.cols;
    
    Mat transparent( height, width, CV_8UC4);
    Mat alphaMask(height, width, CV_8U, Scalar(123.0));
    Mat srcImg[] = {image, alphaMask};
    int from_to[] = { 0,0, 1,1, 2,2, 3,3 };
    mixChannels( srcImg, 2, &transparent, 1, from_to, 4 );
    
    image = transparent;
    
}
