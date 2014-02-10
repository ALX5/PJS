/* 
 * File:   RealTimeVisualizer.cpp
 * Author: bruno
 * 
 * Created on February 10, 2014, 11:46 AM
 */

#include "RealTimeVisualizer.h"
#include "DummyTracker.h"
#include "Tracking.h"
#include "TestProjection.h"

RealTimeVisualizer::RealTimeVisualizer() {
}

RealTimeVisualizer::RealTimeVisualizer(const RealTimeVisualizer& orig) {
}

RealTimeVisualizer::~RealTimeVisualizer() {
}

void RealTimeVisualizer::visualize() {
    Tracking tracker;
    //    DummyTracker tracker;
    TestProjection t;

    cv::namedWindow("Final", CV_WINDOW_NORMAL);
    cv::setWindowProperty("Final", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

    cv::Mat finalImage;

    bool done = false;
    bool originalImage = false;

    const char* nom1 = "../src/logo.png";
    cv::Mat original = cv::imread(nom1, CV_LOAD_IMAGE_COLOR);
    if (!original.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        throw std::exception();
    }

    //    boost::thread threadTracking(listen, done);
    //    boost::thread threadTracking(tracker.track);
    //    boost::thread threadTracking(tracker.track);
    //threadTracking.join();
    boost::thread threadedTracking(&Tracking::setupTracking, &tracker);

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


        int keyPressed = 0;
        cv::Point3f pos = tracker.getUserPosition();
        if(!originalImage){
            finalImage = t.test(pos.x, pos.y, pos.z);
        } else {
            finalImage = original;
        }

        std::cout << "Press ESC to continue..." << std::endl;
        std::cout << pos << std::endl;
        //        do {
        cv::imshow("Final", finalImage);
        keyPressed = cv::waitKey(100);
        if (keyPressed == 27 || keyPressed == 1048603) {
            done = true;
        } else if (keyPressed == 1048585){
            originalImage = !originalImage;
        }
        //        } while (keyPressed != 27);


    }



    cv::destroyAllWindows();

}

//void RealTimeVisualizer::lock() {
//    _mtx.lock();
//}
//
//void RealTimeVisualizer::unlock() {
//    _mtx.unlock();
//}
