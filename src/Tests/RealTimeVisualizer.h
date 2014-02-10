/* 
 * File:   RealTimeVisualizer.h
 * Author: bruno
 *
 * Created on February 10, 2014, 11:46 AM
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

