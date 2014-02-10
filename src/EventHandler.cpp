/* 
 * File:   EventHandler.cpp
 * Author: bruno
 * 
 * Created on February 6, 2014, 6:57 PM
 */

#include <opencv2/highgui/highgui.hpp>

#include "EventHandler.h"

EventHandler::EventHandler() {
}

EventHandler::EventHandler(const EventHandler& orig) {
}

EventHandler::~EventHandler() {
}

//TODO I don't like this mechanism
void EventHandler::listen(bool& done) {
    int keyPressed = 0;
    do{
        keyPressed = cv::waitKey(0);
    }while(keyPressed != 27);
    done = true;
}
