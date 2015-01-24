#include "base.h"

namespace Nodes {

////
//  Give the node a name
Base::Base(const char *name) : Object(name), m_other_node(NULL), m_modulation_node(NULL){ }

////
//  Attach this node to another
void Base::attach(Base *other_node){
    m_other_node = other_node;
}


////
//  Attach this node to another
void Base::attach_modulator(Base *other_node){
    m_modulation_node = other_node;
}


////
//  Detach whatever is attached
void Base::detach(void){
    m_other_node = NULL;
}


////
//  Detach whatever is attached
Base *Base::parent(void){
    return m_other_node;
}


////
//  Return the modulator
Base *Base::modulator(void){
    return m_modulation_node;
}


////
//  The wrapper for processing a buffer
void Base::process(AudioBuffer &audio_buffer){
    if(m_other_node){
        m_other_node->process(audio_buffer);
    }
    _process(audio_buffer);
}


////
//  The wrapper for process_replacing
void Base::process_replacing(AudioBuffer &audio_buffer){
    if(m_other_node){
        m_other_node->process_replacing(audio_buffer);
    }
    _process_replacing(audio_buffer);
}


////
//  Default implementation of process replacing
//  Simply use the sub-class's _process() but zero the buffer first.
void Base::_process_replacing(AudioBuffer &audio_buffer){
    if(!audio_buffer.zeroed()){
        audio_buffer.zero();
    }
    _process(audio_buffer);
}

}
