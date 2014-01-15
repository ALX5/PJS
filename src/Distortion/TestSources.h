/* 
 * File:   TestSources.h
 * Author: bruno
 *
 * Created on January 6, 2014, 11:58 AM
 */

#ifndef TESTSOURCES_H
#define	TESTSOURCES_H

#include <opencv2/opencv.hpp>
#include <vector>

class TestSources {
public:
    int twoPlanesTest();
    std::vector<cv::Mat> divideImageInTwo(cv::Mat&);
    cv::Mat joinImagesAtMiddle(cv::Mat&, cv::Mat&);
    
    TestSources();
    TestSources(const TestSources& orig);
    
    virtual ~TestSources();
private:

};

#endif	/* TESTSOURCES_H */

