

#include "JveVideoSourceStream.h"


JveVideoSourceStream::JveVideoSourceStream(void)
    : JveSourceStream(JveSourceStreamType::Video)
{
}

JveVideoSourceStream::~JveVideoSourceStream(void)
{
}

double
JveVideoSourceStream::fps(void) const
{
    return 0.0;
}

int
JveVideoSourceStream::framesLength(void) const
{
    return 0;
}


