/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv/highgui.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class Calib
{
public:
    Calib();
    vector<Mat> rotationVectors;
    vector<Mat> translationVectors;


private:

};
