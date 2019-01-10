

#ifndef JVEOPTION_H
#define JVEOPTION_H


class jveOption
{
    public:
        enum Options {
            None                  = 0,
            NonGui                = 1,
            Quit                  = 1 << 1,
            Help                  = 1 << 2,
            Version               = 1 << 3,
            CloseProject          = 1 << 4,
            CloseProjectForced    = 1 << 5,
            ShowSaveProjectDialog = 1 << 6,
            SaveProject           = 1 << 7,
            LoadNewProject        = 1 << 8,
            LoadProject           = 1 << 9,
            RenderProject         = 1 << 10
        };
};


#endif // JVEOPTION_H


