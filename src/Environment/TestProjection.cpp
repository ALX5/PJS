/* 
 * File:   TestProjection.cpp
 * Author: bruno
 * 
 * Created on January 28, 2014, 3:33 PM
 */

#include <opencv2/opencv.hpp>
#include "TestProjection.h"
#include "Projection.h"
#include "User.h"
#include <iostream>

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

    Plane3d p1(p11, p12, p13, p14);

    Plane3d p2(p21, p22, p23, p24);

    std::cout << "***********************************************" << std::endl;
    std::cout << "                   Testing                     " << std::endl;
    std::cout << "***********************************************" << std::endl;
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl << std::endl;

    
    std::vector<Plane3d> planes;
    planes.push_back(p1);
    planes.push_back(p2);

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
    std::cout << "Intersections" << std::endl;
    std::vector<Plane3d>::iterator ii;
    std::vector<Plane3d> pPlanes = u.getProjectedPlanes();
    for (ii = pPlanes.begin(); ii != pPlanes.end(); ii++) {
        std::cout << *ii << std::endl;
    }
    
    //En utilisant les plans obtenues par u.getProjectedPlanes(); et les plans
    //parfaits qu'on definissent nous mêmes, on pourra recalculer les homographies
    //à chaque pas de temps
    
}
