/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
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
    
//    Calib c;
    
    return 0;

}

void runTests() {
    AffineTests at;
    at.testAffineTransform();
}
