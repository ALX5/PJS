///* 
// * File:   TestSources.cpp
// * Author: bruno
// * 
// * Created on January 6, 2014, 11:58 AM
// */
//
//#include "TestSources.h"
//
//#include <cstdlib>
//#include <iostream>
//#include "HomographyCalculator.h"
//#include "Utils.h"
//
//using namespace std;
//
//#define IMG_UNIT CV_8UC3
//
//TestSources::TestSources() {
//}
//
//TestSources::TestSources(const TestSources& orig) {
//}
//
//TestSources::~TestSources() {
//}
//
//int TestSources::twoPlanesTest() {
//
//    
//    
//    //**********************************************
//    //                  Step 1
//    //**********************************************
//    //Get the coordinates of the projected planes
//    //from the point of view of the user and find the 
//    //homographies that correct their distortion
//    //**********************************************
//    vector<Plane> a;
//    vector<Plane> b;
//
//    //Distorted plane
//    //Corrected plane 
//    Plane p1(Point2f(0, 670), Point2f(92, 1396), Point2f(1266, 0), Point2f(1254, 1024));
//    Plane p2(Point2f(0, 0), Point2f(0, 1080), Point2f(960, 0), Point2f(960, 1080));
////    Plane p2(Point2f(0, 0), Point2f(0, 540), Point2f(576, 0), Point2f(576, 540));
//    a.push_back(p1);
//    b.push_back(p2);
//
//    //Distorted plane
////    Plane p3(Point2f(12, 0), Point2f(0, 1024), Point2f(928, 148), Point2f(840, 1306));
//      Plane p3(Point2f(306, 0), Point2f(294, 1024), Point2f(1222, 148), Point2f(1134, 1306));
//    //Corrected plane
//    Plane p4(Point2f(0, 0), Point2f(0, 1080), Point2f(960, 0), Point2f(960, 1080));
////    Plane p4(Point2f(0, 0), Point2f(0, 540), Point2f(384, 0), Point2f(384, 540));
//    a.push_back(p3);
//    b.push_back(p4);
//
//    //Calculate the homographies
//    HomographyCalculator hc;
//    hc.determineHomographies(a, b);
//
//    vector<Mat> homographies = hc.getHomographies();
//
//    
//    //**********************************************
//    //                  Step 2
//    //**********************************************
//    //Create planes that represent the projected 
//    //images and apply the homographies to them
//    //**********************************************
//    
//    vector<Plane> transformedPlanes;
//    vector<Point2f> offsets;
//    vector<Plane> untransformedPlanes;
////    Plane provPlane(Point2f(0, 0), Point2f(0, 1080), Point2f(1152, 0), Point2f(1152, 1080))
//    Plane provPlane(Point2f(0, 0), Point2f(0, 1080), Point2f(960, 0), Point2f(960, 1080));
//    untransformedPlanes.push_back(provPlane);
////    Plane provPlane2(Point2f(0, 0), Point2f(0, 1080), Point2f(768, 0), Point2f(768, 1080));
//    Plane provPlane2(Point2f(0, 0), Point2f(0, 1080), Point2f(960, 0), Point2f(960, 1080));
//    untransformedPlanes.push_back(provPlane2);
//    //Apply the homographies
//    for (int i = 0; i < homographies.size(); i++) {
//        Plane p = hc.transformPlane(untransformedPlanes.at(i), homographies.at(i));
//        transformedPlanes.push_back(p);
//    }
//
//    //**********************************************
//    //                  Step 3
//    //**********************************************
//    //Find how misplaced the planes are
//    //The bounding box of the first one should be at the origin
//    //The second one should be just by the first one
//    //**********************************************
//    
//    Point2f origin(0, 0);
//    Point2f offsetFirst = transformedPlanes.at(0).findBBOffset(origin);
//    offsets.push_back(offsetFirst);
//
//    //Move the BB of the first one to the origin so it's all within the image
//    //(for now we're only manipulating the planes representing the images, not
//    //the images themselves)
//    transformedPlanes.at(0).moveBBToOrigin();   
//
//    //Find how much do we need to move the second plane so it matches the first
//    Point2f upperRightFirst = transformedPlanes.at(0).getPoint(2);
//    Point2f offsetSecond = transformedPlanes.at(1).findOffset(upperRightFirst);
//    offsets.push_back(offsetSecond);
//    transformedPlanes.at(1).moveTo(upperRightFirst);
//
//    
//    //**********************************************
//    //                  Step 4
//    //**********************************************
//    //Load the image to apply the corresponding
//    //transformations to it
//    //**********************************************
//    const char* nom1 = "../src/grid-straight2.png";
//    Mat img = imread(nom1, CV_LOAD_IMAGE_COLOR);
//    if (!img.data) {
//        std::cout << " --(!) Error reading image" << std::endl;
//        return -1;
//    }
//
//    //Divide the image in two to apply the corresponding
//    //homography to each part
//    vector<Mat> images = this->divideImageInTwo(img);
//
//    //Modify the homographies so they translate the planes 
//    //as we want them to
//    hc.adjustTranslations(offsets);
//    //Apply the homographies
//    vector<Mat> transformedImages = hc.applyTransformation(images);
//
//    //***************************************************
//    //***************************************************
//    //***************************************************
//    //          Still not in use, but will be
//    //***************************************************
//    //    Plane t1 = transformedPlanes.at(0);
//    //    Plane t2 = transformedPlanes.at(1);
//    //    Plane totalBB = p1.getBoundingBox(t1, t2);
//    //    int imageWidth = totalBB.getPoint(2).x - totalBB.getPoint(0).x;
//    //    int imageHeight = totalBB.getPoint(1).y - totalBB.getPoint(0).y;
//    //***************************************************
//    //***************************************************
//
//
//    
//    
//    //**********************************************
//    //                  Step 5
//    //**********************************************
//    //Add the alpha channel to draw the planes only
//    //**********************************************    
//    Utils utils;
//    utils.addAlphaChannel(transformedImages.at(0), transformedPlanes.at(0));
//    utils.addAlphaChannel(transformedImages.at(1), transformedPlanes.at(1));
//    
//    /*****************************************************
//     * Show the images
//     *****************************************************/
//    int keyPressed = 0;
////    imshow("First half", images.at(0));
////
////    //TODO define constant for ESC key
////    do {
////        keyPressed = waitKey(0);
////        cout << keyPressed << endl;
////    } while (keyPressed != 27);
////
////    imshow("Second half", images.at(1));
////    keyPressed = 0;
////    do {
////        keyPressed = waitKey(0);
////    } while (keyPressed != 27);
//
//    imwrite("tr01.png", transformedImages.at(0));
//    imwrite("tr02.png", transformedImages.at(1));
//    
//    keyPressed = 0;
//    
//    for (int i = 0; i < transformedImages.size(); i++) {
//        imshow("tr", transformedImages.at(i));
//        keyPressed = 0;
//        do {
//            keyPressed = waitKey(0);
//        } while (keyPressed != 27);
//    }    
//
//
//    /*****************************************************
//     * FINAL IMAGE (far from perfect)
//     *****************************************************/
//
//    Mat finalImage(transformedImages.at(0).rows, transformedImages.at(0).cols, CV_8UC4, Scalar(0));
//    
//    this->writeToTimage(transformedImages.at(0), finalImage);
//    this->writeToTimage(transformedImages.at(1), finalImage);
//    
//    imwrite("alpha_image.png", finalImage);
//    
//    imshow("Final", finalImage);
//    keyPressed = 0;
//    do {
//        keyPressed = waitKey(0);
//    } while (keyPressed != 27);
//
//    return 0;
//}
//
//vector<Mat> TestSources::divideImageInTwo(cv::Mat& img) {
//    
//    vector<Mat> images;
//
//   
//    int cols = img.cols;
//    int firstHalfCols = 960;
//    int rows = img.rows;
//
//    cout << "SC: " << img.cols - firstHalfCols << endl;
//    
//    Mat firstHalf(img.rows, firstHalfCols, IMG_UNIT);
//    Mat secondHalf(img.rows, img.cols - firstHalfCols, IMG_UNIT);
//    
//    
//    
//    uchar *fhPtr = firstHalf.ptr();
//    uchar *shPtr = secondHalf.ptr();
//    uchar *imgPtr = img.ptr();
//    for (int row = 0; row < rows; row++) {
//        for (int col = 0; col < firstHalfCols; col++) {
//            for (int i = 0; i < img.channels(); i++) {
//                *fhPtr++ = *imgPtr++;
//            }
//
//        }       
//        for (int col = 0; col < cols - firstHalfCols; col++) {
//            for (int i = 0; i < img.channels(); i++) {
//                *shPtr++ = *imgPtr++;
//            }
//        }
//    }
//    
//    images.push_back(firstHalf);
//    images.push_back(secondHalf);
//    
//    return images;
//}
//
//cv::Mat TestSources::joinImagesAtMiddle(cv::Mat& img1, cv::Mat& img2) {
//    
//    assert(img1.rows == img2.rows && img1.cols == img2.cols);
//
//    int cols = img1.cols;
//    int halfCols = cols / 2;
//    int rows = img1.rows;
//
//    Mat finalImage(img1.rows, img1.cols, IMG_UNIT);
//    uchar *fPtr = img1.ptr();
//    uchar *sPtr = img2.ptr();
//    uchar *iPtr = finalImage.ptr();
//    sPtr += (img1.cols * 3 - halfCols * 3);
//    ;
//    for (int row = 0; row < rows; row++) {
//        for (int col = 0; col < halfCols; col++) {
//            for (int i = 0; i < img1.channels(); i++) {
//                *iPtr++ = *fPtr++;
//            }
//        }
//        fPtr += halfCols * 3;
//        for (int col = 0; col < cols - halfCols; col++) {
//            for (int i = 0; i < img1.channels(); i++) {
//                *iPtr++ = *sPtr++;
//            }
//        }
//        sPtr += (img1.cols * 3 - halfCols * 3);
//    }
//
//    return finalImage;
//}
//
//void TestSources::writeToTimage(cv::Mat& src, cv::Mat& dst) {
//       
//    //The source image must fit into the destination image
//    assert (src.cols <= dst.cols && src.rows <= dst.rows);
//    
//    //Source and destination must have the same number of channels
//    assert(src.channels() == 4 && dst.channels() == 4);
//    
//    uchar *srcPtr = src.ptr();
//    uchar *dstPtr = dst.ptr();
//    
//    int diffCols = dst.cols - src.cols;
//    int diffRows = dst.rows - src.rows;
//    
//    int rows = src.rows;
//    int cols = src.cols;
//    
//    for (int row = 0; row < rows; row++) {
//        for (int col = 0; col < cols; col++) {
//            int alphaValue = src.at<Vec4b>(row, col)[3];
//            for (int i = 0; i < src.channels(); i++) {
//                if(alphaValue > 0){                                    
//                    *dstPtr = *srcPtr;
//                } 
//                dstPtr++;
//                srcPtr++;       
//            }
//        }
//        dstPtr += diffCols * 4;      
//    }  
//    
//}
