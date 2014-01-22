/* 
 * File:   Surface.h
 * Author: bruno
 *
 * Created on January 20, 2014, 4:22 PM
 */

#ifndef SURFACE_H
#define	SURFACE_H

#include "plane.h"

class Surface {
    friend class Utils;
public:

    Surface();
    Surface(Plane &src, Plane &dst, Mat image);
    Surface(const Surface& orig);
    virtual ~Surface();
    
    /**
     * Finds the homography between the source and destination
     * planes and then stores it
     */
    void determineHomography();
    
    /**
     * Calculates the transformed plane using the stored homography
     * and stores it
     */
    void calculateTransformedPlane();
    
    /**
     * Subtracts the given vector from the homography translation
     * @param offsets
     */
    void adjustTranslations(Point2f &offsets);
    
    /**
     * Transforms the original image using the stored homography stored in
     * field homography
     */
    void applyHomography();
    
    /**
     * Moves this surface so that the upper left corner of its bounding box
     * is on the specified point
     * @param point
     */
    void correctBBPosition(Point2f& point);
    
    /**
     * Moves this surface so that its upper left corner
     * is on the specified point
     * @param point
     */
    void correctPosition(Point2f& point);
    
    /**
     * Sets the upper right reconstruction algorithm child surface
     * @param 
     */
    void setUpperRightChild(Surface&);
    
    /**
     * Sets the lower right reconstruction algorithm child surface
     * @param 
     */
    void setLowerRightChild(Surface&);
    
    /**
     * Sets the lower left reconstruction algorithm child surface
     * @param 
     */
    void setLowerLeftChild(Surface&);
    
    /**
     * This function adds an alpha channel to the transformed image
     * and makes everything outside the transformed plane transparent
     */
    void addTransparency();
    
    /**
     * Prints data about this surface
     */
    void print();

    /**
     * Prints data about this surface, using the specified name
     */
    void print(const char *name);
    
    Point2f getUpperLeftCorner();
    Point2f getLowerLeftCorner();
    Point2f getUpperRightCorner();
    Point2f getLowerRightCorner();    
    
    /**
     * Shows the transformed image
     */
    void display();
    
    /**
     * Shows the transformed image using the given string as window name
     */
    void display(const char *name);
    
    /**
     * Saves the transformed image to drive
     */
    void save();
    
    /**
     * Saves the transformed image to drive, using the given string 
     * as filename
     */
    void save(const char* name);
    
    
    //Getters and setters
    Size getSize();
    
private:
    Plane sourcePlane;
    Plane destinationPlane;
    Plane transformedRegion;
    Mat homography;
    Mat image;
    Mat transformedImage;
    Size size;
    
    Surface* upperRightChild;
    Surface* lowerRightChild;
    Surface* lowerLeftChild;
     
};

#endif	/* SURFACE_H */

