#ifndef _POLLER_H_
#define _POLLER_H_
#include <map>

#include "Event.h"

class Poller
{
public:
    virtual ~Poller();

    virtual bool addIOEvent(IOEvent* event) = 0;
    virtual bool updateIOEvent(IOEvent* event) = 0;
    virtual bool removeIOEvent(IOEvent* event) = 0;
    virtual void handleEvent() = 0;

protected:
    Poller(); //只允许构造子类实例

protected:
    typedef std::map<int, IOEvent*> IOEventMap;
    IOEventMap mEventMap;
};

#endif //_POLLER_H_