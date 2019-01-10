

#ifndef JVEAVOPTIONS_H
#define JVEAVOPTIONS_H


extern "C" {


    typedef struct jveVideoSizeEntry {
        const char *abbr;
        int width;
        int height;
        int available;
    } VideoSizeEntry;


    const jveVideoSizeEntry jveVideoSizes[] = {
        { "ntsc",       720,  480, 0 },
        { "pal",        720,  576, 0 },
        { "qntsc",      352,  240, 0 },
        { "qpal",       352,  288, 0 },
        { "sntsc",      640,  480, 1 },
        { "spal",       768,  576, 1 },
        { "film",       352,  240, 0 },
        { "ntsc-film",  352,  240, 0 },
        { "sqcif",      128,   96, 1 },
        { "qcif",       176,  144, 0 },
        { "cif",        352,  288, 0 },
        { "4cif",       704,  576, 0 },
        { "16cif",     1408, 1152, 0 },
        { "qqvga",      160,  120, 1 },
        { "qvga",       320,  240, 1 },
        { "vga",        640,  480, 1 },
        { "svga",       800,  600, 1 },
        { "xga",       1024,  768, 1 },
        { "uxga",      1600, 1200, 1 },
        { "qxga",      2048, 1536, 1 },
        { "sxga",      1280, 1024, 1 },
        { "qsxga",     2560, 2048, 1 },
        { "hsxga",     5120, 4096, 1 },
        { "wvga",       852,  480, 0 },
        { "wxga",      1366,  768, 0 },
        { "wsxga",     1600, 1024, 0 },
        { "wuxga",     1920, 1200, 1 },
        { "woxga",     2560, 1600, 1 },
        { "wqsxga",    3200, 2048, 0 },
        { "wquxga",    3840, 2400, 1 },
        { "whsxga",    6400, 4096, 0 },
        { "whuxga",    7680, 4800, 1 },
        { "cga",        320,  200, 1 },
        { "ega",        640,  350, 0 },
        { "hd480",      852,  480, 0 },
        { "hd720",     1280,  720, 1 },
        { "hd1080",    1920, 1080, 1 },
        { "2kdci",     2048, 1080, 0 },
        { "4kdci",     4096, 2160, 0 },
        { "uhd2160",   3840, 2160, 1 },
        { "uhd4320",   7680, 4320, 1 }
    };


} // extern "C"


#endif // JVEAVOPTIONS_H


