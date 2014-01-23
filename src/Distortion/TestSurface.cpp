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
#include "HomographyCalculator.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <exception>

using namespace std;

TestSurface::TestSurface() {
}

TestSurface::TestSurface(const TestSurface& orig) {
}

TestSurface::~TestSurface() {
}

void TestSurface::test() {
    //Planes for the first part
    //Actual coords on image
//    Plane p1(Point2f(10, 676), Point2f(1274, 0), Point2f(1274, 1016), Point2f(92, 1396));
//    Plane p2(Point2f(0, 0), Point2f(960, 0), Point2f(960, 1080), Point2f(0, 1080));
    //Normalized coords on image
//    Plane p1(Point2f(10 - 194, 676), Point2f(1274 - 194, 0), Point2f(1274 - 194, 1016), Point2f(92 - 194, 1396));
//    Plane p2(Point2f(0, 0), Point2f(960, 0), Point2f(960, 1080), Point2f(0, 1080));
//    Plane p2(Point2f(0+500, 0+250), Point2f(960, 0+250), Point2f(960, 1080-250), Point2f(0+500, 1080-250));
    
    //Planes for the second part
    //    Plane p3(Point2f(306, 0), Point2f(1222, 148), Point2f(1134, 1306), Point2f(287, 1024));
    //    Plane p3(Point2f(0, 0), Point2f(92, 1024-298), Point2f(1222-306, 148-298), Point2f(1134-306, 1306-298));
    //    Plane p3(Point2f(1370, 323), Point2f(1349, 1343), Point2f(2277, 470), Point2f(2189, 1633));
    //Actual coords on image
    //    Plane p3(Point2f(1273, 0), Point2f(2178, 147), Point2f(2091, 1308), Point2f(1263, 1016));
//    Plane p4(Point2f(960, 0), Point2f(1920, 0), Point2f(1920, 1080), Point2f(960, 1080));
    //Normalized coords on image
//    Plane p3(Point2f(0, 0), Point2f(905, 147), Point2f(818, 1308), Point2f(0, 1016));
//    Plane p4(Point2f(0, 0), Point2f(960, 0), Point2f(960, 1080), Point2f(0, 1080));
//    Plane p4(Point2f(0, 0+250), Point2f(960-500, 0+250), Point2f(960-500, 1080-250), Point2f(0, 1080-250));

    //    Plane p4(Point2f(1257, 147), Point2f(1257, 1023), Point2f(2178, 147), Point2f(2178, 1023));

    
    /**
     * Test 14_01_22_16_34
     * */
    //Second option, plane 1
    Plane p1(Point2f(0, 325), Point2f(426, 0), Point2f(426, 625), Point2f(16, 875));
    Plane p2(Point2f(0, 0), Point2f(480, 0), Point2f(480, 540), Point2f(0, 540));
    
    //Second option, plane 2
    //Actual coords on plane
//    Plane p3(Point2f(420-420, 0), Point2f(1002-420, 250), Point2f(1002-420, 779), Point2f(420-420, 667));
    //normalized coords on plane
    Plane p3(Point2f(0, 0), Point2f(568, 250), Point2f(568, 779), Point2f(0, 625));
    Plane p4(Point2f(0, 0), Point2f(480, 0), Point2f(480, 540), Point2f(0, 540));
    
    
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
    //TODO define constant for ESC key
    do {
        keyPressed = waitKey(0);
    } while (keyPressed != 27);

    //TODO Now we must divide the image according to the corresponding regions
    //For now we can 'trick' the user by adjusting the size of the images depending
    //on the original plane if A *= 0.5 and B *= 1, rule of three, just for X

}


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
    Plane p1(Point2f(0, 670), Point2f(92, 1396), Point2f(1266, 0), Point2f(1254, 1024));
//    Plane p1(Point2f(0, 0), Point2f(92, 1396-670), Point2f(1266, -670), Point2f(1254, 1024-670));
//    Plane p1(Point2f(105, 998), Point2f(188, 1723), Point2f(1370, 323), Point2f(1349, 1343));    
    Plane p2(Point2f(0, 0), Point2f(0, 1080), Point2f(960, 0), Point2f(960, 1080));

    //Planes for the second part
    Plane p3(Point2f(306, 0), Point2f(294, 1024), Point2f(1222, 148), Point2f(1134, 1306));
//    Plane p3(Point2f(0, 0), Point2f(92, 1024-298), Point2f(1222-306, 148-298), Point2f(1134-306, 1306-298));
//    Plane p3(Point2f(1370, 323), Point2f(1349, 1343), Point2f(2277, 470), Point2f(2189, 1633));
    Plane p4(Point2f(0, 0), Point2f(0, 1080), Point2f(960, 0), Point2f(960, 1080));

    Utils utils;

    const char* nom1 = "../src/grid-straight2.png";
    Mat img = imread(nom1, CV_LOAD_IMAGE_COLOR);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
    }

    //Divide the image in two
    vector<Mat> images = utils.divideImageInTwo(img);

    //Build the surfaces with their reference planes and their corresponding
    //image
    Surface s1(p1, p2, images.at(0));
    Surface s2(p3, p4, images.at(1));

    //TODO recursive position correction
    //Correct the position of the surfaces
    Point2f origin(0, 0);
    s1.correctBBPosition(origin);
    Point2f s1ur = s1.getUpperRightCorner();
    cout << "Upper right: " << s1ur << endl;
    s2.correctPosition(s1ur);

    s1.applyHomography();
    s2.applyHomography();
    s1.addTransparency();
    s2.addTransparency();
    
    s1.display("s1");
    s2.display("s2");
    
    vector<Surface*> surfaces;
    surfaces.push_back(&s1);
    surfaces.push_back(&s2);
    Mat finalImage = utils.getImageFromSurfaces(surfaces);
    
    int keyPressed = 0;
    imshow("Final", finalImage);
    imwrite("finalImage.png", finalImage);
    //TODO define constant for ESC key
    do {
        keyPressed = waitKey(0);
    } while (keyPressed != 27);    

    //TODO Now we must divide the image according to the corresponding regions
    //For now we can 'trick' the user by adjusting the size of the images depending
    //on the original plane if A *= 0.5 and B *= 1, rule of three, just for X
            
}

