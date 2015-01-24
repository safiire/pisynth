#ifndef INPUT_SOURCES_BASE_H
#define INPUT_SOURCES_BASE_H

#include "midi/event.h"
#include <queue>

namespace Input{ namespace Sources {

    class Base {
        protected:
        
        int m_last_output_tick;
        std::queue<Midi::Event*> m_event_queue;
        virtual void init_events(void){ }

        public:
        Base(void);
        Midi::Event *operator[](const int midi_tick);
    };
}}

#endif
