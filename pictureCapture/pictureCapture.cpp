#include <XnOS.h>
#include <XnCppWrapper.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace xn;

Context context;
ImageGenerator rgbCamera;
ImageMetaData rgbCameraMD;

int main()
{
    context.InitFromXmlFile("../pictureCapture/SamplesConfig.xml");
    context.FindExistingNode(XN_NODE_TYPE_IMAGE, rgbCamera);

    rgbCamera.GetMetaData(rgbCameraMD);

    cout << rgbCameraMD.XRes() << endl;
    cout << rgbCameraMD.YRes() << endl;

    static char mode = ' ';
    while(mode != 27)
    {
        cv::Mat colorArr[3];
        cv::Mat colorImage;
        const XnRGB24Pixel* pPixel;
        const XnRGB24Pixel* pImageRows;
        pImageRows = rgbCameraMD.RGB24Data();

        colorArr[0] = cv::Mat(rgbCameraMD.YRes(),rgbCameraMD.XRes(),CV_8U);
        colorArr[1] = cv::Mat(rgbCameraMD.YRes(),rgbCameraMD.XRes(),CV_8U);
        colorArr[2] = cv::Mat(rgbCameraMD.YRes(),rgbCameraMD.XRes(),CV_8U);

        for (int y=0; y<rgbCameraMD.YRes(); y++){
            pPixel = pImageRows;
            uchar* Bptr = colorArr[0].ptr<uchar>(y);
            uchar* Gptr = colorArr[1].ptr<uchar>(y);
            uchar* Rptr = colorArr[2].ptr<uchar>(y);

            for(int x=0;x<rgbCameraMD.XRes();++x , ++pPixel){
                Bptr[x] = pPixel->nBlue;
                Gptr[x] = pPixel->nGreen;
                Rptr[x] = pPixel->nRed;
            }

            pImageRows += rgbCameraMD.XRes();
        }


        cv::merge(colorArr,3,colorImage);
        IplImage bgrIpl = colorImage;
        cvSaveImage("image.jpg",&bgrIpl);
        printf("A picture was took.\n");
        printf("Press 'Esc' to quit or 'Enter' to key to take an other picture.\n");
        mode = getchar();
    }
}
