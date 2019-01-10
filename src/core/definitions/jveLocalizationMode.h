

#ifndef JVELOCALIZATIONMODE_H
#define JVELOCALIZATIONMODE_H


class jveLocalizationMode
{
    public:
        enum Modes {
            None = 0,
            Cli  = 1,
            Gui  = 1 << 1
        };
};


#endif // JVELOCALIZATIONMODE_H


