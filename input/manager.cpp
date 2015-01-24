#include "manager.h"

namespace Input {

////
//  Constructor for Input Manager Singleton, sets default midi rate 145
Manager::Manager(void) : m_midi_tick(0) {
    set_midi_rate(145, 96);
}


////
//  Add an input source
void Manager::add_source(Sources::Base *source){
    m_source_list.push_back(source);
}


////
//  Remove an input source
void Manager::remove_source(Sources::Base *source){
    m_source_list.remove(source);
    // TODO:  Also remove it from the MidiMap
}


////
//  Register an object that can receive events
void Manager::register_object(Object *object){
    m_object_list.push_back(object);
}


////
//  Unregister an object
void Manager::unregister_object(Object *object){
    m_object_list.remove(object);
}


////
//  Print out which objects are registered
void Manager::print_registered_objects() {
    printf("Registered Objects:\n");
    foreach(Object *obj, m_object_list){
        printf("- %s\n", obj->name());
    }
}


////
//  Object requests specific type of midi message to be forwarded to it
//  Objects are stored in a multimap keyed by 4-bit Midi Message Type
void Manager::midi_request(int midi_message_type, Object *obj){
    m_midi_requests.insert(std::pair<int, Object*>(midi_message_type, obj));
}


////
//  Dispatch a Midi event to objects who have requested the message type
void Manager::dispatch(Midi::Event &event) {
    int message_type = event.message_type();

    typedef MidiRequestMap::iterator Iter;
    typedef std::pair<Iter, Iter> Pairs;
    Iter it;
    Pairs pairs;

    pairs = m_midi_requests.equal_range(message_type);
    for(it = pairs.first; it != pairs.second; ++it){
        (*it).second->midi_callback(event);
    }
}


////
//  Set the midi rate using bpm with specified tick divisions
void Manager::set_midi_rate(int bpm, int divisions){
    m_bpm = bpm;
    m_divisions = divisions;
    memset(&m_period, 0, sizeof(timespec));
    memset(&m_start_time, 0, sizeof(timespec));
    m_period.tv_nsec = ((60.0 / m_bpm) / m_divisions) * 1000000000;
    m_period.tv_sec = m_period.tv_nsec / 1000000000;  //  Integer division
    m_period.tv_nsec -= m_period.tv_sec * 1000000000;
    printf("@ %f bpm with %f divisions, MIDI clock is running at %ds:%ldns\n", m_bpm, m_divisions, (int)m_period.tv_sec, (long int)m_period.tv_nsec);
}


////
//  Convert seconds to midi ticks for current bpm
int Manager::seconds_to_midi_ticks(float s) const {
    return (60 / m_bpm) / s;
}


////
//  Process input from all sources
void Manager::process(void){
    Midi::Event *event;
    clock_gettime(&m_start_time);
    ADD_MACH_TIMESPEC(&m_start_time, &m_period);

    while(1){
        nanosleep(&m_period, NULL);
        // Dispatch input from each source for this tick
        foreach(Sources::Base *source, m_source_list){
            while(NULL != (event = (*source)[m_midi_tick])){
                //event->print();
                dispatch(*event);
            }
        }
        m_midi_tick++;
        ADD_MACH_TIMESPEC(&m_start_time, &m_period);
    }
}


////
//  Get a timespec
int Manager::clock_gettime(struct timespec *ts){
    #ifdef __MACH__
        clock_serv_t cclock;
        mach_timespec_t mts;
        host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
        clock_get_time(cclock, &mts);
        mach_port_deallocate(mach_task_self(), cclock);
        ts->tv_sec = mts.tv_sec;
        ts->tv_nsec = mts.tv_nsec;
    #else
        clock_gettime(CLOCK_MONOTONIC, &ts);
    #endif
    return 0;
}

} 
