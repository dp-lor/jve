

#ifndef JVEPROJECTSOURCESITEMSTATUS_H
#define JVEPROJECTSOURCESITEMSTATUS_H


class jveProjectSourcesItemStatus
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


#endif // JVEPROJECTSOURCESITEMSTATUS_H


