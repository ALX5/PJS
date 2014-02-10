/* 
 * File:   DummyTracker.cpp
 * Author: bruno
 * 
 * Created on February 6, 2014, 4:23 PM
 */

#include <boost/thread/pthread/thread_data.hpp>

#include "DummyTracker.h"

DummyTracker::DummyTracker() : 
        userPosition(cv::Point3f(0.0, 0.0, 0.0)){
    
}

DummyTracker::DummyTracker(const DummyTracker& orig) {
}

DummyTracker::~DummyTracker() {
}

DummyTracker::DummyTracker(RealTimeVisualizer &visualizer){
    (this->visualizer) = &visualizer;
}

void DummyTracker::setupTracking() {
    std::cout << "Setting up tracking..." << std::endl;
    boost::posix_time::seconds workTime(1);
    boost::this_thread::sleep(workTime);
    std::cout << "Done setting up tracking." << std::endl;
}


cv::Point3f DummyTracker::getUserPosition() {
    return userPosition;
}

double DummyTracker::getX() {
    return userPosition.x;
}

double DummyTracker::getY() {
    return userPosition.y;    
}

double DummyTracker::getZ() {
    return userPosition.z;
}

void DummyTracker::track() {
    //TODO rand x, rand y, rand z
    //TODO Get reference to main in order to lock / unlock him
    
    boost::lock_guard<RealTimeVisualizer> guard(*visualizer);
    std::cout << "Tracking..." << std::endl;
    
    
}
