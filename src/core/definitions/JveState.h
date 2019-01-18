

#ifndef JVESTATE_H
#define JVESTATE_H


class JveState
{
    public:
        enum States {
            None                  = 0,
            Busy                  = 1,
            ProjectOpened         = 1 << 1,
            ProjectNew            = 1 << 2,
            ProjectHiddenModified = 1 << 3,
            ProjectModified       = 1 << 4
        };
};


#endif // JVESTATE_H


