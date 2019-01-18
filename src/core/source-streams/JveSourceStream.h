

#ifndef JVESOURCESTREAM_H
#define JVESOURCESTREAM_H


#include "../definitions/JveSourceStreamType.h"


class JveSourceStream
{
    public:
        explicit JveSourceStream(
            const int type = JveSourceStreamType::Undefined
        );
        virtual ~JveSourceStream(void);
    public:
        int type(void) const;
    protected:
        // members
        int mp_type;
    /*public:
        int    videoFramesLength(void) const;
        double videoFps(void) const;*/
};


#endif // JVESOURCESTREAM_H


