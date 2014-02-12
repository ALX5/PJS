/* 
 * File:   Surface.cpp
 * Author: bruno
 * 
 * Created on January 20, 2014, 4:22 PM
 */

#include <iostream>
#include "Surface.h"
#include "Utils.h"

Surface::Surface() {
}

Surface::Surface(const Surface& orig) {
}

Surface::~Surface() {
}

Surface::Surface(Plane2d& src, Plane2d& dst) :
_sourcePlane(src), _destinationPlane(dst) {
    
    this->_affineTransformation =
            (cv::Mat_<double>(3, 3) << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
    this->determineHomography();
    this->calculateTransformedPlane();
}

Surface::Surface(Plane2d& src, Plane2d& dst, cv::Mat image) :
_sourcePlane(src), _destinationPlane(dst), _image(image) {

    this->_affineTransformation =
            (cv::Mat_<double>(3, 3) << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

    this->determineHomography();
    this->calculateTransformedPlane();
}

void Surface::determineHomography() {
    std::vector<cv::Point2f> src;
    std::vector<cv::Point2f> dst;

    src.push_back(_sourcePlane.getPoint(0));
    src.push_back(_sourcePlane.getPoint(1));
    src.push_back(_sourcePlane.getPoint(2));
    src.push_back(_sourcePlane.getPoint(3));

    dst.push_back(_destinationPlane.getPoint(0));
    dst.push_back(_destinationPlane.getPoint(1));
    dst.push_back(_destinationPlane.getPoint(2));
    dst.push_back(_destinationPlane.getPoint(3));

    _homography = cv::findHomography(src, dst);
}

void Surface::determineHomography(Plane2d source, Plane2d destination) {
    std::vector<cv::Point2f> src;
    std::vector<cv::Point2f> dst;

    src.push_back(source.getPoint(0));
    src.push_back(source.getPoint(1));
    src.push_back(source.getPoint(2));
    src.push_back(source.getPoint(3));

    dst.push_back(destination.getPoint(0));
    dst.push_back(destination.getPoint(1));
    dst.push_back(destination.getPoint(2));
    dst.push_back(destination.getPoint(3));

    _homography = cv::findHomography(src, dst);
}

void Surface::calculateTransformedPlane() {
    std::vector<cv::Point2f> src;
    std::vector<cv::Point2f> dst;

    src.push_back(_destinationPlane.getPoint(0));
    src.push_back(_destinationPlane.getPoint(1));
    src.push_back(_destinationPlane.getPoint(2));
    src.push_back(_destinationPlane.getPoint(3));

    cv::perspectiveTransform(src, dst, _homography);
    _transformedRegion = Plane2d(dst);

}

void Surface::adjustTranslations(cv::Point2f &offset) {
    _affineTransformation.at<double>(0, 2) = -offset.x;
    _affineTransformation.at<double>(1, 2) = -offset.y;
    _homography = _affineTransformation*_homography;
}

void Surface::applyHomography() {
    cv::warpPerspective(_image, _transformedImage,
            _homography, cv::Size(_size.width, _size.height),
            cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
}

//TODO this should store the offset but not apply it
//All planes' BBs should be located at (0,0), and then written on
//the final image according to their offset

void Surface::correctPosition(cv::Point2f& point) {
    cv::Point2f offset = _transformedRegion.findOffset(point);
    this->adjustTranslations(offset);
    this->calculateTransformedPlane();
}

void Surface::correctBBPosition(cv::Point2f& point) {
    cv::Point2f offset = _transformedRegion.findBBOffset(point);
    this->adjustTranslations(offset);
    this->calculateTransformedPlane();
}

void Surface::display() {
    this->display("");
}

void Surface::display(const char *name) {
    int keyPressed = 0;
    cv::imshow(name, _transformedImage);
    std::cout << "Press ESC to continue..." << std::endl;
    do {
        keyPressed = cv::waitKey(0);
    } while (keyPressed != 27);

    this->print(name);
}

void Surface::addTransparency() {
    Utils utils;
    utils.addAlphaChannel(_transformedImage, _transformedRegion);
}

void Surface::print() {
    this->print("Surface");
}

void Surface::save() {
    this->save("image.png");
}

void Surface::save(const char *name) {
    cv::imwrite(name, _transformedImage);
}

int Surface::getWidth() {
    return _transformedRegion.getWidth();
}

int Surface::getHeight() {
    return _transformedRegion.getHeight();
}

cv::Point2f Surface::getUpperLeftCorner() {
    return _transformedRegion.getUpperLeftCorner();
}

cv::Point2f Surface::getLowerRightCorner() {
    return _transformedRegion.getLowerRightCorner();
}

cv::Point2f Surface::getUpperRightCorner() {
    return _transformedRegion.getUpperRightCorner();
}

cv::Point2f Surface::getLowerLeftCorner() {
    return _transformedRegion.getLowerLeftCorner();
}

void Surface::print(const char *name) {
    std::cout << std::endl << "========= " << name << " =========" << std::endl;
    std::cout << "Source image: " << std::endl;
    std::cout << "\tChannels: " << _image.channels() << std::endl;
    std::cout << "\trows: " << _image.rows << std::endl;
    std::cout << "\tcols: " << _image.cols << std::endl;
    std::cout << "Transformed image: " << std::endl;
    std::cout << "\tChannels: " << _transformedImage.channels() << std::endl;
    std::cout << "\trows: " << _transformedImage.rows << std::endl;
    std::cout << "\tcols: " << _transformedImage.cols << std::endl;
    std::cout << "Source plane: " << std::endl;
    std::cout << _sourcePlane << std::endl;
    std::cout << "Destination plane: " << std::endl;
    std::cout << _destinationPlane << std::endl;
    std::cout << "Transformed plane: " << std::endl;
    std::cout << _transformedRegion << std::endl;
    std::cout << "Homography: " << std::endl;
    std::cout << _homography << std::endl;
    std::cout << std::endl << "===========================" << std::endl << std::endl;
}


namespace pjs {

    Plane2d getBoundingBox(Plane2d& p1, Plane2d& p2) {
        std::vector<float> xCoords;

        xCoords.push_back(p1.getPoint(0).x);
        xCoords.push_back(p1.getPoint(1).x);
        xCoords.push_back(p1.getPoint(2).x);
        xCoords.push_back(p1.getPoint(3).x);
        xCoords.push_back(p2.getPoint(0).x);
        xCoords.push_back(p2.getPoint(1).x);
        xCoords.push_back(p2.getPoint(2).x);
        xCoords.push_back(p2.getPoint(3).x);


        std::vector<float> yCoords;
        yCoords.push_back(p1.getPoint(0).y);
        yCoords.push_back(p1.getPoint(1).y);
        yCoords.push_back(p1.getPoint(2).y);
        yCoords.push_back(p1.getPoint(3).y);
        yCoords.push_back(p2.getPoint(0).y);
        yCoords.push_back(p2.getPoint(1).y);
        yCoords.push_back(p2.getPoint(2).y);
        yCoords.push_back(p2.getPoint(3).y);


        float minX = *std::min_element(xCoords.begin(), xCoords.end());
        float minY = *std::min_element(yCoords.begin(), yCoords.end());
        float maxX = *std::max_element(xCoords.begin(), xCoords.end());
        float maxY = *std::max_element(yCoords.begin(), yCoords.end());

        Plane2d p(cv::Point2f(minX, minY), cv::Point2f(minX, maxY), cv::Point2f(maxX, minY), cv::Point2f(maxX, maxY));

        return p;
    }
}

void Surface::fixIntersection(Surface& surface) {
    cv::Point2f top1 = this->getUpperRightCorner();
    cv::Point2f top2 = surface.getUpperLeftCorner();
    cv::Point2f bottom1 = this->getLowerRightCorner();
    cv::Point2f bottom2 = surface.getLowerLeftCorner();

    std::vector<cv::Point2f> top;
    top.push_back(top1);
    top.push_back(top2);
    std::vector<cv::Point2f> bottom;
    bottom.push_back(bottom1);
    bottom.push_back(bottom2);



    cv::Point2f topAvg = pjs::average(top);
    cv::Point2f bottomAvg = pjs::average(bottom);

    std::cout << "TopR1: " << top1 << std::endl;
    std::cout << "TopL2: " << top2 << std::endl;
    std::cout << "TopAvg: " << topAvg << std::endl;
    std::cout << "BottomR1: " << bottom1 << std::endl;
    std::cout << "BottomL2: " << bottom2 << std::endl;
    std::cout << "BottomAvg: " << bottomAvg << std::endl;

    Plane2d newPlane1(_transformedRegion.getUpperLeftCorner(),
            topAvg,
            bottomAvg,
            _transformedRegion.getLowerLeftCorner());

    Plane2d newPlane2(topAvg,
            surface.getUpperRightCorner(),
            surface.getLowerRightCorner(),
            bottomAvg);

    std::cout << "New plane 1: " << newPlane1 << std::endl;
    std::cout << "New plane 2: " << newPlane2 << std::endl;


    std::cout << "Old Homography: " << _homography << std::endl;
    this->determineHomography(_destinationPlane, newPlane1);
    surface.determineHomography(_destinationPlane, newPlane2);
    std::cout << "New Homography: " << _homography << std::endl;

    this->calculateTransformedPlane();
    surface.calculateTransformedPlane();

}

cv::Size Surface::getSize() {
    return _size;
}

void Surface::setSize(cv::Size size) {
    _size = size;
}

void Surface::setImage(cv::Mat image) {
    _image = image;
}
