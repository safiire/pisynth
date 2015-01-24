#include "input/sources/test.h"

namespace Input{ namespace Sources {

////
//  Constructor
Test::Test() : Base() { 
  init_events();
}


////
//  Here's a test/fake input source
void Test::init_events() {
    using namespace Midi;

    // A
    m_event_queue.push(new Event(0,   0x90, 69, 127));
    m_event_queue.push(new Event(128, 0x80, 69, 0));

    // C
    m_event_queue.push(new Event(128, 0x90, 72, 127));
    m_event_queue.push(new Event(128, 0x80, 72, 0));

    // E
    m_event_queue.push(new Event(128, 0x90, 76, 127));
    m_event_queue.push(new Event(128, 0x80, 76, 0));


    // G#
    m_event_queue.push(new Event(128, 0x90, 68, 127));
    m_event_queue.push(new Event(128, 0x80, 68, 0));

    // B
    m_event_queue.push(new Event(128, 0x90, 71, 127));
    m_event_queue.push(new Event(128, 0x80, 71, 0));

    // D
    m_event_queue.push(new Event(128, 0x90, 74, 127));
    m_event_queue.push(new Event(128, 0x80, 74, 0));
}

}}
