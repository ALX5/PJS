/**
 *
 *
 */

#include "../Main.h"

#define SAMPLES_CONFIG_PATH "../src/SamplesConfig.xml"
#define DISPLAY_MODE_OVERLAY        1
#define DISPLAY_MODE_DEPTH                2
#define DISPLAY_MODE_IMAGE                3
#define DEFAULT_DISPLAY_MODE        DISPLAY_MODE_DEPTH

#define GL_WIN_SIZE_X 1280
#define GL_WIN_SIZE_Y 1024

class Calibration
{
public :
    Calibration();
    void glutIdle (void);
    void glutDisplay (void);
    void glutKeyboard(unsigned char key);
    unsigned int g_nViewState = DEFAULT_DISPLAY_MODE;

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


    void launchCalibration();
    void initContext();
};
