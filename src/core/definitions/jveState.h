

#ifndef JVESTATE_H
#define JVESTATE_H


class jveState
{
    public:
        enum States {
            None                  = 0,
            Busy                  = 1,
            ProjectOpened         = 1 << 1,
            ProjectNew            = 1 << 2,
            ProjectModified       = 1 << 3,
            ProjectHiddenModified = 1 << 4
        };
};


#endif // JVESTATE_H


