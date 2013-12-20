/* 
 * File:   main.cpp
 * Author: bruno
 *
 * Created on December 20, 2013, 9:02 PM
 */

#include <cstdlib>
#include <iostream>
#include "HomographyCalculator.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    //Define the planes. The first one represents the distorted image.
    //The second one represents the points where the first plane should sit
    Plane p1(Point2f(300,25), Point2f(300,512), Point2f(600,85), Point2f(600,450));
    Plane p2(Point2f(300,35), Point2f(300,512), Point2f(600,25), Point2f(600,515));
    
    //Put the planes in vectors
    //The homography calculator takes plane vectors
    //in order to apply different transformations to different regions
    vector<Plane> a;
    a.push_back(p1);
    vector<Plane> b;
    b.push_back(p2);
    
    //Calculate the homography
    HomographyCalculator hc;    
    hc.determineHomographies(a, b);
    
    //Load the image
    const char* nom1 = "grid-rot.png";
    Mat img = imread(nom1, CV_LOAD_IMAGE_GRAYSCALE);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        return -1;
    }
    
    //Get the transformed image
    vector<Mat> transformedImages = hc.applyTransformation(img);
    
    //And show it
    imshow("Transformed image", transformedImages.at(0));
    
    waitKey(0);
    
    return 0;
}

