

#ifndef JVEREPORT_H
#define JVEREPORT_H


#include <QString>


class jveReport
{
    public:

        enum Types {
            DummyType = 0,

            Error,
            Warning,
            Info,
            Message,
            Success,

            ReservedType
        };

        enum SubTypes {
            DummySubType = 0,

            // cli parse options error
            CliParseOptionsError,
            // cli option help
            CliShowHelp,
            // cli option version
            CliShowVersion,

            // application resource error
            ApplicationResourceInvalid,

            // filesystem errors
            ParentDirectoryNotExists,
            ParentDirectoryIsNotDirectory,
            ParentDirectoryNotReadable,
            ParentDirectoryNotWritable,
            DirectoryNotExists,
            DirectoryIsNotDirectory,
            DirectoryNotReadable,
            DirectoryNotWritable,
            FileNotExists,
            FileIsNotFile,
            FileNotReadable,
            FileNotWritable,

            // file format errors
            FileFormatUnsupported,

            // project processes
            ProjectClosing,
            ProjectNewLoading,
            ProjectLoading,
            ProjectSaving,

            // project errors
            ProjectFileInvalid,
            ProjectDataInvalid,
            ProjectXmlVersionInvalid,
            ProjectXmlEncodingInvalid,
            ProjectVersionUnsupported,
            ProjectSettingsRangeInvalid,
            ProjectStateFpsInvalid,
            ProjectStatePlayheadPositionInvalid,

            // project successes
            ProjectClosed,
            ProjectNewLoaded,
            ProjectLoaded,
            ProjectSaved,

            ReservedSubType
        };

    public:
        explicit jveReport(void);
        explicit jveReport(const int type, const int subType);
        explicit jveReport(
            const int      type,
            const int      subType,
            const QString &arg1
        );
        explicit jveReport(
            const int      type,
            const int      subType,
            const QString &arg1,
            const QString &arg2
        );
        virtual ~jveReport(void);
    public:
        void fill(const int type, const int subType);
        void fill(const int type, const int subType, const QString &arg1);
        void fill(
            const int      type,
            const int      subType,
            const QString &arg1,
            const QString &arg2
        );
        void    setForced(const bool forced = true);
        int     type(void) const;
        int     subType(void) const;
        bool    isForced(void) const;
        QString title(void) const;
        QString message(void) const;
    protected:
        // members
        int     mp_type;
        int     mp_subType;
        bool    mp_forced;
        QString mp_title;
        QString mp_message;
};


#endif // JVEREPORT_H


