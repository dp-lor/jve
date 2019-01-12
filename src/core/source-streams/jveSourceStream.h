

#ifndef JVESOURCESTREAM_H
#define JVESOURCESTREAM_H


#include "../definitions/jveSourceStreamType.h"


class jveSourceStream
{
    public:
        explicit jveSourceStream(
            const int type = jveSourceStreamType::Undefined
        );
        virtual ~jveSourceStream(void);
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


