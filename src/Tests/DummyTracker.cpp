/* 
 * File:   DummyTracker.cpp
 * Author: bruno
 * 
 * Created on February 6, 2014, 4:23 PM
 */

#include <iostream>
#include <boost/thread/pthread/thread_data.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/thread_time.hpp>

#include "DummyTracker.h"

DummyTracker::DummyTracker() : 
        userPosition(cv::Point3f(-500.0, 700.0, -3000.0)), done(false){
    
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

    //TODO Random x, y, z
    int times = 0;
    double increment = 10;
    while(!done){
        cv::Point3f p(userPosition.x+increment, userPosition.y, userPosition.z);
        this->setUserPosition(p);
        times++;
        if(times == 300){
            increment = -increment;
            times = 0;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(40));
    }
    
}

void DummyTracker::stop() {
    done = true;
}
