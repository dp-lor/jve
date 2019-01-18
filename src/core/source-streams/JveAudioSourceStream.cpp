

#include "JveAudioSourceStream.h"


JveAudioSourceStream::JveAudioSourceStream(void)
    : JveSourceStream(JveSourceStreamType::Audio)
{
}

JveAudioSourceStream::~JveAudioSourceStream(void)
{
}

int
JveAudioSourceStream::frameRate(void) const
{
    return 0;
}

int
JveAudioSourceStream::channelsNumber(void) const
{
    return 0;
}

int
JveAudioSourceStream::framesLength(void) const
{
    return 0;
}


