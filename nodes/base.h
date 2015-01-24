#ifndef NODES_BASE_H
#define NODES_BASE_H

#include "audio_buffer.h"
#include "object.h"

namespace Nodes {

class Base : public Object {

    public:
    Base(const char *name);
    void attach(Base *other_node);
    void attach_modulator(Base *other_node);
    void detach(void);
    void process(AudioBuffer &audio_buffer);
    void process_replacing(AudioBuffer &audio_buffer);
    Base *parent(void);
    Base *modulator(void);

    private:
    virtual void _process(AudioBuffer &audio_buffer) = 0;
    virtual void _process_replacing(AudioBuffer &audio_buffer);
    Base *m_other_node;
    Base *m_modulation_node;
};

}
#endif
