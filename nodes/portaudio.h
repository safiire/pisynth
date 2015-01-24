#ifndef NODES_PORTAUDIO_H
#define NODES_PORTAUDIO_H

#include <portaudio.h>
#include <stdio.h>
#include "base.h"

namespace Nodes {

class PortAudio : public Base {
    public:
    PortAudio(const char *name);
    ~PortAudio(void);

    private:
    PaStream *m_stream;
    static int pa_callback(const void *input, void *output, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *instance);
    void _process(AudioBuffer &audio_buffer);
};

}
#endif
