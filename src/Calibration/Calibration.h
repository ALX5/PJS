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

    XnRGB24Pixel* texMap;
    unsigned int texMapX;
    unsigned int texMapY;

    float* pDepthHist;
    XnDepthPixel nZRes;

    void launchCalibration(int argc, char *argv[]);
    void initContext();
};
