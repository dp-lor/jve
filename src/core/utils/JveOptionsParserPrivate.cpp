

#include "JveOptionsParserPrivate.h"


#include "../definitions/JveDefines.h"
#include "../definitions/JveOption.h"

#include "../application/JveReport.h"


JveOptionsParserPrivate JveOptionsParser;


JveOptionsParserPrivate::JveOptionsParserPrivate(void)
    : QObject(nullptr),
        mp_options(0),
        mp_parser()
{
    mp_parser.setSingleDashWordOptionMode(
        QCommandLineParser::ParseAsCompactedShortOptions
    );
}

JveOptionsParserPrivate::~JveOptionsParserPrivate(void)
{
}

void
JveOptionsParserPrivate::parse(
    const QStringList &arguments,
    const int          forcedOptions
)
{
    // add forced options
    mp_options |= forcedOptions;

    // IMPORTANT!!!
    // for first parse add only boolean options,
    // because parser eat its as arguments for other options


    /*** ADD BOOLEAN OPTIONS **********************************/

    // help
    QCommandLineOption optionHelp = mp_parser.addHelpOption();

    // version
    QCommandLineOption optionVersion(
        QStringList()
            << "v"
            << "version",
        tr("cli_option_version_description")
    );
    mp_parser.addOption(optionVersion);

    // render project
    QCommandLineOption optionProjectRender(
        QStringList()
            << "r"
            << "render",
        tr("cli_option_project_render_description")
    );
    mp_parser.addOption(optionProjectRender);


    /*** PARSE BOOLEAN OPTIONS ********************************/

    // parse boolean options
    mp_parser.parse(arguments);

    // store boolean options
    if (mp_parser.isSet(optionHelp)) {
        mp_options |= JveOption::Help;
    }
    if (mp_parser.isSet(optionVersion)) {
        mp_options |= JveOption::Version;
    }
    if (mp_parser.isSet(optionProjectRender)) {
        mp_options |= JveOption::RenderProject;
    }


    /*** NON BOOLEAN OPTIONS **********************************/

    // load project
    QCommandLineOption optionProjectLoad(
        QStringList()
            << "p"
            << "project",
        tr("cli_option_project_load_description"),
        tr("cli_option_project_load_param")
    );
    mp_parser.addOption(optionProjectLoad);


    /*** PARSE AGAIN BUT FOR ALL OPTIONS **********************/

    // IMPORTANT!!!
    // this parse process throw reports

    // parse error
    if (!mp_parser.parse(arguments)) {
        throw JveReport(
            JveReport::Error,
            JveReport::CliParseOptionsError,
            (
                mp_options & JveOption::NonGui
                    ? mp_parser.errorText()
                    : QString("<p>%1</p>")
                          .arg(mp_parser.errorText().toHtmlEscaped())
            ),
            (
                mp_options & JveOption::NonGui
                    ? mp_parser.helpText()
                    : QString("<pre>%1</pre>")
                          .arg(mp_parser.helpText().toHtmlEscaped())
            )
        );
    }
    // show help
    if (mp_options & JveOption::Help) {
        throw JveReport(
            JveReport::Info,
            JveReport::CliShowHelp,
            (
                mp_options & JveOption::NonGui
                    ? mp_parser.helpText()
                    : QString("<pre>%1</pre>")
                          .arg(mp_parser.helpText().toHtmlEscaped())
            )
        );
    }
    // show version
    if (mp_options & JveOption::Version) {
        throw JveReport(
            JveReport::Info,
            JveReport::CliShowVersion,
            QString("%1 - %2")
                .arg(JVE_NAME_STRING)
                .arg(JVE_VERSION_STRING)
        );
    }

    // load project
    if (mp_parser.isSet(optionProjectLoad)) {
        mp_options |= JveOption::LoadProject;
        // TODO fix relative file path (make absolute)
        mp_projectFilePath = mp_parser.value(optionProjectLoad);
    }

    // fallback show help
    if (
        0 != mp_parser.positionalArguments().size()
            || (
                mp_options & JveOption::NonGui
                    && 1 == arguments.size()
            )
    ) {
        throw JveReport(
            JveReport::Info,
            JveReport::CliShowHelp,
            (
                mp_options & JveOption::NonGui
                    ? mp_parser.helpText()
                    : QString("<pre>%1</pre>")
                          .arg(mp_parser.helpText().toHtmlEscaped())
            )
        );
    }
}

int
JveOptionsParserPrivate::options(void) const
{
    return mp_options;
}

QString
JveOptionsParserPrivate::projectFilePath(void) const
{
    return mp_projectFilePath;
}


