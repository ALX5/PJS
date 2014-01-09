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
    void glutIdle (void);
    void glutDisplay (void);
    void glutKeyboard(unsigned char key);

    Context context;
    ScriptNode scriptNode;
    DepthGenerator depthCamera;
    ImageGenerator rgbCamera;
    DepthMetaData depthCameraMD;
    ImageMetaData rgbCameraMD;

    XnRGB24Pixel* texMap = NULL;
    unsigned int texMapX = 0;
    unsigned int texMapY = 0;

    float* pDepthHist;
    XnDepthPixel nZRes;

    void launchCalibration(int argc, char *argv[]);
    void initContext();
};
