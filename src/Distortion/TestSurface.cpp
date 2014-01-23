/* 
 * File:   TestSurfac.cpp
 * Author: bruno
 * 
 * Created on January 20, 2014, 4:29 PM
 */

#include "TestSurface.h"
#include "Surface.h"
#include "HomographyCalculator.h"
#include "Utils.h"
#include <iostream>
#include <vector>

using namespace std;

TestSurface::TestSurface() {
}

TestSurface::TestSurface(const TestSurface& orig) {
}

TestSurface::~TestSurface() {
}

void TestSurface::test() {
    //Planes for the first part
    Plane p1(Point2f(0, 442), Point2f(996, 0), Point2f(971, 630), Point2f(25, 800));
//    Plane p1(Point2f(0, 0), Point2f(92, 1396-670), Point2f(1266, -670), Point2f(1254, 1024-670));
//    Plane p1(Point2f(105, 998), Point2f(188, 1723), Point2f(1370, 323), Point2f(1349, 1343));    
    Plane p2(Point2f(0, 0), Point2f(1280, 0), Point2f(1280, 1024), Point2f(0, 1024));

    //Planes for the second part
    //Plane p3(Point2f(306, 0), Point2f(294, 1024), Point2f(1222, 148), Point2f(1134, 1306));
//    Plane p3(Point2f(0, 0), Point2f(92, 1024-298), Point2f(1222-306, 148-298), Point2f(1134-306, 1306-298));
//    Plane p3(Point2f(1370, 323), Point2f(1349, 1343), Point2f(2277, 470), Point2f(2189, 1633));
    //Plane p4(Point2f(0, 0), Point2f(0, 1080), Point2f(960, 0), Point2f(960, 1080));

    //Utils utils;

    const char* nom1 = "../src/wolf.jpg";
    Mat img = imread(nom1, CV_LOAD_IMAGE_COLOR);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
    }

    //Divide the image in two
    //vector<Mat> images = utils.divideImageInTwo(img);

    //Build the surfaces with their reference planes and their corresponding
    //image
    Surface s1(p1, p2, img);
    //Surface s2(p3, p4, images.at(1));

    //TODO recursive position correction
    //Correct the position of the surfaces
    Point2f origin(0, 0);
    s1.correctBBPosition(origin);
    Point2f s1ur = s1.getUpperRightCorner();
    //s2.correctPosition(s1ur);

    s1.applyHomography();
    //s2.applyHomography();
    //s1.addTransparency();
    //s2.addTransparency();
    
    s1.display("s1");
    //s2.display("s2");
    
    /*vector<Surface*> surfaces;
    surfaces.push_back(&s1);
    surfaces.push_back(&s2);
    Mat finalImage = utils.getImageFromSurfaces(surfaces);
    
    int keyPressed = 0;
    imshow("Final", finalImage);
    imwrite("finalImage.png", finalImage);
    //TODO define constant for ESC key
    do {
        keyPressed = waitKey(0);
    } while (keyPressed != 27);  */

    //TODO Now we must divide the image according to the corresponding regions
    //For now we can 'trick' the user by adjusting the size of the images depending
    //on the original plane if A *= 0.5 and B *= 1, rule of three, just for X
            
}

