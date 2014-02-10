/* 
 * File:   RealTimeVisualizer.cpp
 * Author: bruno
 * 
 * Created on February 10, 2014, 11:46 AM
 */

#include "RealTimeVisualizer.h"
#include "DummyTracker.h"
#include "TestProjection.h"

RealTimeVisualizer::RealTimeVisualizer() {
}

RealTimeVisualizer::RealTimeVisualizer(const RealTimeVisualizer& orig) {
}

RealTimeVisualizer::~RealTimeVisualizer() {
}

void RealTimeVisualizer::visualize() {
    //    Tracking tracker;
    DummyTracker tracker(*this);
    TestProjection t;

    tracker.setupTracking();



        cv::namedWindow("Final", CV_WINDOW_NORMAL);
        cv::setWindowProperty("Final", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

    cv::Mat finalImage;


    double x = 0.0, lastX = 0.0;
    double y = 0.0, lastY = 0.0;
    double z = 0.0, lastZ = 0.0;

    bool done = false;

    //    boost::thread threadTracking(listen, done);
    //    boost::thread threadTracking(tracker.track);
    //    boost::thread threadTracking(tracker.track);
    //threadTracking.join();
    boost::thread threadedTracking(&DummyTracker::track, &tracker);

    while (!done) {
        //TODO Make sure thread does not change coords while we get 'em
        //E.g: this locks itself 
        //thread gets coords and unlocks this, 
        //this locks thread retrieves them and unlocks thread

        //        x = tracker.getX();
        //        y = tracker.getY();
        //        z = tracker.getZ();
        //        cout << done << endl;        
        //        cout << y << endl;
        //        cout << z << endl;
        //        
        //        finalImage = t.test(x, y, z);

        boost::lock_guard<boost::mutex> guard(_mtx);
        int keyPressed = 0;
        finalImage = t.test(0, 1000, -4000);
        std::cout << "Press ESC to continue..." << std::endl;
//        do {
            cv::imshow("Final", finalImage);
//            keyPressed = cv::waitKey(0);
//        } while (keyPressed != 27);



        cv::imshow("Final", finalImage);

        done = true;
    }



    cv::destroyAllWindows();

}

void RealTimeVisualizer::lock() {
    _mtx.lock();
}

void RealTimeVisualizer::unlock() {
    _mtx.unlock();
}
