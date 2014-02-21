/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#ifndef REALTIMEVISUALIZER_H
#define	REALTIMEVISUALIZER_H

#include <boost/thread.hpp>
#include "Visualizer.h"

class RealTimeVisualizer : public Visualizer{
public:
    RealTimeVisualizer();
    RealTimeVisualizer(const RealTimeVisualizer& orig);
    virtual ~RealTimeVisualizer();
    
    virtual void visualize();
    
    //    void lock();
    //    void unlock();
private:

    //    boost::mutex _mtx;
    
};

#endif	/* VISUALIZER_H */

