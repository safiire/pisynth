#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <boost/foreach.hpp>
#include <list>
#include <map>

#include "nodes/object.h"
#include "input/sources/base.h"
#include "midi/event.h"

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#ifndef TIMER_ABSTIME
#define TIMER_ABSTIME 0x01
#endif

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif

class Object;

namespace Input {

    class Manager {

        private:
        float m_bpm;
        float m_divisions;
        timespec m_period;
        timespec m_start_time;
        long int m_midi_tick;

        typedef std::list<Object *> ObjectList;
        typedef std::multimap<int, Object *> MidiRequestMap;
        MidiRequestMap m_midi_requests;

        ObjectList m_object_list;
        std::list<Sources::Base *> m_source_list;

        // Hide these default constructors
        Manager();
        Manager(Manager const &);
        void operator=(Manager const &); 

        public:
        static Manager &instance(){
            static Manager instance;
            return instance;
        };

        //  Set Input Sources
        void add_source(Sources::Base *source);
        void remove_source(Sources::Base *source);

        //  Messaging & Registration
        void register_object(Object *object);
        void unregister_object(Object *object);
        void print_registered_objects();
        void midi_request(int midi_message_type, Object *obj);
        void dispatch(Midi::Event &event);

        void set_midi_rate(int bpm, int divisions);
        int seconds_to_midi_ticks(float s) const;
        void process(void);
        int clock_gettime(struct timespec *ts);
    };
}

#endif
