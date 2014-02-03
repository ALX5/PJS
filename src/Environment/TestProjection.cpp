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

void TestProjection::test() {

    //Ces plans-ci représentent les coordonnées des surfaces projetées
    cv::Point3f p11(-543, 1314, -543);    
    cv::Point3f p12(0, 1474, 0);    
    cv::Point3f p13(0, 175, 0);
    cv::Point3f p14(-543, 228, -543);

    cv::Point3f p21(0, 1474, 0);
    cv::Point3f p22(543, 1314, -543);
    cv::Point3f p23(543, 228, -543);
    cv::Point3f p24(0, 175, 0);

    Plane3d proj1(p11, p12, p13, p14);

    Plane3d proj2(p21, p22, p23, p24);

    std::cout << "***********************************************" << std::endl;
    std::cout << "                   Testing                     " << std::endl;
    std::cout << "***********************************************" << std::endl;
    std::cout << proj1 << std::endl;
    std::cout << proj2 << std::endl << std::endl;

    
    std::vector<Plane3d> planes;
    planes.push_back(proj1);
    planes.push_back(proj2);

    //Cet objet-ci représent-il la projection, avec l'ensemble de plans projetés
    Projection proj(planes);

    //L'utilisateur. À chaque pas de temps il faut mettre à jour
    //sa position
    User u(proj);
    double x = -1500.0;
    double y = 1000.0;
    double z = -3500.0;
    //Cette méthode là fait-elle tout ce qui est necessaire    
    u.updatePosition(x, y, z);

    std::cout << "User" << std::endl;
    std::cout << x << ", " << y << ", " << z << std::endl << std::endl;

    //Ici j'imprime les intersections trouvées. Je crois que les
    //intersections son les bonnes, mais je suis pas completement sûr
    //qu'elle soient bien représentées selon les coordonnées du plan
    //projectif de l'utilisateur. J'essaierais de le voir demain.
//    std::cout << "Intersections" << std::endl;
//    std::vector<Plane3d>::iterator ii;
//    std::vector<Plane3d> pPlanes = u.getProjectedPlanes();
//    for (ii = pPlanes.begin(); ii != pPlanes.end(); ii++) {
//        std::cout << *ii << std::endl;
//    }
//    
    //En utilisant les plans obtenues par u.getProjectedPlanes(); et les plans
    //parfaits qu'on definissent nous mêmes, on pourra recalculer les homographies
    //à chaque pas de temps
    
    
    
    //Plane 1
    Plane2d p1 = u.getProjectedPlanes().at(0).to2d();
    Plane2d p2(cv::Point2f(0, 0), cv::Point2f(480, 0), cv::Point2f(480, 540), cv::Point2f(0, 540));
    
    //Plane 2
    Plane2d p3 = u.getProjectedPlanes().at(1).to2d();
    Plane2d p4(cv::Point2f(0, 0), cv::Point2f(480, 0), cv::Point2f(480, 540), cv::Point2f(0, 540));
    
    std::cout << "Distorted plane 1: " << std::endl << p1 << std::endl;
    std::cout << "Distorted plane 2: " << std::endl << p2 << std::endl;
    
    Utils utils;

    const char* nom1 = "../src/grid-straight2half.png";
    cv::Mat img = cv::imread(nom1, CV_LOAD_IMAGE_COLOR);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        throw std::exception();
    }

    //Divide the image in two
    std::vector<cv::Mat> images = utils.divideImageInTwo(img);
    
    std::cout << "Rows" << images.at(0).rows << std::endl;
    std::cout << "Rows" << images.at(1).rows << std::endl;

    //Build the surfaces with their reference planes and their corresponding
    //image
    Surface s1(p1, p2, images.at(0));
    Surface s2(p3, p4, images.at(1));
    
    s1.print("s1");
    s2.print("s2");

    
    std::vector<Surface*> surfaces;
    surfaces.push_back(&s1);
    surfaces.push_back(&s2);
        
    cv::Size size = utils.getFinalSize(surfaces);
    
    //TODO recursive position correction
    //Correct the position of the surfaces
    //TODO test xOffset when the plane to the left is narrower
    //TODO yOffset?
    int xOffset = size.width - s1.getWidth();
    cv::Point2f origin(0, 0);
    s1.correctBBPosition(origin);
    cv::Point2f s1ur = s1.getUpperRightCorner();
    s2.correctPosition(s1ur);

//    Plane2d boundingBox = pjs::getBoundingBox();
    
    
    s1.applyHomography(size);
    s2.applyHomography(size);
    s1.addTransparency();
    s2.addTransparency();

//    s1.display("s1");
//    s1.save("s1.png");
//    s2.display("s2");
//    s2.save("s2.png");

    cv::Mat finalImage = utils.getImageFromSurfaces(surfaces);

    int keyPressed = 0;
    
    cv::namedWindow("Final", CV_WINDOW_NORMAL);
    cv::setWindowProperty("Final", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    
    cv::imshow("Final", finalImage);
    
    cv::imwrite("finalImage.png", finalImage);
    std::cout << "Press ESC to continue..." << std::endl;
    //TODO define constants for ESC key
    do {
        keyPressed = cv::waitKey(0);
    } while (keyPressed != 27);
    
}
