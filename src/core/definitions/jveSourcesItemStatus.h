

#ifndef JVESOURCESITEMSTATUS_H
#define JVESOURCESITEMSTATUS_H


class jveSourcesItemStatus
{
    public:
        enum Statuses {
            Ok                  = 0,
            EmptyResourcesList  = 1,
            ResourceNotExists   = 1 << 1,
            ResourceNotFile     = 1 << 2,
            ResourceNotReadable = 1 << 3,
            ResourceReplaced    = 1 << 4
        };
};


#endif // JVESOURCESITEMSTATUS_H


