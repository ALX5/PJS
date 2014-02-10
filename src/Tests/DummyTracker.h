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
    
    DummyTracker(RealTimeVisualizer&);
    
    void setupTracking();
    double getX();
    double getY();
    double getZ();
    
    cv::Point3f getUserPosition();
    
    void track();
    
private:    
    cv::Point3f userPosition;
    RealTimeVisualizer *visualizer;
};

#endif	/* DUMMYTRACKER_H */

