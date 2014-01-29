#ifndef PLANE2D_H
#define PLANE2D_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "Plane.h"


class Plane2d : public Plane<cv::Point2f>{
    friend class Plane;
private:    
//    std::vector<cv::Point2f> points;

public:
    Plane2d();
    Plane2d(cv::Point2f, cv::Point2f, cv::Point2f, cv::Point2f);
    Plane2d(std::vector<cv::Point2f> points);
    cv::Size getSize();
    
    
    /**
     * Translates this plane so that its bounding box is in the specified point
     */
    void moveBBTo(cv::Point2f &dst);    
    
    /**
     * Translates this plane so that its bounding box is in the origin
     */
    void moveBBToOrigin();
    
    /**
     * Translates this plane so that the upper-left corner is in the 
     * origin
     * @param 
     */
    void moveToOrigin();
    
    
    /**
     * Translates this plane so that the upper-left corner is in the 
     * given location
     * @param 
     */
    void moveTo(cv::Point2f &dst);
    
    /**
     * Find the offset from the given point of the upper left corner 
     * of this Plane
     * @param 
     * @return 
     */
    cv::Point2f findOffset(cv::Point2f&);
    
    /**
     * Find the offset from the given point of the upper left corner of the
     * bounding box of this Plane
     * @param 
     * @return 
     */
    cv::Point2f findBBOffset(cv::Point2f&);
    
    /**
     * Returns a horizontally and vertically aligned bounding rectangle 
     * for this plane
     * @return 
     */
    Plane2d getBoundingBox();
    
    //TODO maybe this shouldn't be a member function
    /**
     * Returns the bounding rectangle for given planes
     * @param 
     * @param 
     * @return 
     */
    Plane2d getBoundingBox(Plane2d&, Plane2d&);
    
    
    /**
     * Returns the rectangle inscribed in this plane
     * 
     * @return 
      
     e.g for plane A, it returns B
         ____________________  
         \        |         |\ 
          \       |         | \
           \   A  |         |  \ 
            \     |         |   \
             \    |    B    |    \
              \   |         |     \
               \  |         |  A   \
                \ |         |       \
                 \|_________|________\

     */
    Plane2d getInnerBox();
    
    
    
    //TODO We should favor sides in cw or ccw fashion to overcome ambiguity
    /**
     * Of the two leftmost points, this functions returns the uppermost
     * @return 
     */
    cv::Point2f getUpperLeftCorner();
    
    /**
     * Of the two uppermost points, this functions returns the rightmost
     * @return 
     */
    cv::Point2f getUpperRightCorner();
    
    /**
     * Of the two rightmost points, this functions returns the one in the bottom
     * @return 
     */
    
    cv::Point2f getLowerRightCorner();    
    /**
     * Of the two points in the bottom, this function returns the leftmost
     * @return 
     */
    cv::Point2f getLowerLeftCorner();

    
    /**
     * Determines if a point is inside this plane
     * @param 
     * @return 
     */
    bool contains(cv::Point2f&);
    
    /**
     * Determines if a point is inside this plane's bounding box
     * @param 
     * @return 
     */
    bool boxContains(cv::Point2f&);
    
    /**
     * Determines if a point is inside this plane's inner box
     * @param 
     * @return 
     */
    bool innerBoxContains(cv::Point2f&);
    
    
    
    int getWidth();
    int getHeight();
    
};


#endif // PLANE_H
