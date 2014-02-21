/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#ifndef GEOMETRYUTILS_H
#define	GEOMETRYUTILS_H

class GeometryUtils {
public:
    GeometryUtils();
    GeometryUtils(const GeometryUtils& orig);
    virtual ~GeometryUtils();
    
    /**
     * Rotates the given vector theta degrees around the given axis
     * @param vect The vector to be rotated
     * @param axis The rotation axis
     * @param theta The angle of rotation in radians
     * @return
     */
    cv::Point3f rotateAroundAxis(const cv::Vec3f &vect, const cv::Vec3f &axis,
                                 const double &theta);
    
    /**
     * Yields the normalized version of the given vector
     * @param vect The vector to be normalized
     * @return The normalized version of the given vector
     */
    cv::Vec3f normalizeVector(const cv::Vec3f &vect);
    
    /**
     * Calculates the cross product between the given vectors
     * @param vectA
     * @param vectB
     * @return The cross product vector
     */
    cv::Vec3f crossProduct(const cv::Vec3f &vectA, const cv::Vec3f &vectB);
    
    /**
     * Calculates the intersection between a ray and a plane
     * @param ray The ray
     * @param normal The plane normal
     * @param point A point on the plane
     * @return The point where the ray and the plane intersect
     */
    cv::Point3f intersection(const cv::Vec3f &ray, const cv::Point3f &normal,
                             const cv::Point3f &point);
    
    
private:

};

#endif	/* GEOMETRYUTILS_H */

