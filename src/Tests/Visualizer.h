/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#ifndef VISUALIZER_H
#define	VISUALIZER_H

class Visualizer {
public:
    Visualizer();
    Visualizer(const Visualizer& orig);
    virtual ~Visualizer();
    
    virtual void visualize() = 0;
    
    
    
private:

};

#endif	/* VISUALIZER_H */

