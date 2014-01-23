/**
 *
 *
 */

#include "../Main.h"
#define SAMPLES_CONFIG_PATH "../src/SamplesConfig.xml"

class Calibration
{
public :
    Calibration();
    void calibrationDisplay();
    void launchCalibration(int argc, char *argv[]);
    Context context;

private :
    DepthGenerator depthCamera;
    ImageGenerator rgbCamera;
    DepthMetaData depthCameraMD;
    ImageMetaData rgbCameraMD;

    //ISO C++ forbids initialization here. We should use constructors
    XnRGB24Pixel* texMap;
    unsigned int texMapX;
    unsigned int texMapY;

    float* pDepthHist;
    XnDepthPixel nZRes;

    void initContext();
};
