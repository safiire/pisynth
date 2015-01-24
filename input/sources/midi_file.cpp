#include "input/sources/midi_file.h"

namespace Input{ namespace Sources {

////
//  Constructor
MidiFile::MidiFile(const char *filename) : Base() { 
    m_midi_file.init_from_file(filename);
    m_midi_file.print();
    init_events();
}


////
//  Here we get midi events from a track in a midi file
void MidiFile::init_events() {
    using namespace Midi;
    Track *track = m_midi_file.m_tracks[0];

    foreach(Event *event, track->m_events){
        m_event_queue.push(event);
    }
}

}}
