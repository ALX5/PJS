/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#ifndef PERIODICVISUALIZER_H
#define	PERIODICVISUALIZER_H

#include "Visualizer.h"

class PeriodicVisualizer : public Visualizer{
public:
    PeriodicVisualizer();
    PeriodicVisualizer(const PeriodicVisualizer& orig);
    virtual ~PeriodicVisualizer();
    
    void visualize();
private:

};

#endif	/* PERIODICVISUALIZER_H */

