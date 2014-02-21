/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#include <opencv2/opencv.hpp>
#include <boost/thread.hpp>
#include "../Main.h"

#define MAX_USERS 1

class Tracking
{
    
public :
    Tracking();
    void setupTracking ();
    void track ();
    double X;
    double Y;
    double Z;
    
    cv::Point3f getUserPosition();
    void setUserPosition(cv::Point3f &pos);

    
    double getX() { return X; }
    double getY() { return Y; }
    double getZ() { return Z; }
    
    void stop();
    
private:
    boost::mutex _mtx;
    cv::Point3f userPosition;
    bool done;
    
    XnUserID users[MAX_USERS];
    XnUInt16 nUsers;
    XnSkeletonJointTransformation head;
};
