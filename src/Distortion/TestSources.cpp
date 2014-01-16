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

int TestSources::twoPlanesTest() {

    
    
    //**********************************************
    //                  Step 1
    //**********************************************
    //Get the coordinates of the projected planes
    //from the point of view of the user and find the 
    //homographies that correct their distortion
    //**********************************************
    vector<Plane> a;
    vector<Plane> b;

    //Distorted plane
    //Corrected plane 
    Plane p1(Point2f(0, 575), Point2f(70, 1290), Point2f(1050, 0), Point2f(1025, 990));
    Plane p2(Point2f(0, 0), Point2f(0, 1080), Point2f(960, 0), Point2f(960, 1080));

    a.push_back(p1);
    b.push_back(p2);

    //Distorted plane
    Plane p3(Point2f(25, 0), Point2f(0, 990), Point2f(1022, 168), Point2f(938, 1300));
    //Corrected plane
    Plane p4(Point2f(0, 0), Point2f(0, 1080), Point2f(960, 0), Point2f(960, 1080));

    a.push_back(p3);
    b.push_back(p4);

    //Calculate the homographies
    HomographyCalculator hc;
    hc.determineHomographies(a, b);

    vector<Mat> homographies = hc.getHomographies();

    
    //**********************************************
    //                  Step 2
    //**********************************************
    //Create planes that represent the projected 
    //images and apply the homographies to them
    //**********************************************
    
    vector<Plane> transformedPlanes;
    vector<Point2f> offsets;
    vector<Plane> untransformedPlanes;
    Plane provPlane(Point2f(0, 0), Point2f(0, 540), Point2f(480, 0), Point2f(480, 540));
    untransformedPlanes.push_back(provPlane);
    Plane provPlane2(Point2f(0, 0), Point2f(0, 540), Point2f(480, 0), Point2f(480, 540));
    untransformedPlanes.push_back(provPlane2);
    //Apply the homographies
    for (int i = 0; i < homographies.size(); i++) {
        Plane p = hc.transformPlane(untransformedPlanes.at(i), homographies.at(i));
        transformedPlanes.push_back(p);
    }

    //**********************************************
    //                  Step 3
    //**********************************************
    //Find how misplaced the planes are
    //The bounding box of the first one should be at the origin
    //The second one should be just by the first one
    //**********************************************
    
    Point2f origin(0, 0);
    Point2f offsetFirst = transformedPlanes.at(0).findBBOffset(origin);
    offsets.push_back(offsetFirst);

    //Move the BB of the first one to the origin so it's all within the image
    //(for now we're only manipulating the planes representing the images, not
    //the images themselves)
    transformedPlanes.at(0).moveBBToOrigin();   

    //Find how much do we need to move the second plane so it matches the first
    Point2f upperRightFirst = transformedPlanes.at(0).getPoint(2);
    Point2f offsetSecond = transformedPlanes.at(1).findOffset(upperRightFirst);
    offsets.push_back(offsetSecond);

    
    //**********************************************
    //                  Step 4
    //**********************************************
    //Load the image to apply the corresponding
    //transformations to it
    //**********************************************
    const char* nom1 = "../src/grid-straight2half.png";
    Mat img = imread(nom1, CV_LOAD_IMAGE_GRAYSCALE);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        return -1;
    }

    //Divide the image in two to apply the corresponding
    //homography to each part
    vector<Mat> images = this->divideImageInTwo(img);

    //Modify the homographies so they translate the planes 
    //as we want them to
    hc.adjustTranslations(offsets);
    //Apply the homographies
    vector<Mat> transformedImages = hc.applyTransformation(images);

    //***************************************************
    //***************************************************
    //***************************************************
    //          Still not in use, but will be
    //***************************************************
    //    Plane t1 = transformedPlanes.at(0);
    //    Plane t2 = transformedPlanes.at(1);
    //    Plane totalBB = p1.getBoundingBox(t1, t2);
    //    int imageWidth = totalBB.getPoint(2).x - totalBB.getPoint(0).x;
    //    int imageHeight = totalBB.getPoint(1).y - totalBB.getPoint(0).y;
    //***************************************************
    //***************************************************


    /*****************************************************
     * Show the images
     *****************************************************/
    int keyPressed = 0;
    imshow("First half", images.at(0));

    //TODO define constant for ESC key
    do {
        keyPressed = waitKey(0);
        cout << keyPressed << endl;
    } while (keyPressed != 27);

    imshow("Second half", images.at(1));
    keyPressed = 0;
    do {
        keyPressed = waitKey(0);
    } while (keyPressed != 27);

    for (int i = 0; i < transformedImages.size(); i++) {
        imshow("tr", transformedImages.at(i));
        keyPressed = 0;
        do {
            keyPressed = waitKey(0);
        } while (keyPressed != 27);
    }imwrite("test", transformedImages.at(0));



    /*****************************************************
     * FINAL IMAGE (far from perfect)
     *****************************************************/

    Mat finalImage = this->joinImagesAtMiddle(transformedImages.at(0), transformedImages.at(1));

    imshow("Final", finalImage);
    keyPressed = 0;
    do {
        keyPressed = waitKey(0);
    } while (keyPressed != 27);

    return 0;
}

vector<Mat> TestSources::divideImageInTwo(cv::Mat& img) {
        
    vector<Mat> images;
    
    int halfCols = img.cols / 2;
    Mat firstHalf(img.rows, halfCols, CV_8U);
    Mat secondHalf(img.rows, img.cols - halfCols, CV_8U);

    uchar *fhPtr = firstHalf.ptr();
    uchar *shPtr = secondHalf.ptr();
    uchar *imgPtr = img.ptr();
    for (int row = 0; row < img.rows; row++) {
        for (int col = 0; col < halfCols; col++) {
            *fhPtr = *imgPtr;
            fhPtr++;
            imgPtr++;
        }
        for (int col = 0; col < img.cols - halfCols; col++) {
            *shPtr = *imgPtr;
            shPtr++;
            imgPtr++;
            
        }
    }
    
    images.push_back(firstHalf);
    images.push_back(secondHalf);
    
    return images;
}

cv::Mat TestSources::joinImagesAtMiddle(cv::Mat& img1, cv::Mat& img2) {
    
    assert(img1.rows == img2.rows && img1.cols == img2.cols);
    
    int halfCols = img1.cols / 2;
    
    Mat finalImage(img1.rows, img1.cols, CV_8U);   
    uchar *fPtr = img1.ptr();
    uchar *sPtr = img2.ptr();
    uchar *iPtr = finalImage.ptr();
    sPtr += halfCols;
    for (int row = 0; row < img1.rows; row++) {
        for (int col = 0; col < halfCols; col++) {
            *iPtr = *fPtr;
            fPtr++;
            iPtr++;
        }
        fPtr += halfCols;
        for (int col = 0; col < img1.cols - halfCols; col++) {
            *iPtr = *sPtr;
            sPtr++;
            iPtr++;
        }
        sPtr += img1.cols - halfCols;
    }
    
    return finalImage;
}
