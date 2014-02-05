/* 
 * File:   AffineTests.cpp
 * Author: bruno
 * 
 * Created on February 5, 2014, 12:21 AM
 */

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "AffineTests.h"

AffineTests::AffineTests() {
}

AffineTests::AffineTests(const AffineTests& orig) {
}

AffineTests::~AffineTests() {
}

void AffineTests::testAffineTransform() {
    std::vector<cv::Point2f> src;
    std::vector<cv::Point2f> dst;
    src.push_back(cv::Point2f(0.0, 0.0));
    src.push_back(cv::Point2f(0.0, 10.0));
    src.push_back(cv::Point2f(10.0, 0.0));
    src.push_back(cv::Point2f(10.0, 10.0));
    
    
    /**
     * Translate (10.0, 0)
     */
    std::cout << "=================================" << std::endl;
    std::cout << "Test plane: " << std::endl;
    std::cout << src << std::endl << std::endl;
    cv::Mat tr10 = 
            (cv::Mat_<double>(2,3) << 1.0, 0.0, 10.0, 0.0, 1.0, 0.0);        
    
    cv::transform(src, dst, tr10);
    std::cout << "Translate (10,0): " << std::endl;
    std::cout << dst << std::endl << std::endl;
    
    /**
     * Translate (10.0, 5.0)
     */
    std::cout << "=================================" << std::endl;
    std::cout << "Test plane: " << std::endl;
    std::cout << src << std::endl << std::endl;
    cv::Mat tr10_5 = 
            (cv::Mat_<double>(2,3) << 1.0, 0.0, 10.0, 0.0, 1.0, 5.0);     
    
    cv::transform(src, dst, tr10_5);
    std::cout << "Translate (10,5): " << std::endl;
    std::cout << dst << std::endl << std::endl;
    
    
    /**
     * Translate (10.0, 0) in place
     */
    std::cout << "=================================" << std::endl;
    std::cout << "Test plane: " << std::endl;
    std::cout << dst << std::endl << std::endl;
        
    cv::transform(dst, dst, tr10);
    std::cout << "Translate (10,0) in place: " << std::endl;
    std::cout << dst << std::endl << std::endl;
    
    
    /**
     * Homography
     */
    std::cout << "=================================" << std::endl;
    std::cout << "Test plane: " << std::endl;
    std::cout << src << std::endl << std::endl;
        
    cv::Mat homography = 
        (cv::Mat_<double>(3,3) <<  0.61, -0.015, -9.94,
                                -0.31, -0.83, 7.15,
                                -0.0004839, 5.24e-05, 1);
    
    cv::perspectiveTransform(src, dst, homography);    
    std::cout << "Homography: " << std::endl;
    std::cout << homography  << std::endl;
    std::cout << "Result: " << std::endl;
    std::cout << dst << std::endl << std::endl;
    
    /**
     * Homography, then affine
     */
    std::cout << "=================================" << std::endl;
    std::cout << "Test plane: " << std::endl;
    std::cout << src << std::endl << std::endl;   
    
    std::cout << "Homography then translate (10, 0): " << std::endl;
    
    cv::perspectiveTransform(src, dst, homography);    
    cv::transform(dst, dst, tr10);    
    
    
    std::cout << "Result: " << std::endl;
    std::cout << dst << std::endl << std::endl;
    
    /**
     * Affine, then homography
     */
    std::cout << "=================================" << std::endl;
    std::cout << "Test plane: " << std::endl;
    std::cout << src << std::endl << std::endl;
           
    std::cout << "Translate (10, 0) then homography: " << std::endl;
    
    cv::transform(src, dst, tr10);    
    cv::perspectiveTransform(dst, dst, homography);    
    
    std::cout << "Result: " << std::endl;
    std::cout << dst << std::endl << std::endl;
    
    
}
