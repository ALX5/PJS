/* 
 * File:   X11Tests.h
 * Author: bruno
 *
 * Created on February 6, 2014, 2:01 PM
 */

#ifndef X11TESTS_H
#define	X11TESTS_H

class X11Tests {
public:
    X11Tests();
    X11Tests(const X11Tests& orig);
    virtual ~X11Tests();
    
    void test();
    void testGetScreenSize();
    
private:

};

#endif	/* X11TESTS_H */

