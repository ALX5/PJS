/* 
 * File:   Plane.h
 * Author: bruno
 *
 * Created on January 27, 2014, 10:05 AM
 */

#ifndef PLANE_H
#define	PLANE_H
#include <iostream>
#include <vector>

template <class T>
class Plane {
    //TODO Bad design. Plane should not be aware of who inherits from it
    friend class Plane2d;
    friend class Plane3d;
public:

    Plane<T>() {
    }

    Plane<T>(T& t1, T& t2, T& t3, T& t4) {
        points.push_back(t1);
        points.push_back(t2);
        points.push_back(t3);
        points.push_back(t4);
    }

    Plane<T>(std::vector<T> pts) {
        points.push_back(pts.at(0));
        points.push_back(pts.at(1));
        points.push_back(pts.at(2));
        points.push_back(pts.at(3));
    }

    //TODO Move semantics
    Plane<T>(const Plane& orig) {
        points.push_back(orig.points.at(0));
        points.push_back(orig.points.at(1));
        points.push_back(orig.points.at(2));
        points.push_back(orig.points.at(3));
    }

    virtual ~Plane<T>() {
    }

    std::vector<T> getPoints() {
        return points;
    }

    T getPoint(int n) const {
        return points.at(n);
    }

private:
    std::vector<T> points;


};

template <class T>
std::ostream &operator<<(std::ostream &os, Plane<T> &m) {
    os << m.getPoints();
    return os;
}

#endif	/* PLANE_H */

