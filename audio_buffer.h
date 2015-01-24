#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include <stdio.h>
#include <string.h>

#define Sample double

class AudioBuffer {

    public:
    AudioBuffer(size_t buffer_size, Sample init_value = 0);
    ~AudioBuffer();
    Sample &operator[](int index);
    size_t size() const;
    void print();
    void fill(Sample value);
    Sample last(){ return m_buffer[m_size - 1]; }
    void zero();
    bool zeroed() const { return m_zeroed; }

    private:
    bool m_zeroed;
    size_t m_size;
    Sample *m_buffer;
};

#endif
