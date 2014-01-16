/* 
 * File:   Utils.h
 * Author: bruno
 *
 * Created on January 16, 2014, 1:29 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#include <opencv2/opencv.hpp>

class Utils {
public:
    Utils();
    Utils(const Utils& orig);
    virtual ~Utils();
    
    void addAlphaChannel(cv::Mat&);
    
    
private:

};

#endif	/* UTILS_H */

