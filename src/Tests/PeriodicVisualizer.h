/* 
 * File:   PeriodicVisualizer.h
 * Author: bruno
 *
 * Created on February 10, 2014, 12:00 PM
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

