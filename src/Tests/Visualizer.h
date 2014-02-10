/* 
 * File:   Visualizer.h
 * Author: bruno
 *
 * Created on February 10, 2014, 12:02 PM
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

