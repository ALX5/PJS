/* 
 * File:   HomographyCalculator.cpp
 * Author: bruno
 * 
 * Created on December 20, 2013, 6:19 PM
 */

#include "HomographyCalculator.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace cv;
using namespace std;
HomographyCalculator::HomographyCalculator() {
}

HomographyCalculator::HomographyCalculator(const HomographyCalculator& orig) {
}

HomographyCalculator::~HomographyCalculator() {
}

void HomographyCalculator::determineHomographies(vector<Plane> a, vector<Plane> b){

    assert(a.size() == b.size());

    for(int i = 0; i < a.size(); i++){
    
        Plane p1 = a.at(i);
        Plane p2 = b.at(i);
        vector<Point2f> src;
        vector<Point2f> dst;

        src.push_back(p1.getPoint(0));
        src.push_back(p1.getPoint(1));
        src.push_back(p1.getPoint(2));
        src.push_back(p1.getPoint(3));

        dst.push_back(p2.getPoint(0));
        dst.push_back(p2.getPoint(1));
        dst.push_back(p2.getPoint(2));
        dst.push_back(p2.getPoint(3));

        Mat m = findHomography(src, dst);
        cout << m << endl;
        m.at<double>(0,2) = 0;
        m.at<double>(1,2) = 0;
        cout << m.at<double>(0,2) << endl;
        cout << m.at<double>(1,2) << endl;
        
        
        //TODO Insert the homographies into the list elsewhere?
        //The interface is not intuitive. I think we should have a method
        //that finds the homography between each single pair and returns it
        homographies.push_back(m);

    }
    
}

vector<Mat> HomographyCalculator::applyTransformation(vector<Mat> images){
    
    vector<Mat> transformedImages;
    
    for(int i = 0; i < images.size(); i++){
        Mat newImg;
        Mat image = images.at(i);
        
        warpPerspective(image, newImg, homographies.at(i), Size(image.cols*2, image.rows*2));    
        transformedImages.push_back(newImg);
    }
    
    return transformedImages;
}