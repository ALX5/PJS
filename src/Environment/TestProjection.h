/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#ifndef TESTPROJECTION_H
#define	TESTPROJECTION_H
#include <opencv2/opencv.hpp>

class TestProjection {
public:
    TestProjection();
    TestProjection(const TestProjection& orig);
    virtual ~TestProjection();
    
    cv::Mat test(double userX, double userY, double userZ);
    
private:

};

#endif	/* TESTPROJECTION_H */

