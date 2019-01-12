

#include "jveVideoSourceStream.h"


jveVideoSourceStream::jveVideoSourceStream(void)
    : jveSourceStream(jveSourceStreamType::Video)
{
}

jveVideoSourceStream::~jveVideoSourceStream(void)
{
}

double
jveVideoSourceStream::fps(void) const
{
    return 0.0;
}

int
jveVideoSourceStream::framesLength(void) const
{
    return 0;
}


