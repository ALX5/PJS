
/* 
 * File:   X11Tests.cpp
 * Author: bruno
 * 
 * Created on February 6, 2014, 2:01 PM
 */
#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>
#include "X11Tests.h"
#include "Utils.h"

X11Tests::X11Tests() {
}

X11Tests::X11Tests(const X11Tests& orig) {
}

X11Tests::~X11Tests() {
}

void X11Tests::test() {
    // Open a display.
    Display *d = XOpenDisplay(0);

    if (d) {
        std::cout << "Success" << std::endl;
        // Create the window
        Window w = XCreateWindow(d, DefaultRootWindow(d), 0, 0, 200,
                100, 0, CopyFromParent, CopyFromParent,
                CopyFromParent, 0, 0);

        // Show the window
        XMapWindow(d, w);
        XFlush(d);

        // Sleep long enough to see the window.
//              sleep(10);

        cv::waitKey(0);
    } else {
        std::cerr << "Error" << std::endl;
    }
}

void X11Tests::testGetScreenSize() {
    std::cout << "***************************************" << std::endl;
    std::cout << "          Testing screen size          " << std::endl;
    std::cout << "***************************************" << std::endl;
    cv::Size s = pjs::getScreenSize();
    std::cout << s << std::endl;
    
}

