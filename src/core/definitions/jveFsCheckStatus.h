

#ifndef JVEFSCHECKSTATUS_H
#define JVEFSCHECKSTATUS_H


class jveFsCheckStatus
{
    public:
        enum Statuses {
            Ok,
            NotExists,
            NotFile,
            NotDirectory,
            NotReadable,
            NotWritable,
            ParentNotExists,
            ParentNotDirectory,
            ParentNotReadable,
            ParentNotWritable
        };
};


#endif // JVEFSCHECKSTATUS_H


