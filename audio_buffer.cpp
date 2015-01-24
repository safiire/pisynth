#include "audio_buffer.h"


////
//  Create an audio buffer with the correct size
AudioBuffer::AudioBuffer(size_t buffer_size, Sample init_value){
    m_buffer = new Sample[buffer_size];
    m_size = buffer_size;
    fill(init_value);
}


////
//  Fill the audio buffer with a value
void AudioBuffer::fill(Sample value){
    for(size_t i = 0; i < m_size; i++){
        m_buffer[i] = value;
    }
    if(value == 0){
        m_zeroed = true;
    }
}


////
//  Zero out the buffer and set the zero flag
void AudioBuffer::zero(){
    fill(0);
}


////
//  Release an audio buffer
AudioBuffer::~AudioBuffer(void){
    m_size = 0;
    delete[] m_buffer;
}


////
//  Access to the audio buffer
Sample &AudioBuffer::operator[](int index) {
    m_zeroed = false;
    return m_buffer[index];
}


////
//  Get the buffer
size_t AudioBuffer::size(void) const{
    return m_size;
}


////
//  Get the buffer
void AudioBuffer::print(void){
    printf("[");
    for(size_t i = 0; i < m_size; i++){
      printf("%f%s", m_buffer[i], i == m_size-1 ? "" : ", ");
    }
    printf("]\n");
}


