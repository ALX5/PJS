/* 
 * File:   TestProjection.h
 * Author: bruno
 *
 * Created on January 28, 2014, 3:33 PM
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

