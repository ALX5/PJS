#include "Distortion.h"

Distortion::Distortion()
{
}

void Distortion::onePlane()
{
    // Definition of the distored image's plane
    Point2f distoredP1(306,24);
    Point2f distoredP2(610,84);
    Point2f distoredP3(610,455);
    Point2f distoredP4(306,515);

    vector<Point2f> distoredPlane;
    distoredPlane.push_back(distoredP1);
    distoredPlane.push_back(distoredP2);
    distoredPlane.push_back(distoredP3);
    distoredPlane.push_back(distoredP4);

    // Definition of normal image's plane
    Point2f normalP1(0,0);
    Point2f normalP2(422,0);
    Point2f normalP3(422,422);
    Point2f normalP4(0,422);

    vector<Point2f> normalPlane;
    normalPlane.push_back(normalP1);
    normalPlane.push_back(normalP2);
    normalPlane.push_back(normalP3);
    normalPlane.push_back(normalP4);

    // Calculation of the homography between distored image and normal image
    Mat homography = findHomography(distoredPlane, normalPlane);

    homography.at<double>(0,2) = 0;
    homography.at<double>(1,2) = 69;

    // normal image loading
    const char* nom = "../src/grid-straight.png";
    Mat normalImg = imread(nom, CV_LOAD_IMAGE_COLOR);
    if (!normalImg.data)
        std::cout << " --(!) Error reading image" << std::endl;


    // Find the four corners of the transformed image to know the translation
    vector<Point2f> transformedPlane;

    perspectiveTransform(normalPlane, transformedPlane, homography);
    // Homography application on the normal image
    Mat transformedImg;

    warpPerspective(normalImg, transformedImg, homography, Size(1000,1000));

    // Show Image
    imshow("Transformed Image", transformedImg);
    waitKey(0);

}
