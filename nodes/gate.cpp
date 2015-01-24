#include "gate.h"

namespace Nodes {

////
//  Produces a rectancular on/off gate
Gate::Gate(const char *name) : Base(name), m_gate(0) { }

 
////
//  Open the gate
void Gate::on(float value = 1){
    m_gate = value;
}


////
//  Close the gate
void Gate::off(void){
    m_gate = 0.f;
}


////
//  Outputs the gate
void Gate::_process(AudioBuffer &audio_buffer) {
    for(unsigned int i = 0; i < audio_buffer.size(); i++){
        audio_buffer[i] = m_gate;
    }
}

}
