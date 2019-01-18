

#ifndef JVEAUDIOSOURCESTREAM_H
#define JVEAUDIOSOURCESTREAM_H


#include "JveSourceStream.h"


class JveAudioSourceStream : public JveSourceStream
{
    public:
        explicit  JveAudioSourceStream(void);
        virtual  ~JveAudioSourceStream(void);
    public:
        int frameRate(void) const;
        int channelsNumber(void) const;
        int framesLength(void) const;
};


#endif // JVEAUDIOSOURCESTREAM_H


