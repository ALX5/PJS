/* 
 * File:   main.cpp
 * Author: bruno
 *
 * Created on December 20, 2013, 9:02 PM
 */

#include "Distortion/TestSources.h"
#include "Tests/PlaneTests.h"

void runTests();

/*
 * 
 */
int main(int argc, char** argv) {
    TestSources t;
    return t.twoPlanesTest();
    
//    runTests();
}

void runTests(){
    PlaneTests planeTests;
    planeTests.testContains();
}