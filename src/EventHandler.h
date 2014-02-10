/* 
 * File:   EventHandler.h
 * Author: bruno
 *
 * Created on February 6, 2014, 6:57 PM
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

