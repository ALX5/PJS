/* 
 * File:   TestSurfac.cpp
 * Author: bruno
 * 
 * Created on January 20, 2014, 4:29 PM
 */
/* 
 * File:   TestSurfac.cpp
 * Author: bruno
 * 
 * Created on January 20, 2014, 4:29 PM
 */

#include "TestSurface.h"
#include "Surface.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;
using namespace cv;

TestSurface::TestSurface() {
}

TestSurface::TestSurface(const TestSurface& orig) {
}

TestSurface::~TestSurface() {
}

void TestSurface::test() {   
    
    /**
     * Test 14_01_22_16_34
     * */
    //Plane2d 1
    Plane2d p1(Point2f(0, 325), Point2f(426, 0), Point2f(426, 625), Point2f(16, 875));
    Plane2d p2(Point2f(0, 0), Point2f(480, 0), Point2f(480, 540), Point2f(0, 540));
    
    //Plane2d 2
    Plane2d p3(Point2f(0, 0), Point2f(568, 250), Point2f(568, 779), Point2f(0, 625));
    Plane2d p4(Point2f(0, 0), Point2f(480, 0), Point2f(480, 540), Point2f(0, 540));
    
    //Tests for full image
//    Plane2d p1(Point2f(0, 325), Point2f(426, 0), Point2f(426, 625), Point2f(16, 875));
//    Plane2d p2(Point2f(0, 0), Point2f(960, 0), Point2f(960, 1080), Point2f(0, 1080));
//    
//    Plane2d p3(Point2f(0, 0), Point2f(568, 250), Point2f(568, 779), Point2f(0, 625));
//    Plane2d p4(Point2f(0, 0), Point2f(960, 0), Point2f(960, 1080), Point2f(0, 1080));
    
    
    Utils utils;

    const char* nom1 = "../src/grid-straight2half.png";
    Mat img = imread(nom1, CV_LOAD_IMAGE_COLOR);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        throw exception();
    }

    //Divide the image in two
    vector<Mat> images = utils.divideImageInTwo(img);
    
    cout << "Rows" << images.at(0).rows << endl;
    cout << "Rows" << images.at(1).rows << endl;

    //Build the surfaces with their reference planes and their corresponding
    //image
    Surface s1(p1, p2, images.at(0));
    Surface s2(p3, p4, images.at(1));
    
    s1.print("s1");
    s2.print("s2");

    //TODO recursive position correction
    //Correct the position of the surfaces
    Point2f origin(100, 100);
    s1.correctBBPosition(origin);
    Point2f s1ur = s1.getUpperRightCorner();
    cout << "Upper right: " << s1ur << endl;
    s2.correctPosition(s1ur);

    s1.applyHomography();
    s2.applyHomography();
    s1.addTransparency();
    s2.addTransparency();

    s1.display("s1");
    s1.save("s1.png");
    s2.display("s2");
    s2.save("s2.png");

    vector<Surface*> surfaces;
    surfaces.push_back(&s1);
    surfaces.push_back(&s2);
    Mat finalImage = utils.getImageFromSurfaces(surfaces);

    int keyPressed = 0;
    imshow("Final", finalImage);
    imwrite("finalImage.png", finalImage);
    cout << "Press ESC to continue..." << endl;
    //TODO define constants for ESC key
    do {
        keyPressed = waitKey(0);
    } while (keyPressed != 27);
}