#ifndef INPUT_SOURCES_MIDI_FILE_H
#define INPUT_SOURCES_MIDI_FILE_H

#include <boost/foreach.hpp>
#include "input/sources/base.h"
#include "midi/file.h"

namespace Input{ namespace Sources {

    class MidiFile : public Base {
        public:
        MidiFile(const char *filename);

        private:
        Midi::File m_midi_file;
        virtual void init_events(void);
    };
} }

#endif
