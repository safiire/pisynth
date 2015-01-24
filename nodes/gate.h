#ifndef NODES_GATE_H
#define NODES_GATE_H

#include "base.h"
#include "audio_buffer.h"

namespace Nodes {

class Gate : public Base{

    public:
    float m_gate;

    Gate(const char *name);
    void _process(AudioBuffer &audio_buffer);
    void on(float value);
    void off(void);
};

}
#endif
