

#ifndef JVEAUDIOSOURCESTREAM_H
#define JVEAUDIOSOURCESTREAM_H


#include "jveSourceStream.h"


class jveAudioSourceStream : public jveSourceStream
{
    public:
        explicit  jveAudioSourceStream(void);
        virtual  ~jveAudioSourceStream(void);
    public:
        int frameRate(void) const;
        int channelsNumber(void) const;
        int framesLength(void) const;
};


#endif // JVEAUDIOSOURCESTREAM_H


