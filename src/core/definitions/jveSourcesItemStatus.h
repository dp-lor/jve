

#ifndef JVESOURCESITEMSTATUS_H
#define JVESOURCESITEMSTATUS_H


class jveSourcesItemStatus
{
    public:
        enum Statuses {
            Ok,
            NotExists,
            NotFile,
            NotReadable,
            Replaced,
            EmptySequence,
            OneOrMoreNotExists,
            OneOrMoreNotFile,
            OneOrMoreNotReadable,
            OneOrMoreReplaced
        };
};


#endif // JVESOURCESITEMSTATUS_H


