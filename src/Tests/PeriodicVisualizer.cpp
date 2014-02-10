/* 
 * File:   PeriodicVisualizer.cpp
 * Author: bruno
 * 
 * Created on February 10, 2014, 12:00 PM
 */

#include <boost/thread.hpp>
#include "PeriodicVisualizer.h"
#include "Tracking.h"
#include "TestProjection.h"

PeriodicVisualizer::PeriodicVisualizer() {
}

PeriodicVisualizer::PeriodicVisualizer(const PeriodicVisualizer& orig) {
}

PeriodicVisualizer::~PeriodicVisualizer() {
}

void PeriodicVisualizer::visualize() {

    Tracking tracking;
    TestProjection t;

    boost::thread threadTracking(&Tracking::setupTracking, &tracking);
    //threadTracking.join();


    double x = 0.0, lastX = 0.0;
    double y = 0.0, lastY = 0.0;
    double z = 0.0, lastZ = 0.0;

    while (1) {
        if (tracking.getX() == 0.0 && tracking.getY() == 0.0 && tracking.getZ() == 0.0)
            continue;
        //lastX=x;
        //lastY=y;
        //lastZ=z;
        x = tracking.getX();
        y = tracking.getY();
        z = tracking.getZ();
        //if(x<lastX+1000 && x> lastX-1000 && y<lastY+1000 && y> lastY-1000 && z<lastZ+1000 && z> lastZ-1000)

        std::cout << x << ", " << y << ", " << z << std::endl;

        cv::Mat img = t.test(x, y, z);

        int keyPressed = cv::waitKey(1000);
        if (keyPressed == 1048585) cv::imshow("Final", img);

    }
}
