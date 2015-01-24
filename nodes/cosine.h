#ifndef NODES_COSINE_H
#define NODES_COSINE_H

#include <math.h>
#include "base.h"
#include "audio_buffer.h"

namespace Nodes {

static const float Tau = 6.28318531;

class Cosine : public Base {


    public:
    float m_theta;
    float m_f;

    Cosine(const char *name);
    void _process(AudioBuffer &audio_buffer);
    virtual void midi_callback(Midi::Event &midi);
};

}
#endif
