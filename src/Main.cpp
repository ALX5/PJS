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

#include <boost/thread.hpp>

void runTests();

int main(int argc, char** argv) {    

    Tracking tracking;
    TestProjection t;

    boost::thread threadTracking(&Tracking::setupTracking, &tracking);
    //threadTracking.join();

    cout << "here" << endl;

    double x = 0.0, lastX = 0.0;
    double y = 0.0, lastY = 0.0;
    double z = 0.0, lastZ = 0.0;

    while(1) {
        if(tracking.getX() == 0.0 && tracking.getY() == 0.0 && tracking.getZ() == 0.0)
            continue;
        //lastX=x;
        //lastY=y;
        //lastZ=z;
        x=tracking.getX();
        y=tracking.getY();
        z=tracking.getZ();
        cout << x << endl;
        cout << y << endl;
        cout << z << endl;
        //if(x<lastX+1000 && x> lastX-1000 && y<lastY+1000 && y> lastY-1000 && z<lastZ+1000 && z> lastZ-1000)
            t.test(x,y,z);
    }

/*

    Tracking tracking;
    tracking.setupTracking(argc,argv);

    
    //TestProjection t;
    //t.test(294.899,1617.23,-3020.34);

    
//    Tracking tracking;
//    tracking.setupTracking(argc,argv);
//    Calib();

    //  int mode = openni_wrapper::OpenNIDevice::OpenNI_12_bit_depth;
    //  console::parse_argument (argc, argv, "-mode", mode);
    //  Modelisation m (static_cast<openni_wrapper::OpenNIDevice::DepthMode> (mode));
    //  m.run ();

//    runTests(); */
    
    return 0;

}

void runTests(){
    AffineTests at;
    at.testAffineTransform();
}
