/* 
 * File:   TestSources.h
 * Author: bruno
 *
 * Created on January 6, 2014, 11:58 AM
 */

#ifndef TESTSOURCES_H
#define	TESTSOURCES_H

class TestSources {
public:
    int singlePlaneTest();
    int createImageTest();
    int twoPlanesTest();
    TestSources();
    TestSources(const TestSources& orig);
    virtual ~TestSources();
private:

};

#endif	/* TESTSOURCES_H */

