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

    XnRGB24Pixel* texMap = NULL;
    unsigned int texMapX = 0;
    unsigned int texMapY = 0;

    float* pDepthHist;
    XnDepthPixel nZRes;

    void initContext();
};
