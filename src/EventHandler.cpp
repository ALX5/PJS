/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
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
