/* 
 * File:   Surface.cpp
 * Author: bruno
 * 
 * Created on January 20, 2014, 4:22 PM
 */

#include "Surface.h"
#include "Utils.h"
#include <iostream>

using namespace std;

Surface::Surface() {
}

Surface::Surface(const Surface& orig) {
}

Surface::~Surface() {
}

Surface::Surface(Plane& src, Plane& dst, Mat image) {
    this->sourcePlane = src;
    this->destinationPlane = dst;
    this->image = image;

    this->determineHomography();
    this->calculateTransformedPlane();
}

void Surface::determineHomography() {
    vector<Point2f> src;
    vector<Point2f> dst;

    src.push_back(sourcePlane.getPoint(0));
    src.push_back(sourcePlane.getPoint(1));
    src.push_back(sourcePlane.getPoint(2));
    src.push_back(sourcePlane.getPoint(3));

    dst.push_back(destinationPlane.getPoint(0));
    dst.push_back(destinationPlane.getPoint(1));
    dst.push_back(destinationPlane.getPoint(2));
    dst.push_back(destinationPlane.getPoint(3));

    homography = findHomography(src, dst, CV_RANSAC);    
}

void Surface::calculateTransformedPlane() {
    vector<Point2f> src;
    vector<Point2f> dst;

    src.push_back(destinationPlane.getPoint(0));
    src.push_back(destinationPlane.getPoint(1));
    src.push_back(destinationPlane.getPoint(2));
    src.push_back(destinationPlane.getPoint(3));

    perspectiveTransform(src, dst, homography);

    transformedRegion = Plane(dst);

    Plane boundingBox = transformedRegion.getBoundingBox();

    size = boundingBox.getSize();

}

void Surface::adjustTranslations(Point2f &offset) {
    homography.at<double>(0, 2) -= offset.x;
    homography.at<double>(1, 2) -= offset.y;
}

//TODO get right size
//It is like this right now because the second half needs to be
//located to the right
void Surface::applyHomography() {    
    warpPerspective(image, transformedImage,
            homography, Size(2000,2000));
}

//TODO this should store the offset but not apply it
//All planes' BBs should be located at (0,0), and then written on
//the final image according to their offset
void Surface::correctPosition(Point2f& point) {
    Point2f offset = transformedRegion.findOffset(point);
    this->adjustTranslations(offset);
    this->calculateTransformedPlane();
}

void Surface::correctBBPosition(Point2f& point) {
    Point2f offset = transformedRegion.findBBOffset(point);
    this->adjustTranslations(offset);
    this->calculateTransformedPlane();
}

void Surface::display() {
    this->display("");
}


void Surface::display(const char *name) {
    int keyPressed = 0;
    imshow(name, transformedImage);
    do {
        keyPressed = waitKey(0);
        cout << keyPressed << endl;
    } while (keyPressed != 27);
    
    this->print(name);    
}

Point2f Surface::getUpperLeftCorner() {
    return transformedRegion.getUpperLeftCorner();
}

Point2f Surface::getLowerRightCorner() {
    return transformedRegion.getUpperRightCorner();
}

Point2f Surface::getUpperRightCorner() {
    return transformedRegion.getUpperRightCorner();
}

Point2f Surface::getLowerLeftCorner() {
    return transformedRegion.getLowerLeftCorner();
}

void Surface::addTransparency() {
    Utils utils;
    utils.addAlphaChannel(transformedImage, transformedRegion);
}

Size Surface::getSize() {
    return size;
}

void Surface::print() {
    this->print("Surface");
}


void Surface::print(const char *name) {
    cout << endl << "========= " << name << " =========" << endl;
    cout << "Source image: " << endl;
    cout << "\tChannels: " << image.channels() << endl;
    cout << "\trows: " << image.rows << endl;
    cout << "\tcols: " << image.cols << endl;
    cout << "Transformed image: " << endl;
    cout << "\tChannels: " << transformedImage.channels() << endl;
    cout << "\trows: " << transformedImage.rows << endl;
    cout << "\tcols: " << transformedImage.cols << endl;
    cout << "Source plane: " << endl;
    cout << sourcePlane << endl;
    cout << "Destination plane: " << endl;
    cout << destinationPlane << endl;
    cout << "Transformed plane: " << endl;
    cout << transformedRegion << endl;
    cout << "Homography: " << endl;
    cout << homography << endl;
    cout << endl << "===========================" << endl << endl;
}

void Surface::save() {
    this->save("image.png");
}

void Surface::save(const char *name) {
    imwrite(name, transformedImage);
}
