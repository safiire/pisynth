#include "nodes/voice_assigner.h"

namespace Nodes {

////
//  Here I will instantiate a vector of Voices
VoiceAssigner::VoiceAssigner() : Base("Voice Assigner"){ 

    for(unsigned int i = 0; i < NumVoices; i++){
        printf("Creating voice #%d\n", i);
        m_voices.push_back(new Voice("Voice"));
    }

    for(unsigned int i = 0; i < NumMidiNotes; i++){
        m_notes_playing[i] = NULL;
    }

    //  Register for Midi Events to assign to voices
    using namespace Midi;
    Input::Manager &im = Input::Manager::instance();
    im.midi_request(MidiNoteOff, this);
    im.midi_request(MidiNoteOn,  this);
}


////
//  Clean up
VoiceAssigner::~VoiceAssigner(){
    for(unsigned int i = 0; i < m_voices.size(); i++){
        delete m_voices[i];
    }
}

////
//  This _process method renders the active voices and 
//  also acts as a voice mixer
void VoiceAssigner::_process(AudioBuffer &mix){
    AudioBuffer voice_buffer(mix.size());

    foreach(Voice *voice, m_voices){
        if(voice->busy()){
            voice->process(voice_buffer);
            for(unsigned int i = 0; i < mix.size(); i++){
                mix[i] += voice_buffer[i];
            }
            for(unsigned int i = 0; i < mix.size(); i++){
                mix[i] /= Headroom;
            }
        }
    }
}


////
//  Look for a free voice which isn't assigned to anything
Voice *VoiceAssigner::find_free_voice(){
    foreach(Voice *voice, m_voices){
        if(! voice->busy()){
            return voice;
        }
    }
    return NULL;
}


////
//  Assign a voice to handle a midi event
void VoiceAssigner::assign_note_on(Midi::Event &event){
    Voice *voice_to_assign = NULL;

    //  Is this note already playing?  Retrigger with same voice
    voice_to_assign = m_notes_playing[event.parameter1()];
    if(!voice_to_assign){
        voice_to_assign = find_free_voice();
    }

    //  Assign it if we now have a voice
    if(voice_to_assign){
        printf("Actually found a voice\n");
        m_notes_playing[event.parameter1()] = voice_to_assign;
        voice_to_assign->midi_callback(event);
    }
}


////
//  Find the voice that is playing this note and send it the off message
void VoiceAssigner::assign_note_off(Midi::Event &event) {
    Voice *voice_to_assign = m_notes_playing[event.parameter1()];

    if(voice_to_assign){
        printf("Found it, telling it to turn off\n");
        voice_to_assign->midi_callback(event);
        //m_notes_playing[event.parameter1()] = NULL;
    }
}


////
//  Here we must assign a voice to handle a midi event
void VoiceAssigner::midi_callback(Midi::Event &event){ 
    using namespace Midi;
    
    switch(event.message_type()){
    case MidiNoteOn:
        printf("Processing Note On\n");
        assign_note_on(event);
        break;

    case MidiNoteOff:
        printf("Processing Note Off\n");
        assign_note_off(event);
        break;
    }
}

}

