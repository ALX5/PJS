/* 
 * File:   main.cpp
 * Author: bruno
 *
 * Created on December 20, 2013, 9:02 PM
 */

#include "Distortion/TestSources.h"
#include "Tests/PlaneTests.h"
#include "Distortion/TestSurface.h"
#include "Tracking/Tracking.h"
#include "Calibration/Calib.h"

//void runTests();

/*
 * 
 */
int main(int argc, char** argv) {
//    TestSources t;
//    return t.twoPlanesTest();
    
    /*TestSurface t;
    t.test();*/
    
	/* USER TRACKING. */
//    Tracking tracking;
//    tracking.setupTracking(argc,argv);

    Calib();

	return 0;

}

void runTests(){
    PlaneTests planeTests;
    planeTests.testContains();
}
