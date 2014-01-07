/* 
 * File:   TestSources.cpp
 * Author: bruno
 * 
 * Created on January 6, 2014, 11:58 AM
 */

#include "TestSources.h"

#include <cstdlib>
#include <iostream>
#include "HomographyCalculator.h"

using namespace std;

TestSources::TestSources() {
}

TestSources::TestSources(const TestSources& orig) {
}

TestSources::~TestSources() {
}

int TestSources::singlePlaneTest() {

    //Define the planes. The first one represents the distorted image.
    //The second one represents the points where the first plane should sit
    Plane p1(Point2f(300, 25), Point2f(300, 512), Point2f(600, 85), Point2f(600, 450));
    Plane p2(Point2f(300, 100), Point2f(300, 400), Point2f(600, 100), Point2f(600, 400));

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
    vector<Mat> images;
    images.push_back(img);

    //Get the transformed image
    vector<Mat> transformedImages = hc.applyTransformation(images);

    //And show it
    imshow("Transformed image", transformedImages.at(0));

    waitKey(0);

    return 0;

}

int TestSources::createImageTest() {

    //Load the image
    const char* nom1 = "grid-straight.png";
    Mat img = imread(nom1, CV_LOAD_IMAGE_GRAYSCALE);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        return -1;
    }

    int halfCols = img.cols / 2;

    Mat firstHalf(img.rows, halfCols, CV_8U);
    Mat secondHalf(img.rows, img.cols - halfCols, CV_8U);

    uchar *fhPtr = firstHalf.ptr();
    uchar *shPtr = secondHalf.ptr();
    uchar *imgPtr = img.ptr();
    for (int row = 0; row < img.rows; row++) {
        for (int col = 0; col < halfCols; col++) {
            //*(firstHalf.ptr(col+row*img.cols)) = *(img.ptr(col+row*img.cols));
            *fhPtr = *imgPtr;
            //   cout << *fhPtr << endl;
            fhPtr++;
            imgPtr++;
        }
        for (int col = 0; col < img.cols - halfCols; col++) {
            //*(firstHalf.ptr(col+row*img.cols)) = *(img.ptr(col+row*img.cols));
            *shPtr = *imgPtr;
            //   cout << *fhPtr << endl;
            shPtr++;
            imgPtr++;
        }
    }

    imshow("First half", firstHalf);
    imshow("Second half", secondHalf);

    waitKey(0);

    return 0;



}

int TestSources::twoPlanesTest() {


    vector<Plane> a;
    vector<Plane> b;

    Plane p1(Point2f(300, 110), Point2f(310, 290), Point2f(495, 138), Point2f(500, 309));
    Plane p2(Point2f(400, 120), Point2f(400, 275), Point2f(500, 120), Point2f(500, 275));


    a.push_back(p1);
    b.push_back(p2);

    Plane p3(Point2f(495, 138), Point2f(500, 309), Point2f(616, 122), Point2f(608, 333));
    Plane p4(Point2f(500, 120), Point2f(500, 275), Point2f(600, 120), Point2f(600, 275));

    a.push_back(p3);
    b.push_back(p4);


    //Calculate the homography
    HomographyCalculator hc;
    hc.determineHomographies(a, b);


    const char* nom1 = "grid-straight.png";
    Mat img = imread(nom1, CV_LOAD_IMAGE_GRAYSCALE);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        return -1;
    }

    int halfCols = img.cols / 2;

    Mat firstHalf(img.rows, halfCols, CV_8U);
    Mat secondHalf(img.rows, img.cols - halfCols, CV_8U);

    uchar *fhPtr = firstHalf.ptr();
    uchar *shPtr = secondHalf.ptr();
    uchar *imgPtr = img.ptr();
    for (int row = 0; row < img.rows; row++) {
        for (int col = 0; col < halfCols; col++) {
            //*(firstHalf.ptr(col+row*img.cols)) = *(img.ptr(col+row*img.cols));
            *fhPtr = *imgPtr;
            //   cout << *fhPtr << endl;
            fhPtr++;
            imgPtr++;
        }
        for (int col = 0; col < img.cols - halfCols; col++) {
            //*(firstHalf.ptr(col+row*img.cols)) = *(img.ptr(col+row*img.cols));
            *shPtr = *imgPtr;
            //   cout << *fhPtr << endl;
            shPtr++;
            imgPtr++;
        }
    }


    vector<Mat> images;
    images.push_back(firstHalf);
    images.push_back(secondHalf);

    //Get the transformed images
    vector<Mat> transformedImages = hc.applyTransformation(images);



    imshow("First half", firstHalf);
    
    //TODO define constant for ESC key
    int keyPressed = 0;
    do {
        keyPressed = waitKey(0);
    } while (keyPressed != 1048603);
    
    imshow("Second half", secondHalf);
    keyPressed = 0;
    do {
        keyPressed = waitKey(0);
    } while (keyPressed != 1048603);

    for (int i = 0; i < transformedImages.size(); i++) {
        imshow("tr", transformedImages.at(i));
        keyPressed = 0;
        do {
            keyPressed = waitKey(0);
        } while (keyPressed != 1048603);
    }



    return 0;
}
