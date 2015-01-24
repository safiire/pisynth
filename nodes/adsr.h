#ifndef NODES_ADSR_H
#define NODES_ADSR_H

#include "base.h"
#include "gate.h"
#include "df2_low_pass.h"
#include "audio_buffer.h"

namespace Nodes {

class ADSR : public Base {

    private:
    Gate m_gate;
    DF2LowPass m_lp;
    Object *m_voice;

    public:
    ADSR(const char *name, Object *voice = NULL);
    void on(float velocity);
    void off(void);
    void _process(AudioBuffer &audio_buffer);
    void midi_callback(Midi::Event &event);
};

}
#endif
