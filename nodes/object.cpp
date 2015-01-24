#include "object.h"

////
//  This baseclass should find the global midi manager and
//  assign it to every Object, it automatically registers itself
Object::Object(const char *name) : m_name(name) {
    Input::Manager::instance().register_object(this);
    printf("Created [%s]\n", m_name);
}


////
//  Automatically unregister objects
Object::~Object(){
    Input::Manager::instance().unregister_object(this);
    printf("Destroyed [%s]\n", m_name);
}


////
//   Every object has a callback for midi
void Object::midi_callback(Midi::Event &midi) {
  //  Nothing by default
}

