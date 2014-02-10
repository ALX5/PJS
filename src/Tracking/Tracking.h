#include <opencv2/opencv.hpp>
#include <boost/thread.hpp>
#include "../Main.h"

class Tracking
{
public :
    Tracking();
    void setupTracking ();
    double X;
    double Y;
    double Z;
    
    cv::Point3f getUserPosition();
    void setUserPosition(cv::Point3f &pos);

    
    double getX() { return X; }
    double getY() { return Y; }
    double getZ() { return Z; }
    
private:
    boost::mutex _mtx;
    cv::Point3f userPosition;
};
