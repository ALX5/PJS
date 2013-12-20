/**
 *
 * Based on NiSimpleViewer.cpp
 */

#include "Calibration.h"

void Calibration::glutIdle (void)
{
        // Display the frame
        glutPostRedisplay();
}

void Calibration::glutDisplay (void)
{
        XnStatus rc = XN_STATUS_OK;

        // Read a new frame
        rc = context.WaitAnyUpdateAll();
        if (rc != XN_STATUS_OK)
        {
                printf("Read failed: %s\n", xnGetStatusString(rc));
                return;
        }

        depthCamera.GetMetaData(depthCameraMD);
        rgbCamera.GetMetaData(rgbCameraMD);

        const XnDepthPixel* pDepth = depthCameraMD.Data();

        // Copied from SimpleViewer
        // Clear the OpenGL buffers
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup the OpenGL viewpoint
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, 1280, 1024, 0, -1.0, 1.0);

        // Calculate the accumulative histogram (the yellow display...)
        xnOSMemSet(pDepthHist, 0, nZRes*sizeof(float));

        unsigned int nNumberOfPoints = 0;
        for (XnUInt y = 0; y < depthCameraMD.YRes(); ++y)
        {
                for (XnUInt x = 0; x < depthCameraMD.XRes(); ++x, ++pDepth)
                {
                        if (*pDepth != 0)
                        {
                                pDepthHist[*pDepth]++;
                                nNumberOfPoints++;
                        }
                }
        }
        for (int nIndex=1; nIndex<nZRes; nIndex++)
        {
                pDepthHist[nIndex] += pDepthHist[nIndex-1];
        }
        if (nNumberOfPoints)
        {
                for (int nIndex=1; nIndex<nZRes; nIndex++)
                {
                        pDepthHist[nIndex] = (unsigned int)(256 * (1.0f - (pDepthHist[nIndex] / nNumberOfPoints)));
                }
        }

        xnOSMemSet(texMap, 0, texMapX*texMapY*sizeof(XnRGB24Pixel));

        // check if we need to draw image frame to texture

                const XnRGB24Pixel* pImageRow = rgbCameraMD.RGB24Data();
                XnRGB24Pixel* pTexRow = texMap + rgbCameraMD.YOffset() * texMapX;

                for (XnUInt y = 0; y < rgbCameraMD.YRes(); ++y)
                {
                        const XnRGB24Pixel* pImage = pImageRow;
                        XnRGB24Pixel* pTex = pTexRow + rgbCameraMD.XOffset();

                        for (XnUInt x = 0; x < rgbCameraMD.XRes(); ++x, ++pImage, ++pTex)
                        {
                                *pTex = *pImage;
                        }

                        pImageRow += rgbCameraMD.XRes();
                        pTexRow += texMapX;
                }

        // check if we need to draw depth frame to texture
        /*if (g_nViewState == DISPLAY_MODE_OVERLAY ||
                g_nViewState == DISPLAY_MODE_DEPTH)
        {
                const XnDepthPixel* pDepthRow = depthCameraMD.Data();
                XnRGB24Pixel* pTexRow = texMap + depthCameraMD.YOffset() * texMapX;

                for (XnUInt y = 0; y < depthCameraMD.YRes(); ++y)
                {
                        const XnDepthPixel* pDepth = pDepthRow;
                        XnRGB24Pixel* pTex = pTexRow + depthCameraMD.XOffset();

                        for (XnUInt x = 0; x < depthCameraMD.XRes(); ++x, ++pDepth, ++pTex)
                        {
                                if (*pDepth != 0)
                                {
                                        int nHistValue = pDepthHist[*pDepth];
                                        pTex->nRed = nHistValue;
                                        pTex->nGreen = nHistValue;
                                        pTex->nBlue = 0;
                                }
                        }

                        pDepthRow += depthCameraMD.XRes();
                        pTexRow += texMapX;
                }
        }*/

        // Create the OpenGL texture map
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texMapX, texMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, texMap);

        // Display the OpenGL texture map
        glColor4f(1,1,1,1);

        glBegin(GL_QUADS);

        int nXRes = depthCameraMD.FullXRes();
        int nYRes = depthCameraMD.FullYRes();

        // upper left
        glTexCoord2f(0, 0);
        glVertex2f(0, 0);
        // upper right
        glTexCoord2f((float)nXRes/(float)texMapX, 0);
        glVertex2f(1280, 0);
        // bottom right
        glTexCoord2f((float)nXRes/(float)texMapX, (float)nYRes/(float)texMapY);
        glVertex2f(1280, 1024);
        // bottom left
        glTexCoord2f(0, (float)nYRes/(float)texMapY);
        glVertex2f(0, 1024);

        glEnd();

        // Swap the OpenGL display buffers
        glutSwapBuffers();
}

Calibration::Calibration() { launchCalibration(); }

void Calibration::initContext() {
    context.InitFromXmlFile(SAMPLES_CONFIG_PATH/*,scriptNode*/);
    depthCamera.GetMetaData(depthCameraMD);
    rgbCamera.GetMetaData(rgbCameraMD);
    texMapX=(((unsigned short)(depthCameraMD.FullXRes()-1) / 512) + 1) * 512;
    texMapY = (((unsigned short)(depthCameraMD.FullYRes()-1) / 512) + 1) * 512;
    texMap = (XnRGB24Pixel*)malloc(texMapX * texMapY * sizeof(XnRGB24Pixel));
    nZRes = depthCameraMD.ZRes();
    pDepthHist = (float*)malloc(nZRes * sizeof(float));
}

void Calibration::launchCalibration() {
    initContext();
    // OpenGL init
    char *myargv [1];
    int myargc=1;
    myargv [0]=strdup ("Myappname");
    glutInit(&myargc, myargv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1280, 1024);
    glutCreateWindow ("OpenNI Simple Viewer");
    glutFullScreen();
    glutSetCursor(GLUT_CURSOR_NONE);

    glutDisplayFunc(glutDisplay);
    glutIdleFunc(glutIdle);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // Per frame code is in glutDisplay
    glutMainLoop();
}
