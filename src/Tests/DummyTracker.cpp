/* 
 * File:   DummyTracker.cpp
 * Author: bruno
 * 
 * Created on February 6, 2014, 4:23 PM
 */

#include <boost/thread/pthread/thread_data.hpp>

#include "DummyTracker.h"

DummyTracker::DummyTracker() : 
        userPosition(cv::Point3f(0.0, 1700.0, -3000.0)){
    
}

DummyTracker::DummyTracker(const DummyTracker& orig) {
}

DummyTracker::~DummyTracker() {
}


void DummyTracker::setupTracking() {
    std::cout << "Setting up tracking..." << std::endl;
    boost::posix_time::seconds workTime(1);
    boost::this_thread::sleep(workTime);
    std::cout << "Done setting up tracking." << std::endl;
}


cv::Point3f DummyTracker::getUserPosition() {
    boost::lock_guard<boost::mutex> guard(_mtx);
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

void DummyTracker::setUserPosition(cv::Point3f &pos) {
    boost::lock_guard<boost::mutex> guard(_mtx);
    userPosition = pos;
}


void DummyTracker::track() {
    //TODO rand x, rand y, rand z
    //TODO Get reference to main in order to lock / unlock him
    
//    boost::lock_guard<RealTimeVisualizer> guard(*visualizer);
    while(1){
        cv::Point3f p(userPosition.x+0.0001, userPosition.y, userPosition.z);
        this->setUserPosition(p);
    }
    
}
