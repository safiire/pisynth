#include "portaudio.h"

namespace Nodes {

////
//  Initialize PortAudio
PortAudio::PortAudio(const char *name) : Base(name){
    PaError error;
    error = Pa_Initialize();
    if(error != paNoError){
        printf("PortAudio error: %s\n", Pa_GetErrorText(error));
    }
    //                                   In Out                   Frame Size          # Data
    error = Pa_OpenDefaultStream(&m_stream, 0, 2, paFloat32, 44100, 16, pa_callback, this); 
    if(error != paNoError){
        printf("Cannot create stream: %s\n", Pa_GetErrorText(error));
    }
}


////
//  Initialize PortAudio
PortAudio::~PortAudio(void){
    PaError error;
    error = Pa_Terminate();
    if(error != paNoError){
        printf("PortAudio termination error: %s\n", Pa_GetErrorText(error));
    }
}


////
//  The callback function
int PortAudio::pa_callback(const void *input, void *output, unsigned long frames, 
                           const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *data){
    float *out = (float*) output;
    PortAudio *instance = static_cast<PortAudio*>(data);
    AudioBuffer audio_buffer(frames);
    instance->parent()->process(audio_buffer);

    for(unsigned int i = 0; i < audio_buffer.size(); i++){
        *out++ = audio_buffer[i];
        *out++ = audio_buffer[i];
    }
    return 0;
}

////
//  Process
void PortAudio::_process(AudioBuffer &audio_buffer){
    PaError error;
    error = Pa_StartStream(m_stream);
    if(error != paNoError){
        printf("PortAudio error: %s\n", Pa_GetErrorText(error));
    }
}

}
