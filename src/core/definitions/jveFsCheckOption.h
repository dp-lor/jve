

#ifndef JVEFSCHECKOPTION_H
#define JVEFSCHECKOPTION_H


class jveFsCheckOption
{
    public:
        enum Options {
            None              = 0,
            IsExists          = 1,
            IsReadable        = 1 << 1,
            IsWritable        = 1 << 2,
            IsParentExists    = 1 << 3,
            IsParentReadable  = 1 << 4,
            IsParentWritable  = 1 << 5
        };
};


#endif // JVEFSCHECKOPTION_H


