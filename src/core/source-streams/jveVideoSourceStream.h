

#ifndef JVEVIDEOSOURCESTREAM_H
#define JVEVIDEOSOURCESTREAM_H


#include "jveSourceStream.h"


class jveVideoSourceStream : public jveSourceStream
{
    public:
        explicit  jveVideoSourceStream(void);
        virtual  ~jveVideoSourceStream(void);
    public:
        double fps(void) const;
        int    framesLength(void) const;
};


#endif // JVEVIDEOSOURCESTREAM_H


