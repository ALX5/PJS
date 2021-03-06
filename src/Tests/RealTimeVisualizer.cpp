/* 
 * File:   RealTimeVisualizer.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
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
//    Tracking tracker;
        DummyTracker tracker;
    

    cv::namedWindow("Final", CV_WINDOW_NORMAL);
    cv::setWindowProperty("Final", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);

    cv::Mat finalImage;

    bool done = false;
    bool originalImage = false;

//    const char* filename = "../src/grid-straight2half.png";
//    const char* filename = "../src/logoinv.png";
    const char* filename = "../src/logo.png";
//    const char* filename = "../src/alexis.png";
//    const char* filename = "../src/jon.png";
//    const char* filename = "../src/bruno.png";
//    const char* filename = "../src/avion.png";    
    cv::Mat original = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
    if (!original.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        throw std::exception();
    }

    TestProjection t;
    
//    boost::thread threadedTracking(&Tracking::setupTracking, &tracker);
    boost::thread threadedTracking(&DummyTracker::track, &tracker);
    while (!done) {   

        //Init time
//        boost::posix_time::ptime initTime = boost::date_time::microsec_clock::local_time();
        
        int keyPressed = 0;
        cv::Point3f pos = tracker.getUserPosition();
        if(!originalImage){            
            finalImage = t.test(pos.x, pos.y, pos.z, filename);
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

//        boost::posix_time::ptime endTime = boost::date_time::microsec_clock::local_time();    
//        std::cout << "Time: " << endTime - initTime << std::endl;
                
    }

    cv::destroyAllWindows();

}
