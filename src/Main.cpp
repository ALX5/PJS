/**
 *
 */

#include "Main.h"
#include "Calibration/Calibration.h"

int main(int argc, char *argv[]) {

    //sift = cv2.SIFT();
    /// Distorsions correction.
    //Define the planes. The first one represents the distorted image.
    //The second one represents the points where the first plane should sit
    Plane p1(Point2f(0,0), Point2f(0,422), Point2f(422,0), Point2f(422,422));
    Plane p2(Point2f(306,24), Point2f(306,515), Point2f(610,84), Point2f(610,455));

    //Put the planes in vectors
    //The homography calculator takes plane vectors
    //in order to apply different transformations to different regions
    vector<Plane> a;
    a.push_back(p1);

    vector<Plane> b;
    b.push_back(p2);

    //Calculate the homography
    HomographyCalculator hc;
    hc.determineHomographies(a, b);

    //Load the image
    const char* nom1 = "../src/grid-straight.png";
    Mat img = imread(nom1, CV_LOAD_IMAGE_GRAYSCALE);
    if (!img.data) {
        std::cout << " --(!) Error reading image" << std::endl;
        return -1;
    }

    // Image Warping
    vector<Mat> transformedImages = hc.applyTransformation(img);

    //And show it
    imshow("Transformed image", transformedImages.at(0));
    waitKey(0);

    /*/// Camera calibration.
    Calibration *c = new Calibration();

    /// User tracking.*/
}
