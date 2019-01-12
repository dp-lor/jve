

#include "jveAudioSourceStream.h"


jveAudioSourceStream::jveAudioSourceStream(void)
    : jveSourceStream(jveSourceStreamType::Audio)
{
}

jveAudioSourceStream::~jveAudioSourceStream(void)
{
}

int
jveAudioSourceStream::frameRate(void) const
{
    return 0;
}

int
jveAudioSourceStream::channelsNumber(void) const
{
    return 0;
}

int
jveAudioSourceStream::framesLength(void) const
{
    return 0;
}


