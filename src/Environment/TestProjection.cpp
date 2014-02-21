/* 
 * File:   TestProjection.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Created on January 28, 2014, 3:33 PM
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>
#include "TestProjection.h"
#include "Projection.h"
#include "User.h"
#include "Utils.h"
#include "opencv/cv.hpp"

TestProjection::TestProjection() {
}

TestProjection::TestProjection(const TestProjection& orig) {
}

TestProjection::~TestProjection() {
}

cv::Mat TestProjection::test(double userX, double userY, double userZ, 
        const char* filename) {

    //Coordinates of the projection in the real world
    /*cv::Point3f p11(-480, 735, -420);
    cv::Point3f p12(0, 935, 0);
    cv::Point3f p13(0, 220, 0);
    cv::Point3f p14(-480, 240, -420);
    Plane3d proj1(p11, p12, p13, p14);

    cv::Point3f p21(0, 935, 0);
    cv::Point3f p22(480, 735, -420);
    cv::Point3f p23(480, 240, -420);
    cv::Point3f p24(0, 220, 0);
    Plane3d proj2(p21, p22, p23, p24);*/

    cv::Point3f p11(-590, 725, -350);
    cv::Point3f p12(0, 955, 0);
    cv::Point3f p13(0, 200, 0);
    cv::Point3f p14(-590, 227, -350);
    Plane3d proj1(p11, p12, p13, p14);

    cv::Point3f p21(0, 955, 0);
    cv::Point3f p22(567, 755, -350);
    cv::Point3f p23(567, 227, -350);
    cv::Point3f p24(0, 200, 0);
    Plane3d proj2(p21, p22, p23, p24);

    std::vector<Plane3d> planes;
    planes.push_back(proj1);
    planes.push_back(proj2);

    Projection proj(planes);

    //    proj.print();

    //Create the user with the obtained projection coordinates
    User u(proj);

    //Update his position
    u.updatePosition(userX, userY, userZ);
    //    u.print();

    //Create the distorted-corrected plane pairs, using the projections
    //on the user's view plane
    //Plane 1
    //****************************************************************************************************
    Plane2d p1 = u.getProjectedPlanes().at(0).to2d();
    Plane2d p2(cv::Point2f(0, 0), cv::Point2f(480, 0), cv::Point2f(480, 540), cv::Point2f(0, 540));
//    Plane2d p2(cv::Point2f(0, 0), cv::Point2f(230, 0), cv::Point2f(230, 520), cv::Point2f(0, 520));
//    Plane2d p2(cv::Point2f(0, 0), cv::Point2f(270, 0), cv::Point2f(270, 405), cv::Point2f(0, 405));
    //****************************************************************************************************
    //Invert the plane y coordinates
    Plane2d inv1 = p1.yInverted();
    //Move it so that it's closer to the target plane
    cv::Vec2f dist = pjs::distance(inv1, p2);
    Plane2d pp1(cv::Point2f(inv1.getPoint(0).x - dist[0], inv1.getPoint(0).y - dist[1]),
            cv::Point2f(inv1.getPoint(1).x - dist[0], inv1.getPoint(1).y - dist[1]),
            cv::Point2f(inv1.getPoint(2).x - dist[0], inv1.getPoint(2).y - dist[1]),
            cv::Point2f(inv1.getPoint(3).x - dist[0], inv1.getPoint(3).y - dist[1]));

    //Plane 2
    //****************************************************************************************************
    Plane2d p3 = u.getProjectedPlanes().at(1).to2d();
    Plane2d p4(cv::Point2f(0, 0), cv::Point2f(480, 0), cv::Point2f(480, 540), cv::Point2f(0, 540));
//    Plane2d p4(cv::Point2f(0, 0), cv::Point2f(230, 0), cv::Point2f(230, 520), cv::Point2f(0, 520));
//    Plane2d p4(cv::Point2f(0, 0), cv::Point2f(270, 0), cv::Point2f(270, 405), cv::Point2f(0, 405));
    //****************************************************************************************************
    //Invert the plane y coordinates
    Plane2d inv2 = p3.yInverted();
    //Move it so that it's closer to the target plane
    dist = pjs::distance(inv2, p4);
    Plane2d pp3(cv::Point2f(inv2.getPoint(0).x - dist[0], inv2.getPoint(0).y - dist[1]),
            cv::Point2f(inv2.getPoint(1).x - dist[0], inv2.getPoint(1).y - dist[1]),
            cv::Point2f(inv2.getPoint(2).x - dist[0], inv2.getPoint(2).y - dist[1]),
            cv::Point2f(inv2.getPoint(3).x - dist[0], inv2.getPoint(3).y - dist[1]));



    //***********************
    //Load the target image
    //***********************    
    cv::Mat img = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        throw std::exception();
    }

    //Helper object
    Utils utils;

    //Divide the image in two
    //    std::vector<cv::Mat> images = utils.divideImageInTwo(img);

    //Build the surfaces with their reference planes and their corresponding
    //image
    Surface s1(pp1, p2);
    Surface s2(pp3, p4);

    std::vector<Surface*> surfaces;
    surfaces.push_back(&s1);
    surfaces.push_back(&s2);

    int originX;
    int padding;
    int screenWidth = 1280;
    int screenHeight = 800;
    //TODO recursive position correction
    int width1 = s1.getWidth();
    int width2 = s2.getWidth();
    int diffW = width1 - width2;
    if (diffW < 0) {
        originX = screenWidth / 2 - width1;
        padding = 0;
    } else {
        originX = 0 + screenWidth / 2 - width1;
        padding = 0;
    }

    //1st position correction
    cv::Point2f origin(originX, 0);
    s1.correctBBPosition(origin);
    cv::Point2f s1ur = s1.getUpperRightCorner();    
    s2.correctPosition(s1ur);

    cv::Point2f upperLeft = s2.getUpperLeftCorner();
    cv::Point2f upperRight = s2.getUpperRightCorner();
    double topY;
    if (upperLeft.y < upperRight.y) {
        topY = upperLeft.y;
    } else {
        topY = upperRight.y;
    }
    cv::Size size = utils.getFinalSize(surfaces);
    int diffH = screenHeight - size.height;
    //2nd position correction if necessary (if second plane is still outside)
    if (!topY < 0) {
        topY = 0;
    }
    cv::Point2f newOrigin(originX, -topY + diffH / 2);
    s1.correctBBPosition(newOrigin);
    s1ur = s1.getUpperRightCorner();
    s2.correctPosition(s1ur);

    //    cv::Size size = utils.getFinalSize(surfaces);
    size.width += padding;

    size.width = std::max(screenWidth, size.width);
    size.height = screenHeight;

    cv::Size sizeS1(size.width / 2, size.height);

    s1.setSize(sizeS1);
    s2.setSize(size);

    std::vector<cv::Mat> images = utils.divideImageInTwo(img);

    s1.setImage(images.at(0));
    s2.setImage(images.at(1));

    s1.applyHomography();
    s2.applyHomography();
    //        s1.addTransparency();
    //        s2.addTransparency();

    cv::Mat finalImage = utils.getImageFromSurfaces(surfaces);

    surfaces.clear();

    return finalImage;
}
