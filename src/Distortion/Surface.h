/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#ifndef SURFACE_H
#define	SURFACE_H

#include "Plane2d.h"

class Surface {
    friend class Utils;
public:

    Surface();
    Surface(Plane2d &src, Plane2d &dst);
    Surface(Plane2d &src, Plane2d &dst, cv::Mat image);
    Surface(const Surface& orig);
    virtual ~Surface();
    
    /**
     * Finds the homography between the member source and destination
     * planes and then stores it
     */
    void determineHomography();
    
    /**
     * Finds the homography between the given source and destination
     * planes and then stores it
     */
    void determineHomography(Plane2d source, Plane2d destination);
    
    /**
     * Calculates the transformed plane using the stored homography
     * and stores it
     */
    void calculateTransformedPlane();
    
    /**
     * Subtracts the given vector from the homography translation
     * @param offsets
     */
    void adjustTranslations(cv::Point2f &offsets);
    
    /**
     * Transforms the original image using the stored homography stored in
     * field homography. The transformed image is written to a matrix of the given
     * size
     */
    void applyHomography();
    
    /**
     * Moves this surface so that the upper left corner of its bounding box
     * is on the specified point
     * @param point
     */
    void correctBBPosition(cv::Point2f& point);
    
    /**
     * Moves this surface so that its upper left corner
     * is on the specified point
     * @param point
     */
    void correctPosition(cv::Point2f& point);
    
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
    
    cv::Point2f getUpperLeftCorner();
    cv::Point2f getLowerLeftCorner();
    cv::Point2f getUpperRightCorner();
    cv::Point2f getLowerRightCorner();
    
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
    cv::Size getSize();
    void setSize(cv::Size size);
    
    void setImage(cv::Mat image);
    
    int getWidth();
    int getHeight();

    //Experimental
    void fixIntersection(Surface &surface);
    
private:
    Plane2d _sourcePlane;
    Plane2d _destinationPlane;
    Plane2d _transformedRegion;
    cv::Mat _homography;
    cv::Mat _affineTransformation;
    cv::Mat _image;
    cv::Mat _transformedImage;
    cv::Size _size;
    
    //TODO
    cv::Point2f offset;
    
    Surface* upperRightChild;
    Surface* lowerRightChild;
    Surface* lowerLeftChild;

    

    
};

namespace pjs{
Plane2d getBoundingBox(Plane2d&, Plane2d&);
}

#endif	/* SURFACE_H */

