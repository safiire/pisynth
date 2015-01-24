#include "input/manager.h"
#include "input/sources/midi_file.h"
#include "input/sources/test.h"

#include "nodes/voice.h"
#include "nodes/voice_assigner.h"
#include "nodes/portaudio.h"

int
main(){

    //  Create a reuseable buffer
    AudioBuffer buffer(0);

    //  Create some nodes
    using namespace Nodes;

    VoiceAssigner voice_assigner;
    //Voice voice("Voice");
    PortAudio portaudio("Port Audio");

    //  Attach them together
    portaudio.attach(&voice_assigner);
    portaudio.process(buffer);

    //  Start processing input
    Input::Sources::MidiFile source("midi_files/guitar.mid");
    Input::Sources::Test test;
    Input::Manager &im = Input::Manager::instance();
    //im.add_source(&test);
    im.add_source(&source);
    im.process();

    return 0;
}
