/* 
 * File:   DummyTracker.h
 * Author: bruno
 *
 * Created on February 6, 2014, 4:23 PM
 */

#ifndef DUMMYTRACKER_H
#define	DUMMYTRACKER_H

#include <opencv2/opencv.hpp>
#include "RealTimeVisualizer.h"
class DummyTracker {
public:
    DummyTracker();
    DummyTracker(const DummyTracker& orig);
    virtual ~DummyTracker();
    
    void setupTracking();
    double getX();
    double getY();
    double getZ();
    
    
    cv::Point3f getUserPosition();
    void setUserPosition(cv::Point3f &pos);
    
    void track();
    void stop();
    
private:    
    cv::Point3f userPosition;
    boost::mutex _mtx;
    bool done;
};

#endif	/* DUMMYTRACKER_H */

