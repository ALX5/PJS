/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#include "../Main.h"
#define SAMPLES_CONFIG_PATH "../src/SamplesConfig.xml"

class Calibration
{
public :
    Calibration();
    void calibrationDisplay();
    void launchCalibration();
    Context context;

private :
    DepthGenerator depthCamera;
    ImageGenerator rgbCamera;
    DepthMetaData depthCameraMD;
    ImageMetaData rgbCameraMD;

    XnRGB24Pixel* texMap;
    unsigned int texMapX;
    unsigned int texMapY;

    float* pDepthHist;
    XnDepthPixel nZRes;

    void initContext();
};
