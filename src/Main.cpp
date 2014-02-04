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

//void runTests();

int main(int argc, char** argv) {    
//    TestSurface t;
//    t.test();  
    
    TestProjection t;
<<<<<<< HEAD
<<<<<<< HEAD
    t.test();
=======
    t.test(-1500.0, 1000.0, -3500.0);
>>>>>>> 32a6818ae0d9d86380aeb166f11fd39e64c52591
=======
    t.test(-1500.0, 1000.0, -3500.0);
>>>>>>> 32a6818ae0d9d86380aeb166f11fd39e64c52591

//    TestPlanes t;
//    t.test();

    Calib c;

    /* USER TRACKING. */
<<<<<<< HEAD
    Tracking tracking;
    tracking.setupTracking(argc,argv,c.rotationVectors.at(0),c.translationVectors.at(0));
=======
//    Tracking tracking;
//    tracking.setupTracking(argc,argv);
//    Calib();
<<<<<<< HEAD
>>>>>>> 32a6818ae0d9d86380aeb166f11fd39e64c52591
=======
>>>>>>> 32a6818ae0d9d86380aeb166f11fd39e64c52591

    //  int mode = openni_wrapper::OpenNIDevice::OpenNI_12_bit_depth;
    //  console::parse_argument (argc, argv, "-mode", mode);
    //  Modelisation m (static_cast<openni_wrapper::OpenNIDevice::DepthMode> (mode));
    //  m.run ();

    return 0;

}

void runTests(){
    PlaneTests planeTests;
    planeTests.testContains();
}
