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
#include "Tests/DummyTracker.h"
#include "EventHandler.h"
#include "PeriodicVisualizer.h"
#include "Visualizer.h"
#include <boost/thread.hpp>

void runTests();
void listen(bool &done){
    
    int keyPressed = 0;
    do{
        std::cout << "Waiting key: " << keyPressed << std::endl;
        keyPressed = cv::waitKey(0);
//        std::cin >> keyPressed;
        std::cout << "KEY: " << keyPressed << std::endl;
    }while(keyPressed != 27);
    done = true;
}
int main(int argc, char** argv) {

    Visualizer *visualizer = new RealTimeVisualizer();    
    visualizer->visualize();    
    delete visualizer;
    
    return 0;
}

void runTests() {
    AffineTests at;
    at.testAffineTransform();
}
