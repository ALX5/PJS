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

        Plane p1 = a.at(i);
        Plane p2 = b.at(i);
        vector<Point2d> src;
        vector<Point2d> dst;

        src.push_back(p1.getPoint(0));
        src.push_back(p1.getPoint(1));
        src.push_back(p1.getPoint(2));
        src.push_back(p1.getPoint(3));

        dst.push_back(p2.getPoint(0));
        dst.push_back(p2.getPoint(1));
        dst.push_back(p2.getPoint(2));
        dst.push_back(p2.getPoint(3));

        Mat H = findHomography(src, dst, CV_RANSAC);

        // Find the translation to keep image in the window
        Mat P1 = Mat(3,1,CV_64F);
        P1.at<double>(0,0) = p1.getPoint(0).x;
        P1.at<double>(1,0) = p1.getPoint(0).y;
        P1.at<double>(2,0) = 1;

        Mat P2 = Mat(3,1,CV_64F);
        P2.at<double>(0,0) = p1.getPoint(1).x;
        P2.at<double>(1,0) = p1.getPoint(1).y;
        P2.at<double>(2,0) = 1;

        Mat P3 = Mat(3,1,CV_64F);
        P3.at<double>(0,0) = p1.getPoint(2).x;
        P3.at<double>(1,0) = p1.getPoint(2).y;
        P3.at<double>(2,0) = 1;

        Mat P4 = Mat(3,1,CV_64F);
        P4.at<double>(0,0) = p1.getPoint(3).x;
        P4.at<double>(1,0) = p1.getPoint(3).y;
        P4.at<double>(2,0) = 1;

        Mat P1New = H*P1;
        Mat P2New = H*P2;
        Mat P3New = H*P3;
        Mat P4New = H*P4;

        /*Mat X = Mat(4,1, CV_64F);
        X.at<double>(0,0) = P1New.at<double>(0,0);
        X.at<double>(1,0) = P2New.at<double>(0,0);
        X.at<double>(2,0) = P3New.at<double>(0,0);
        X.at<double>(3,0) = P4New.at<double>(0,0);

        Mat Y = Mat(4,1, CV_64F);
        Y.at<double>(0,0) = P1New.at<double>(1,0);
        Y.at<double>(1,0) = P2New.at<double>(1,0);
        Y.at<double>(2,0) = P3New.at<double>(1,0);
        Y.at<double>(3,0) = P4New.at<double>(1,0);

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
        perspectiveTransform(src,pts, H);

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

        H.at<double>(0,2) -= xMin;
        H.at<double>(1,2) -= P3New.at<double>(1,0);

        //cout << X << endl;
        cout << "----------" << endl;
        cout << pts << endl;

        homographies.push_back(H);

    }

}

vector<Mat> HomographyCalculator::applyTransformation(Mat image){

    vector<Mat> transformedImages;

    //cout << homographies.at(0) << endl;
    transformedImages.resize(nbHomographies);

    for (int i=0; i<nbHomographies; i++)
    {
        warpPerspective(image, transformedImages.at(i), homographies.at(i), Size(500, 500), WARP_INVERSE_MAP);

    }

    return transformedImages;
}
