/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
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

