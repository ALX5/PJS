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
#include "Calib.h"

//void runTests();

int main(int argc, char** argv) {    
//    TestSurface t;
//    t.test();  
    
    TestProjection t;
    t.test(-1500.0, 1000.0, -3500.0);

//    TestPlanes t;
//    t.test();
    
    /* USER TRACKING. */
//    Tracking tracking;
//    tracking.setupTracking(argc,argv);
//    Calib();

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
