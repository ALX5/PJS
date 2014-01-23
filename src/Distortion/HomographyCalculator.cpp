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
#include "Surface.h"
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
//TODO deprecated
void HomographyCalculator::determineHomographies(const Plane &planeA, const Plane &planeB) {

        vector<Point2f> src;
        vector<Point2f> dst;

        src.push_back(planeA.getPoint(0));
        src.push_back(planeA.getPoint(1));
        src.push_back(planeA.getPoint(2));
        src.push_back(planeA.getPoint(3));

        dst.push_back(planeB.getPoint(0));
        dst.push_back(planeB.getPoint(1));
        dst.push_back(planeB.getPoint(2));
        dst.push_back(planeB.getPoint(3));

        Mat homography = findHomography(src, dst, CV_RANSAC);
//        surface.setHomography(homography);
}

vector<Mat> HomographyCalculator::applyTransformation(vector<Mat> images) {

    vector<Mat> transformedImages;
    transformedImages.resize(nbHomographies);

    for (int i = 0; i < nbHomographies; i++) {

        //TODO Size cannot be an attribute of this class
        //For the moment, I'll hard code it for testing, but each fraction
        //of the image should be represented by a class that stores its 
        //characteristics, including the size of the bounding box
        warpPerspective(images.at(i), transformedImages.at(i),
                homographies.at(i), Size(2160, 1920));
    }

    return transformedImages;
}

Plane HomographyCalculator::transformPlane(Plane& plane, Mat& homography) {

    vector<Point2f> src;
    vector<Point2f> dst;

    src.push_back(plane.getPoint(0));
    src.push_back(plane.getPoint(1));
    src.push_back(plane.getPoint(2));
    src.push_back(plane.getPoint(3));

    perspectiveTransform(src, dst, homography);

    Plane newPlane(dst);

    Plane boundingBox = newPlane.getBoundingBox();

    size = boundingBox.getSize();

    return newPlane;

}

//TODO Find out if this is fast enough.

void HomographyCalculator::moveImage(Mat &image, Point2f &p) {
    Mat homography(3, 3, CV_32F, Scalar(0));
    homography.at<float>(0, 2) = 0;
    homography.at<float>(1, 2) = 0;

    warpPerspective(image, image,
            homography, size);
}

void HomographyCalculator::adjustTranslations(vector<Point2f>& offsets) {
    assert(offsets.size() == homographies.size());

    for (int i = 0; i < offsets.size(); i++) {
        Mat *h = &(homographies.at(i));
        h->at<double>(0, 2) -= offsets.at(i).x;
        h->at<double>(1, 2) -= offsets.at(i).y;
    }
}

vector<Mat> HomographyCalculator::getHomographies() {
    return homographies;
}



