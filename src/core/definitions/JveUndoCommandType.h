

#ifndef JVEUNDOCOMMANDTYPE_H
#define JVEUNDOCOMMANDTYPE_H


class JveUndoCommandType
{
    public:
        enum Types {
            ProjectLoaded,
            NewProjectLoaded,
            SetRangeStart,
            SetRangeEnd
        };
};


#endif // JVEUNDOCOMMANDTYPE_H


