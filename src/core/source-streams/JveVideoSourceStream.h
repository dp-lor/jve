

#ifndef JVEVIDEOSOURCESTREAM_H
#define JVEVIDEOSOURCESTREAM_H


#include "JveSourceStream.h"


class JveVideoSourceStream : public JveSourceStream
{
    public:
        explicit  JveVideoSourceStream(void);
        virtual  ~JveVideoSourceStream(void);
    public:
        double fps(void) const;
        int    framesLength(void) const;
};


#endif // JVEVIDEOSOURCESTREAM_H


