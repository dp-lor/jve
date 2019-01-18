

#ifndef JVESOURCESITEMSTATUS_H
#define JVESOURCESITEMSTATUS_H


class JveSourcesItemStatus
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


