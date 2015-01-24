#ifndef NODES_VOICE_ASSIGNER_H
#define NODES_VOICE_ASSIGNER_H

#include <boost/foreach.hpp>
#include "nodes/base.h"
#include "nodes/voice.h"

namespace Nodes {

    static const unsigned int NumVoices = 8;
    static const float Headroom = 8.0;
    static const unsigned int NumMidiNotes = 128;

    class VoiceAssigner: public Base {
        private:
        std::vector<Voice *> m_voices;
        Voice *m_notes_playing[NumMidiNotes];

        public:
        VoiceAssigner();
        ~VoiceAssigner();
        void assign_note_on(Midi::Event &event);
        void assign_note_off(Midi::Event &event);
        Voice *find_free_voice();
        void _process(AudioBuffer &audio_buffer);
        void midi_callback(Midi::Event &event);
    };
}

#endif
