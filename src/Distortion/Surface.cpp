/* 
 * File:   Surface.cpp
 * Author: bruno
 * 
 * Created on January 20, 2014, 4:22 PM
 */

#include "Surface.h"
#include "Utils.h"
#include <iostream>


Surface::Surface() {
}

Surface::Surface(const Surface& orig) {
}

Surface::~Surface() {
}

Surface::Surface(Plane2d& src, Plane2d& dst, cv::Mat image) {
    this->sourcePlane = src;
    this->destinationPlane = dst;
    this->image = image;

    this->determineHomography();
    this->calculateTransformedPlane();
}

void Surface::determineHomography() {
    std::vector<cv::Point2f> src;
    std::vector<cv::Point2f> dst;

    src.push_back(sourcePlane.getPoint(0));
    src.push_back(sourcePlane.getPoint(1));
    src.push_back(sourcePlane.getPoint(2));
    src.push_back(sourcePlane.getPoint(3));

    dst.push_back(destinationPlane.getPoint(0));
    dst.push_back(destinationPlane.getPoint(1));
    dst.push_back(destinationPlane.getPoint(2));
    dst.push_back(destinationPlane.getPoint(3));

    homography = cv::findHomography(src, dst, CV_RANSAC);    
}

void Surface::calculateTransformedPlane() {
    std::vector<cv::Point2f> src;
    std::vector<cv::Point2f> dst;

    src.push_back(destinationPlane.getPoint(0));
    src.push_back(destinationPlane.getPoint(1));
    src.push_back(destinationPlane.getPoint(2));
    src.push_back(destinationPlane.getPoint(3));

    cv::perspectiveTransform(src, dst, homography);

    transformedRegion = Plane2d(dst);

    Plane2d boundingBox = transformedRegion.getBoundingBox();

    size = boundingBox.getSize();

}

void Surface::adjustTranslations(cv::Point2f &offset) {
    homography.at<double>(0, 2) -= offset.x;
    homography.at<double>(1, 2) -= offset.y;
}

//TODO get right size
//It is like this right now because the second half needs to be
//located to the right
void Surface::applyHomography() {    
    cv::warpPerspective(image, transformedImage,
            homography, cv::Size(2000,2000));
}

//TODO this should store the offset but not apply it
//All planes' BBs should be located at (0,0), and then written on
//the final image according to their offset
void Surface::correctPosition(cv::Point2f& point) {
    cv::Point2f offset = transformedRegion.findOffset(point);
    this->adjustTranslations(offset);
    this->calculateTransformedPlane();
}

void Surface::correctBBPosition(cv::Point2f& point) {
    cv::Point2f offset = transformedRegion.findBBOffset(point);
    this->adjustTranslations(offset);
    this->calculateTransformedPlane();
}

void Surface::display() {
    this->display("");
}


void Surface::display(const char *name) {
    int keyPressed = 0;
    cv::imshow(name, transformedImage);
    std::cout << "Press ESC to continue..." << std::endl;
    do {
        keyPressed = cv::waitKey(0);
    } while (keyPressed != 27);
    
    this->print(name);    
}

cv::Point2f Surface::getUpperLeftCorner() {
    return transformedRegion.getUpperLeftCorner();
}

cv::Point2f Surface::getLowerRightCorner() {
    return transformedRegion.getUpperRightCorner();
}

cv::Point2f Surface::getUpperRightCorner() {
    return transformedRegion.getUpperRightCorner();
}

cv::Point2f Surface::getLowerLeftCorner() {
    return transformedRegion.getLowerLeftCorner();
}

void Surface::addTransparency() {
    Utils utils;
    utils.addAlphaChannel(transformedImage, transformedRegion);
}

cv::Size Surface::getSize() {
    return size;
}

void Surface::print() {
    this->print("Surface");
}


void Surface::print(const char *name) {
    std::cout << std::endl << "========= " << name << " =========" << std::endl;
    std::cout << "Source image: " << std::endl;
    std::cout << "\tChannels: " << image.channels() << std::endl;
    std::cout << "\trows: " << image.rows << std::endl;
    std::cout << "\tcols: " << image.cols << std::endl;
    std::cout << "Transformed image: " << std::endl;
    std::cout << "\tChannels: " << transformedImage.channels() << std::endl;
    std::cout << "\trows: " << transformedImage.rows << std::endl;
    std::cout << "\tcols: " << transformedImage.cols << std::endl;
    std::cout << "Source plane: " << std::endl;
    std::cout << sourcePlane << std::endl;
    std::cout << "Destination plane: " << std::endl;
    std::cout << destinationPlane << std::endl;
    std::cout << "Transformed plane: " << std::endl;
    std::cout << transformedRegion << std::endl;
    std::cout << "Homography: " << std::endl;
    std::cout << homography << std::endl;
    std::cout << std::endl << "===========================" << std::endl << std::endl;
}

void Surface::save() {
    this->save("image.png");
}

void Surface::save(const char *name) {
    cv::imwrite(name, transformedImage);
}
