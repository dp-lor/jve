

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
            ResourceNotImage,
            ResourceNotAudio,
            ResourceNotVideo,
            EmptyResourcesList,
            SeveralResourcesNotExists,
            SeveralResourcesNotFile,
            SeveralResourcesNotReadable,
            ErrorReadSeveralResources,
            SeveralResourcesReplaced,
            SeveralResourcesNotImage,
            Reserved
        };
};


#endif // JVESOURCESITEMSTATUS_H


