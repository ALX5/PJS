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

using namespace std;

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
    void determineHomographies(vector<Plane> a, vector<Plane> b);
    
    /**
     * This function retrieves every homography present in vector homographies and
     * transform the corresponding region of the image with it
     * @param image
     * @return 
     */
    vector<Mat> applyTransformation(Mat image);
    
private:
    vector<Mat> homographies;
    
};

#endif	/* HOMOGRAPHYCALCULATOR_H */

