

#include "JveSourceStream.h"


JveSourceStream::JveSourceStream(const int type)
    : mp_type(type)
{
}

JveSourceStream::~JveSourceStream(void)
{
}

int
JveSourceStream::type(void) const
{
    return mp_type;
}


