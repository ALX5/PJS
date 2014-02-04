#include "../Main.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/core/core.hpp"
#include "opencv/highgui.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class Tracking
{
public :
    Tracking();
    int setupTracking (int argc, char *argv[], Mat rot, Mat trsl);
};
