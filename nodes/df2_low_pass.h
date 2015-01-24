#ifndef NODES_DF2_LOWPASS_H
#define NODES_DF2_LOWPASS_H

#include "base.h"
#include "audio_buffer.h"

namespace Nodes {

class DF2LowPass : public Base{

    public:
    float m_b0;
    float m_a1;
    float m_y_of_n_minus_1;

    DF2LowPass(const char *name);
    void feedback(float feedback);
    void _process(AudioBuffer &audio_buffer);
};

}
#endif
