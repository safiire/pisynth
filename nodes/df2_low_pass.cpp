#include "df2_low_pass.h"

namespace Nodes {

////
//  Direct Form 2 low pass filter
DF2LowPass::DF2LowPass(const char *name) : Base(name), m_b0(0.75), m_a1(0.025), m_y_of_n_minus_1(0){ }


////
//  Set the feedback and therefore the cutoff of the filter
void DF2LowPass::feedback(float feedback){
    m_b0 = feedback;
    m_a1 = 1 - m_b0;
}

 
////
//  Outputs the gate
void DF2LowPass::_process(AudioBuffer &audio_buffer){
    for(unsigned int i = 0; i < audio_buffer.size(); i++){
        m_y_of_n_minus_1 = audio_buffer[i] = m_b0 * audio_buffer[i] + m_a1 * m_y_of_n_minus_1;
    }
}

}
