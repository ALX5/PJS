/**
 * File:   Main.cpp
 * Author: Alexis Linke, Jonathan Mathieu and Bruno Ordozgoiti.
 *
 * Released on Febuary 20, 2014
 */

#ifndef EVENTHANDLER_H
#define	EVENTHANDLER_H

class EventHandler {
public:
    EventHandler();
    EventHandler(const EventHandler& orig);
    virtual ~EventHandler();
    
    
    void listen(bool &done);
    
private:

};

#endif	/* EVENTHANDLER_H */

