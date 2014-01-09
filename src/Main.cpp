/**
 *
 */

#include "Main.h"
#include "Calibration/Calibration.h"

int main(int argc, char *argv[]) {

    /// Distorsions correction.
    //Define the planes. The first one represents the distorted image.
    //The second one represents the points where the first plane should sit
    Plane p1(Point2f(302,110), Point2f(310,294), Point2f(500,139), Point2f(501,309));
    Plane p2(Point2f(500,139), Point2f(501,309), Point2f(617,122), Point2f(610,334));
    Plane p3(Point2f(300,100), Point2f(300,522), Point2f(511,100), Point2f(511,522));
    Plane p4(Point2f(511,100), Point2f(511,522), Point2f(722,100), Point2f(722,522));

    //Put the planes in vectors
    //The homography calculator takes plane vectors
    //in order to apply different transformations to different regions
    vector<Plane> a;
    a.push_back(p1);
    a.push_back(p2);

    vector<Plane> b;
    b.push_back(p3);
    b.push_back(p4);

    //Calculate the homography
    HomographyCalculator hc;
    hc.determineHomographies(a, b);

    //Load the image
    const char* nom1 = "../src/projection01.png";
    Mat img = imread(nom1, CV_LOAD_IMAGE_GRAYSCALE);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        return -1;
    }

    //Get the transformed image
    vector<Mat> transformedImages = hc.applyTransformation(img);

    CvRect roi1 = cvRect(300, 100, 211, 422);
    CvRect roi2 = cvRect(511, 100, 211, 422);

    Mat transformedLeft = Mat(transformedImages.at(0), roi1);
    Mat transformedRight = Mat(transformedImages.at(1), roi2);

    // Combine views
    Mat combine = Mat(max(transformedLeft.rows, transformedRight.rows), transformedLeft.cols + transformedRight.cols, CV_8UC1);

    CvRect left = cvRect(0, 0, transformedLeft.cols, transformedLeft.rows);
    CvRect right = cvRect(transformedLeft.cols, 0, transformedRight.cols, transformedRight.rows);

    Mat leftCombine = Mat(combine, left);
    Mat rightCombine = Mat(combine, right);

    transformedLeft.copyTo(leftCombine);
    transformedRight.copyTo(rightCombine);

    //And show it
    imshow("Transformed image", combine);

    waitKey(0);

    /// Camera calibration.
    Calibration c;
    c.launchCalibration(argc,argv);

    /// User tracking.*/
}
