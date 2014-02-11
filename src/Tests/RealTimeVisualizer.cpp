/* 
 * File:   RealTimeVisualizer.cpp
 * Author: bruno
 * 
 * Created on February 10, 2014, 11:46 AM
 */

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
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
//        DummyTracker tracker;
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

        //Init time
//        boost::posix_time::ptime initTime = boost::date_time::microsec_clock::local_time();
        
        int keyPressed = 0;
        cv::Point3f pos = tracker.getUserPosition();
        if(!originalImage){
            finalImage = t.test(pos.x, pos.y, pos.z);
        } else {
            finalImage = original;
        }

        cv::imshow("Final", finalImage);
        keyPressed = cv::waitKey(10);
        if (keyPressed == 27 || keyPressed == 1048603) {
            done = true;
            tracker.stop();
        } else if (keyPressed == 1048585 || keyPressed == 9 ){
            originalImage = !originalImage;
        }
       
 ;
//        boost::posix_time::ptime endTime = boost::date_time::microsec_clock::local_time();
        
//        std::cout << "Time: " << endTime - initTime << std::endl;
                
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
