

#ifndef JVEPROJECTSTATE_H
#define JVEPROJECTSTATE_H


class jveProjectState
{
    public:
        enum States {
            Closed         = 0,
            Opened         = 1,
            New            = 1 << 1,
            HiddenModified = 1 << 2,
            Modified       = 1 << 3
        };
};


#endif // JVEPROJECTSTATE_H


