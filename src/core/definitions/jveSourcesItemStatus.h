

#ifndef JVESOURCESITEMSTATUS_H
#define JVESOURCESITEMSTATUS_H


class jveSourcesItemStatus
{
    public:
        enum Statuses {
            Ok,
            ResourceNotExists,
            ResourceNotFile,
            ResourceNotReadable,
            ErrorReadResource,
            ResourceReplaced,
            EmptyResourcesList,
            SeveralResourcesNotExists,
            SeveralResourcesNotFile,
            SeveralResourcesNotReadable,
            ErrorReadSeveralResources,
            SeveralResourcesReplaced,
            Reserved
        };
};


#endif // JVESOURCESITEMSTATUS_H


