/**
 *
 *
 */

#include "Main.h"

#define SAMPLES_CONFIG_PATH "SamplesConfig.xml"

class Calibration
{
public :
    Calibration();

private :
    Context context;
    //ScriptNode scriptNode;
    DepthGenerator depthCamera;
    ImageGenerator rgbCamera;
    DepthMetaData depthCameraMD;
    ImageMetaData rgbCameraMD;

    XnRGB24Pixel* texMap = NULL;
    unsigned int texMapX = 0;
    unsigned int texMapY = 0;

    float* pDepthHist;
    XnDepthPixel nZRes;


    void launchCalibration();
    void initContext();
    void glutIdle (void);
    void glutDisplay (void);
};
