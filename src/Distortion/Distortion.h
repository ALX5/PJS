#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <opencv/highgui.h>
#include <opencv2/calib3d/calib3d.hpp>
#include "plane.h"

using namespace std;

class Distortion
{
private:

public:
    Distortion();

    void onePlane();
};
