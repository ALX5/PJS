/*
 * File:   main.cpp
 * Author: bruno
 *
 * Created on December 20, 2013, 9:02 PM
 */

#include "Tests/PlaneTests.h"
#include "Tracking/Tracking.h"
#include "Distortion/TestPlanes.h"
#include "Environment/TestProjection.h"



#include "Calibration/Calib.h"
#include "Tests/AffineTests.h"

void runTests();

int main(int argc, char** argv) {    

//    Calib c;

    /* USER TRACKING. */

//    Tracking tracking;
//    tracking.setupTracking(argc,argv,c.rotationVectors.at(0),c.translationVectors.at(0));

    
    TestProjection t;
    t.test(0.0, 1800, -2000.0);

    
//    Tracking tracking;
//    tracking.setupTracking(argc,argv);
//    Calib();

    //  int mode = openni_wrapper::OpenNIDevice::OpenNI_12_bit_depth;
    //  console::parse_argument (argc, argv, "-mode", mode);
    //  Modelisation m (static_cast<openni_wrapper::OpenNIDevice::DepthMode> (mode));
    //  m.run ();

//    runTests();
    
    return 0;

}

void runTests(){
    AffineTests at;
    at.testAffineTransform();
}
