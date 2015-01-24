#include "nodes/cosine.h"

namespace Nodes {

////
//  Produces a real time calculated Cosine function
Cosine::Cosine(const char *name) : Base(name), m_theta(0), m_f(0){ }


////
//  Fill the buffer with a cosine at f hz
void Cosine::_process(AudioBuffer &audio_buffer){
    float w;
    Base *adsr = modulator();
    AudioBuffer adsr_buffer(audio_buffer.size(), 1); // 1 is multiplicative identity

    if(adsr){
        adsr->process(adsr_buffer);
    }

    w = Tau * (m_f / 44100.0);
    for(size_t i = 0; i < audio_buffer.size(); i++){
        audio_buffer[i] += cos(w * i + m_theta) * adsr_buffer[i];
    }
    m_theta += w * audio_buffer.size();
}


////
//  Here, respond to external midi messages
void Cosine::midi_callback(Midi::Event &midi) {
    m_f = 440 * pow(2, (midi.parameter1() - 69) / 12.0f);
    printf("Frequency of %d is %f\n", midi.parameter1(), m_f);
}

}
