

#include "jveTrPrivate.h"


#include "../application/jveReport.h"
#include "jveTranslation.h"


jveTrPrivate jveTr;


jveTrPrivate::jveTrPrivate(void)
    : QObject(Q_NULLPTR),
        mp_texts(jveTranslation::ReservedTranslation),
        mp_titles(jveReport::ReservedType),
        mp_messages(jveReport::ReservedSubType)
{
}

jveTrPrivate::~jveTrPrivate(void)
{
}

QString
jveTrPrivate::textAt(const int key) const
{
    return mp_texts.at(key);
}

QString
jveTrPrivate::titleAt(const int type) const
{
    return mp_titles.at(type);
}

QString
jveTrPrivate::messageAt(const int subType) const
{
    return mp_messages.at(subType);
}

void
jveTrPrivate::update(void)
{
    // untitled project
    mp_texts.replace(
        jveTranslation::NewProjectName,
        tr("text_new_project_name")
    );

    // error
    mp_titles.replace(
        jveReport::Error,
        tr("report_title_error")
    );
    // warning
    mp_titles.replace(
        jveReport::Warning,
        tr("report_title_warning")
    );
    // info
    mp_titles.replace(
        jveReport::Info,
        tr("report_title_info")
    );

    // message
    /*
        don't replace jveReport::Message
        it always unused empty string
    */

    // success
    mp_titles.replace(
        jveReport::Success,
        tr("report_title_success")
    );

    // cli parse options error
    mp_messages.replace(
        jveReport::CliParseOptionsError,
        tr("report_message_cli_parse_options_error%1%2")
    );
    // cli option help
    mp_messages.replace(
        jveReport::CliShowHelp,
        tr("report_message_cli_option_help%1")
    );
    // cli option version
    mp_messages.replace(
        jveReport::CliShowVersion,
        tr("report_message_cli_option_version%1")
    );

    // invalid application resource
    mp_messages.replace(
        jveReport::ApplicationResourceInvalid,
        tr("report_message_application_resource_invalid%1%2")
    );

    // parent directory not exists
    mp_messages.replace(
        jveReport::ParentDirectoryNotExists,
        tr("report_message_parent_directory_not_exists%1")
    );
    // parent directory is not directory
    mp_messages.replace(
        jveReport::ParentDirectoryIsNotDirectory,
        tr("report_message_parent_directory_is_not_directory%1")
    );
    // parent directory not readable
    mp_messages.replace(
        jveReport::ParentDirectoryNotReadable,
        tr("report_message_parent_directory_not_readable%1")
    );
    // parent directory not writable
    mp_messages.replace(
        jveReport::ParentDirectoryNotWritable,
        tr("report_message_parent_directory_not_writable%1")
    );

    // directory not exists
    mp_messages.replace(
        jveReport::DirectoryNotExists,
        tr("report_message_directory_not_exists%1")
    );
    // directory is not directory
    mp_messages.replace(
        jveReport::DirectoryIsNotDirectory,
        tr("report_message_directory_is_not_directory%1")
    );
    // directory not readable
    mp_messages.replace(
        jveReport::DirectoryNotReadable,
        tr("report_message_directory_not_readable%1")
    );
    // directory not writable
    mp_messages.replace(
        jveReport::DirectoryNotWritable,
        tr("report_message_directory_not_writable%1")
    );

    // file not exists
    mp_messages.replace(
        jveReport::FileNotExists,
        tr("report_message_file_not_exists%1")
    );
    // file is not file
    mp_messages.replace(
        jveReport::FileIsNotFile,
        tr("report_message_file_is_not_file%1")
    );
    // file not readable
    mp_messages.replace(
        jveReport::FileNotReadable,
        tr("report_message_file_not_readable%1")
    );
    // file not writable
    mp_messages.replace(
        jveReport::FileNotWritable,
        tr("report_message_file_not_writable%1")
    );

    // unsupported file format
    mp_messages.replace(
        jveReport::FileFormatUnsupported,
        tr("report_message_file_format_unsupported%1")
    );

    // project closing
    mp_messages.replace(
        jveReport::ProjectClosing,
        tr("report_message_project_closing")
    );
    // new project loading
    mp_messages.replace(
        jveReport::ProjectNewLoading,
        tr("report_message_project_new_loading")
    );
    // project loading
    mp_messages.replace(
        jveReport::ProjectLoading,
        tr("report_message_project_loading")
    );
    // project saving
    mp_messages.replace(
        jveReport::ProjectSaving,
        tr("report_message_project_saving")
    );

    // invalid project file
    mp_messages.replace(
        jveReport::ProjectFileInvalid,
        tr("report_message_project_file_invalid%1%2")
    );
    // invalid project data
    mp_messages.replace(
        jveReport::ProjectDataInvalid,
        tr("report_message_project_data_invalid%1%2")
    );
    // invalid project xml document version
    mp_messages.replace(
        jveReport::ProjectXmlVersionInvalid,
        tr("report_message_project_xml_version_invalid%1")
    );
    // invalid project xml encoding
    mp_messages.replace(
        jveReport::ProjectXmlEncodingInvalid,
        tr("report_message_project_xml_encoding_invalid%1")
    );
    // unsupported project version
    mp_messages.replace(
        jveReport::ProjectVersionUnsupported,
        tr("report_message_project_version_unsupported%1")
    );
    // invalid project settings range values
    mp_messages.replace(
        jveReport::ProjectSettingsRangeInvalid,
        tr("report_message_project_settings_range_invalid%1")
    );
    // invalid fps
    mp_messages.replace(
        jveReport::ProjectStateFpsInvalid,
        tr("report_message_project_state_fps_invalid%1")
    );
    // invalid playhead position
    mp_messages.replace(
        jveReport::ProjectStatePlayheadPositionInvalid,
        tr("report_message_project_state_playhead_position_invalid%1")
    );

    // project closed
    mp_messages.replace(
        jveReport::ProjectClosed,
        tr("report_message_project_closed")
    );
    // new project loaded
    mp_messages.replace(
        jveReport::ProjectNewLoaded,
        tr("report_message_project_new_loaded")
    );
    // project loaded
    mp_messages.replace(
        jveReport::ProjectLoaded,
        tr("report_message_project_loaded")
    );
    // project saved
    mp_messages.replace(
        jveReport::ProjectSaved,
        tr("report_message_project_saved")
    );
}


