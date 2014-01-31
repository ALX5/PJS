#include "Calib.h"

Calib::Calib()
{
    Size boardSize(6,5); // Chessboard' size in corners with both color (nb of squares -1)
    int widthSquare = 40; // Width of a square in mm
    int heightSquare = 27;
    vector <Mat> images;

    // Getting the four images of the chessboard
    string imageFileName = "../src/mire1.jpg";
    images.push_back(imread(imageFileName, 1));

    imageFileName = "../src/mire2.jpg";
    images.push_back(imread(imageFileName, 1));

    imageFileName = "../src/mire3.jpg";
    images.push_back(imread(imageFileName, 1));

    imageFileName = "../src/mire4.jpg";
    images.push_back(imread(imageFileName, 1));

    Size imageSize = images.at(0).size();

    // Find chessboard's corners in the scene for the 4 images
    vector<vector<Point2f> > cornersScene(1);
    vector<Mat> imagesGray;

    imagesGray.resize(4);

    for (int i=0; i<4; i++)
    {
        if(images.at(i).empty())
        {
            cerr << "Image not read correctly!" << endl;
            exit(-1);
        }

        bool patternFound = findChessboardCorners(images.at(i), boardSize, cornersScene[0]);
        if(!patternFound)
        {
            cerr << "Could not find chess board!" << endl;
            exit(-1);
        }

        // Improve corner's coordinate accuracy
        cvtColor(images.at(i), imagesGray.at(i), CV_RGB2GRAY);
        cornerSubPix(imagesGray.at(i), cornersScene[0], Size(3,2), Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1));

        // Drawing the corners
        drawChessboardCorners(images.at(i), boardSize, Mat(cornersScene[0]), patternFound );

        imshow("Corners find", images.at(i));
        waitKey();

        int keyPressed;
        do
        {
            keyPressed = waitKey(0);
        } while (keyPressed != 27);
    }

    // Getting the chessboard's corners on the mire's image
    vector<vector<Point3f> > cornersMire(1);

    for( int y = 0; y < boardSize.height; y++ )
      {
        for( int x = 0; x < boardSize.width; x++ )
        {
          cornersMire[0].push_back(cv::Point3f(float(x*widthSquare),
                                    float(y*heightSquare), 0));
        }
      }

    // Getting the camera's parameters
    vector<Mat> rotationVectors;
    vector<Mat> translationVectors;

    Mat distortionCoefficients = Mat::zeros(8, 1, CV_64F);
    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);

    calibrateCamera(cornersMire, cornersScene, imageSize, cameraMatrix,
                    distortionCoefficients, rotationVectors, translationVectors);


    //cout << "Camera matrix: " << cameraMatrix << endl;
    //cout << "Distortion _coefficients: " << distortionCoefficients << endl;

}
