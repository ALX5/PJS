#ifndef PLANE_H
#define PLANE_H

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
class Plane {
private:    
    vector<Point2f> points;
public:
    Plane();
    Plane(Point2f, Point2f, Point2f, Point2f);
    Plane(vector<Point2f> points);
    
    vector<Point2f> getPoints();
    Point2f getPoint(int n);
    void setPoints(Point2f, Point2f, Point2f, Point2f);
    
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
    void moveTo(Point2f&);
    
    /**
     * Find the offset from the given point of the upper left corner 
     * of this Plane
     * @param 
     * @return 
     */
    Point2f findOffset(Point2f&);
    
    /**
     * Find the offset from the given point of the upper left corner of the
     * bounding box of this Plane
     * @param 
     * @return 
     */
    Point2f findBBOffset(Point2f&);
    
    /**
     * Returns a horizontally and vertically aligned bounding rectangle 
     * for this plane
     * @return 
     */
    Plane getBoundingBox();
    
    //TODO maybe this shouldn't be a member function
    /**
     * Returns the bounding rectangle for given planes
     * @param 
     * @param 
     * @return 
     */
    Plane getBoundingBox(Plane&, Plane&);
    
    //TODO These functions could save us some headaches
    Point2f getUpperLeftCorner();
    Point2f getLowerLeftCorner();
    Point2f getUpperRightCorner();
    Point2f getLowerRightCorner();
    
    bool contains(Point2f&);
    
};

std::ostream &operator<<(std::ostream &os, Plane &m);

#endif // PLANE_H
