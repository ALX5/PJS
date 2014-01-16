/*
 * File:   HomographyCalculator.h
 * Author: bruno
 *
 * Created on December 20, 2013, 6:19 PM
 */

#ifndef HOMOGRAPHYCALCULATOR_H
#define	HOMOGRAPHYCALCULATOR_H

#include "plane.h"
#include <vector>


class HomographyCalculator {
public:
    HomographyCalculator();
    HomographyCalculator(const HomographyCalculator& orig);
    virtual ~HomographyCalculator();

    /**
     * For every plane Ai in vector a, this function finds its homography with
     * plane Bi in vector b and stores it in the homographies vector
     * @param a
     * @param b
     */
    void determineHomographies(std::vector<Plane> a, std::vector<Plane> b);

    /**
     * This method just let's us use the perspective transform with out Plane
     * type
     * @param p
     * @param 
     * @return 
     */
    Plane transformPlane(Plane &p, Mat &h);
    
    /**
     * This function retrieves every homography present in vector homographies and
     * transforms the corresponding region of the image with it
     * @param image
     * @return
     */
    std::vector<Mat> applyTransformation(std::vector<Mat> images);

    //TODO Change this approach. It would be better to have an object that stores
    //all the involved features (plane, image, homography, offset) instead of
    //relying on the order of vectors
    /**
     * Modifies the homographies with the offsets present in the given vector.
     * The offset values are applied to the homographies according to 
     * their order in the vector
     * @param 
     */
    void adjustTranslations(std::vector<Point2f>&);
    
    //TODO not in use right now
    void moveImage(Mat&, Point2f&);
    
    //Getters and setters
    std::vector<Mat> getHomographies();
    
private:
    std::vector<Mat> homographies;
    int nbHomographies;
    Size size;

};

#endif	/* HOMOGRAPHYCALCULATOR_H */
