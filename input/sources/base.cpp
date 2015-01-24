#include "input/sources/base.h"

namespace Input{ namespace Sources {

////
//  Base class for an Input Source
Base::Base(void) : m_last_output_tick(0) { 
    init_events();
}


////
//  Check the source for an event, these events will
Midi::Event *Base::operator[](const int midi_tick){
    if(m_event_queue.empty()){
        return NULL;
    }

    Midi::Event *event = m_event_queue.front();
    unsigned int now_delta = midi_tick - m_last_output_tick;
    if(event->delta() == now_delta){
        m_event_queue.pop();
        m_last_output_tick = midi_tick;
        return event;  //  This is leaking memory right here, maybe some kind of smart pointer would be good.
    }else{
        return NULL;
    }
}

}} 
