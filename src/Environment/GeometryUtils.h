/* 
 * File:   GeometryUtils.h
 * Author: bruno
 *
 * Created on January 30, 2014, 10:33 AM
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
    cv::Point3f rotateAroundAxis(const cv::Point3f &vect, const cv::Point3f &axis, 
        const double &theta);
    
    /**
     * Yields the normalized version of the given vector
     * @param vect The vector to be normalized
     * @return The normalized version of the given vector 
     */
    cv::Point3f normalizeVector(const cv::Point3f &vect);
    
    /**
     * Calculates the cross product between the given vectors
     * @param vectA
     * @param vectB
     * @return The cross product vector
     */
    cv::Point3f crossProduct(const cv::Point3f &vectA, const cv::Point3f &vectB);
    
    
    
private:

};

#endif	/* GEOMETRYUTILS_H */

