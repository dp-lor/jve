

#include "jveSourceStream.h"


jveSourceStream::jveSourceStream(const int type)
    : mp_type(type)
{
}

jveSourceStream::~jveSourceStream(void)
{
}

int
jveSourceStream::type(void) const
{
    return mp_type;
}


