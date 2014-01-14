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

    nbHomographies = a.size();

    for(int i = 0; i < nbHomographies; i++){

        Plane planeA = a.at(i);
        Plane planeB = b.at(i);
        vector<Point2d> src;
        vector<Point2d> dst;

        src.push_back(planeA.getPoint(0));
        src.push_back(planeA.getPoint(1));
        src.push_back(planeA.getPoint(2));
        src.push_back(planeA.getPoint(3));

        dst.push_back(planeB.getPoint(0));
        dst.push_back(planeB.getPoint(1));
        dst.push_back(planeB.getPoint(2));
        dst.push_back(planeB.getPoint(3));

        Mat homography = findHomography(src, dst, CV_RANSAC);

        // Find the translation to keep image in the window
        Mat point1 = Mat(3,1,CV_64F);
        point1.at<double>(0,0) = planeA.getPoint(0).x;
        point1.at<double>(1,0) = planeA.getPoint(0).y;
        point1.at<double>(2,0) = 1;

        Mat point2 = Mat(3,1,CV_64F);
        point2.at<double>(0,0) = planeA.getPoint(1).x;
        point2.at<double>(1,0) = planeA.getPoint(1).y;
        point2.at<double>(2,0) = 1;

        Mat point3 = Mat(3,1,CV_64F);
        point3.at<double>(0,0) = planeA.getPoint(2).x;
        point3.at<double>(1,0) = planeA.getPoint(2).y;
        point3.at<double>(2,0) = 1;

        Mat point4 = Mat(3,1,CV_64F);
        point4.at<double>(0,0) = planeA.getPoint(3).x;
        point4.at<double>(1,0) = planeA.getPoint(3).y;
        point4.at<double>(2,0) = 1;

        Mat point1New = homography*point1;
        Mat point2New = homography*point2;
        Mat point3New = homography*point3;
        Mat point4New = homography*point4;

        /*Mat X = Mat(4,1, CV_64F);
        X.at<double>(0,0) = point1New.at<double>(0,0);
        X.at<double>(1,0) = point2New.at<double>(0,0);
        X.at<double>(2,0) = point3New.at<double>(0,0);
        X.at<double>(3,0) = point4New.at<double>(0,0);

        Mat Y = Mat(4,1, CV_64F);
        Y.at<double>(0,0) = point1New.at<double>(1,0);
        Y.at<double>(1,0) = point2New.at<double>(1,0);
        Y.at<double>(2,0) = point3New.at<double>(1,0);
        Y.at<double>(3,0) = point4New.at<double>(1,0);

        double xMin = 9999;

        for (int i=0; i<4; i++)
        {
            if (X.at<double>(i,0) < xMin)
                xMin = X.at<double>(i,0);
        }

        double yMin = 9999;

        for (int i=0; i<4; i++)
        {
            if (Y.at<double>(i,0) < yMin)
                yMin = Y.at<double>(i,0);
        }*/

        Mat pts;
        perspectiveTransform(src, pts, homography);

        double xMin = 9999;

        for (int i=0; i<8; i+=2)
        {
            //cout << pts.at<double>(i,0) << endl;
            if (pts.at<double>(0,i) < xMin)
                xMin = pts.at<double>(0,i);
        }

        double yMin = 9999;

        for (int i=1; i<8; i+=2)
        {
            //cout << pts.at<double>(0,i) << endl;
            if (pts.at<double>(0,i) < yMin)
                yMin = pts.at<double>(0,i);
        }

        homography.at<double>(0,2) -= xMin;
//        homography.at<double>(1,2) -= point3New.at<double>(1,0);
        homography.at<double>(1,2) -= yMin;
        cout << xMin << endl;
        cout << yMin << endl;
//        homography.at<double>(0,2) = 0;
//        homography.at<double>(1,2) = 0;

        //cout << X << endl;
        cout << "----------" << endl;
        cout << pts << endl;

        cout << "Homography:" << endl;
        cout << homography << endl;
        homographies.push_back(homography);

    }
    
}

vector<Mat> HomographyCalculator::applyTransformation(vector<Mat> images){

    vector<Mat> transformedImages;

    transformedImages.resize(nbHomographies);

    for (int i=0; i < nbHomographies; i++){
        warpPerspective(images.at(i), transformedImages.at(i), 
                homographies.at(i), Size(1920, 1080) );
    }

    return transformedImages;
}
