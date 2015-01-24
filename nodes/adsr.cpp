#include "adsr.h"

namespace Nodes {

////
//  Produces a smooth ADSR envelope
ADSR::ADSR(const char *name, Object *voice) : Base(name), 
                                              m_gate(Gate("Gate")), 
                                              m_lp(DF2LowPass("Envelope LowPass")),
                                              m_voice(voice){ 
    m_lp.feedback(0.0005f);
}

 
////
//  Open the envelope
void ADSR::on(float velocity){
    m_gate.on(velocity);
}


////
//  Close the envelope
void ADSR::off(void){
    m_gate.off();
}


////
//  Output the Envelope
void ADSR::_process(AudioBuffer &audio_buffer){

    AudioBuffer envelope(audio_buffer.size());
    m_gate.process(envelope);
    m_lp.process(envelope);

    for(unsigned int i = 0; i < audio_buffer.size(); i++){
        audio_buffer[i] = envelope[i];
    }
    //if(audio_buffer.last() == 0){
        //printf("Envelope has just closed, I should tell %x\n", m_voice);
    //}
}


////
//  Here, respond to external midi
void ADSR::midi_callback(Midi::Event &event) {
    using namespace Midi;
    float velocity = event.parameter2() / 127.0;

    switch(event.message_type()){
    case MidiNoteOn:
        on(velocity);
        break;
    case MidiNoteOff:
        off();
        break;
    }
}

}
