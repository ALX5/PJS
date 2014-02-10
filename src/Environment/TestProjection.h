/* 
 * File:   TestProjection.h
 * Author: bruno
 *
 * Created on January 28, 2014, 3:33 PM
 */

#ifndef TESTPROJECTION_H
#define	TESTPROJECTION_H

class TestProjection {
public:
    TestProjection();
    TestProjection(const TestProjection& orig);
    virtual ~TestProjection();
    
    int test(double userX, double userY, double userZ, int keyPressed);
    
private:

};

#endif	/* TESTPROJECTION_H */

