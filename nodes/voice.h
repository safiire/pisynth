#ifndef NODES_VOICE_H
#define NODES_VOICE_H

#include "nodes/base.h"
#include "nodes/cosine.h"
#include "nodes/adsr.h"

namespace Nodes {

    class Voice: public Base {
        private:
        Base *m_oscillator1;
        ADSR  m_adsr1;
        bool  m_busy;

        public:
        Voice(const char *name);
        ~Voice();
        void sysex_env_closed(Midi::Event &event);
        bool busy() const { return m_busy; }
        void _process(AudioBuffer &audio_buffer);
        virtual void midi_callback(Midi::Event &event);
    };
}
#endif
