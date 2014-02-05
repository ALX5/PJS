/* 
 * File:   TestProjection.cpp
 * Author: bruno
 * 
 * Created on January 28, 2014, 3:33 PM
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "TestProjection.h"
#include "Projection.h"
#include "User.h"
#include "Utils.h"

TestProjection::TestProjection() {
}

TestProjection::TestProjection(const TestProjection& orig) {
}

TestProjection::~TestProjection() {
}

void TestProjection::test(double userX, double userY, double userZ) {

    //TODO ******* In order to get the right Y offset, check the whole picture
    //2 passes, at least for the moment?
    //It does not work, anyway. We get the same shit
    
    //    cv::Point3f p11(-543, 1314, -543);    
    //    cv::Point3f p12(0, 1474, 0);    
    //    cv::Point3f p13(0, 175, 0);
    //    cv::Point3f p14(-543, 228, -543);
    //
    //    cv::Point3f p21(0, 1474, 0);
    //    cv::Point3f p22(543, 1314, -543);
    //    cv::Point3f p23(543, 228, -543);
    //    cv::Point3f p24(0, 175, 0);

    
    //Coordinates of the projection in the real world
    cv::Point3f p11(-480, 735, -420);
    cv::Point3f p12(0, 935, 0);
    cv::Point3f p13(0, 220, 0);
    cv::Point3f p14(-480, 240, -420);
    Plane3d proj1(p11, p12, p13, p14);

    cv::Point3f p21(0, 935, 0);
    cv::Point3f p22(480, 735, -420);
    cv::Point3f p23(480, 240, -420);
    cv::Point3f p24(0, 220, 0);
    Plane3d proj2(p21, p22, p23, p24);

    std::vector<Plane3d> planes;
    planes.push_back(proj1);
    planes.push_back(proj2);

    Projection proj(planes);

    proj.print();
    
    //Create the user with the obtained projection coordinates
    User u(proj);

    //Update his position
    u.updatePosition(userX, userY, userZ);
    u.print();

    //Create the distorted-corrected plane pairs, using the projections
    //on the user's view plane
    //Plane 1
    Plane2d p1 = u.getProjectedPlanes().at(0).to2d();
//    Plane2d p2(cv::Point2f(0, 0), cv::Point2f(480, 0), cv::Point2f(480, 540), cv::Point2f(0, 540));
//    Plane2d p2(cv::Point2f(-480, 0), cv::Point2f(0, 0), cv::Point2f(0, 540), cv::Point2f(-480, 540));
    Plane2d p2(cv::Point2f(-480, 540), cv::Point2f(0, 540), cv::Point2f(0, 0), cv::Point2f(-480, 0));
    //Plane 2
    Plane2d p3 = u.getProjectedPlanes().at(1).to2d();
    Plane2d p4(cv::Point2f(0, 540), cv::Point2f(480, 540), cv::Point2f(480, 0), cv::Point2f(0, 0));

    //Load the target image
    const char* nom1 = "../src/grid-straight2half.png";
    cv::Mat img = cv::imread(nom1, CV_LOAD_IMAGE_COLOR);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        throw std::exception();
    }

    //Helper object
    Utils utils;
    //Divide the image in two
    std::vector<cv::Mat> images = utils.divideImageInTwo(img);

    //Build the surfaces with their reference planes and their corresponding
    //image
    Surface s1(p1, p2, images.at(0));
    Surface s2(p3, p4, images.at(1));
  
    std::vector<Surface*> surfaces;
    surfaces.push_back(&s1);
    surfaces.push_back(&s2);

    s1.print("s1");
    s2.print("s2");
  

    //TODO recursive position correction
    //Correct the position of the surfaces
    //TODO test xOffset when the plane to the left is narrower
    //TODO yOffset?

//    int xOffset;
//    if (s1.getWidth() > s2.getWidth()) {
//        xOffset = size.width / 2 - s1.getWidth();
//    } else {
//        xOffset = size.width / 2 - s2.getWidth();
//    }
//    int yOffset;
//    if (s1.getHeight() > s2.getHeight()) {
//        yOffset = size.height - s1.getHeight();
//    } else {
//        yOffset = size.height - s2.getHeight();
//    }
//    std::cout << "Offset: " << xOffset << ", " << yOffset << std::endl;

    //TODO Changing the translation in the homography further affects the
    //transformation
    cv::Point2f origin(0, 0);
    s1.correctBBPosition(origin);
    cv::Point2f s1ur = s1.getUpperRightCorner();
    s2.correctPosition(s1ur);
    
    cv::Point2f upperLeft = s2.getUpperLeftCorner();
    cv::Point2f upperRight = s2.getUpperRightCorner();
    double topY;
    if(upperLeft.y < upperRight.y){
        topY = upperLeft.y;
    } else {
        topY = upperRight.y;
    }
    
    std::cout << "topy " << topY << std::endl;
    
    cv::Point2f newOrigin(0, -topY);
    s1.correctBBPosition(newOrigin);    
    s1ur = s1.getUpperRightCorner();
    s2.correctPosition(s1ur);
    
    cv::Size size = utils.getFinalSize(surfaces);
    std::cout << "Size: " << size << std::endl;
    
//    cv::Point2f origin3(0, 0);
//    s1.correctBBPosition(origin3);
//    s1ur = s1.getUpperRightCorner();
//    s2.correctPosition(s1ur);
//    size = utils.getFinalSize(surfaces);
//    std::cout << "Size: " << size << std::endl;
   
    
    s1.print("s1");
    s2.print("s2");

    
    s1.applyHomography(size);
    s2.applyHomography(size);
    s1.addTransparency();
    s2.addTransparency();

//        s1.display("s1");
//        s1.save("s1.png");
//        s2.display("s2");
//        s2.save("s2.png");

    cv::Mat finalImage = utils.getImageFromSurfaces(surfaces);

    int keyPressed = 0;

    //    cv::namedWindow("Final", CV_WINDOW_NORMAL);
    //    cv::setWindowProperty("Final", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    //    
    cv::imshow("Final", finalImage);

    cv::imwrite("finalImage.png", finalImage);
    std::cout << "Press ESC to continue..." << std::endl;
    //TODO define constants for ESC key
    do {
        keyPressed = cv::waitKey(0);
    } while (keyPressed != 27);

    surfaces.clear();

    cv::destroyAllWindows();

}
