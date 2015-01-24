#ifndef OBJECT_H
#define OBJECT_H

#include "input/manager.h"
#include "midi/event.h"


//  This is the baseclass object that anything wanting to 
//  recieve midi messages should derive from
class Object {

    private:
    const char *m_name;

    public:
    Object(const char *name);
    ~Object();
    const char *name(void) const { return m_name; }
    virtual void midi_callback(Midi::Event &midi);
};

#endif
