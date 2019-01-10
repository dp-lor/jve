

#include "jveOptionsParserPrivate.h"


#include "../definitions/jveDefines.h"
#include "../definitions/jveOption.h"

#include "../application/jveReport.h"


jveOptionsParserPrivate jveOptionsParser;


jveOptionsParserPrivate::jveOptionsParserPrivate(void)
    : QObject(Q_NULLPTR),
        mp_options(0),
        mp_parser()
{
    mp_parser.setSingleDashWordOptionMode(
        QCommandLineParser::ParseAsCompactedShortOptions
    );
}

jveOptionsParserPrivate::~jveOptionsParserPrivate(void)
{
}

void
jveOptionsParserPrivate::parse(
    const QStringList &arguments,
    const int          forcedOptions
)
{
    // add forced options
    mp_options |= forcedOptions;

    // IMPORTANT!!!
    // for first parse add only boolean options,
    // because parser eat its as arguments for other options


    /*** ADD BOOLEAN OPTIONS **********************************************/

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


    /*** PARSE BOOLEAN OPTIONS ********************************************/

    // parse boolean options
    mp_parser.parse(arguments);

    // store boolean options
    if (mp_parser.isSet(optionHelp)) {
        mp_options |= jveOption::Help;
    }
    if (mp_parser.isSet(optionVersion)) {
        mp_options |= jveOption::Version;
    }
    if (mp_parser.isSet(optionProjectRender)) {
        mp_options |= jveOption::RenderProject;
    }


    /*** NON BOOLEAN OPTIONS **********************************************/

    // load project
    QCommandLineOption optionProjectLoad(
        QStringList()
            << "p"
            << "project",
        tr("cli_option_project_load_description"),
        tr("cli_option_project_load_param")
    );
    mp_parser.addOption(optionProjectLoad);


    /*** PARSE AGAIN BUT FOR ALL OPTIONS **********************************/

    // IMPORTANT!!!
    // this parse process throw reports

    // parse error
    if (!mp_parser.parse(arguments)) {
        throw jveReport(
            jveReport::Error,
            jveReport::CliParseOptionsError,
            (
                mp_options & jveOption::NonGui
                    ? mp_parser.errorText()
                    : QString("<p>%1</p>")
                          .arg(mp_parser.errorText().toHtmlEscaped())
            ),
            (
                mp_options & jveOption::NonGui
                    ? mp_parser.helpText()
                    : QString("<pre>%1</pre>")
                          .arg(mp_parser.helpText().toHtmlEscaped())
            )
        );
    }
    // show help
    if (mp_options & jveOption::Help) {
        throw jveReport(
            jveReport::Info,
            jveReport::CliShowHelp,
            (
                mp_options & jveOption::NonGui
                    ? mp_parser.helpText()
                    : QString("<pre>%1</pre>")
                          .arg(mp_parser.helpText().toHtmlEscaped())
            )
        );
    }
    // show version
    if (mp_options & jveOption::Version) {
        throw jveReport(
            jveReport::Info,
            jveReport::CliShowVersion,
            QString("%1 - %2")
                .arg(JVE_NAME_STRING)
                .arg(JVE_VERSION_STRING)
        );
    }

    // load project
    if (mp_parser.isSet(optionProjectLoad)) {
        mp_options |= jveOption::LoadProject;
        mp_projectFilePath = mp_parser.value(optionProjectLoad);
    }

    // fallback show help
    if (
        0 != mp_parser.positionalArguments().size()
            || (
                mp_options & jveOption::NonGui
                    && 1 == arguments.size()
            )
    ) {
        throw jveReport(
            jveReport::Info,
            jveReport::CliShowHelp,
            (
                mp_options & jveOption::NonGui
                    ? mp_parser.helpText()
                    : QString("<pre>%1</pre>")
                          .arg(mp_parser.helpText().toHtmlEscaped())
            )
        );
    }
}

int
jveOptionsParserPrivate::options(void) const
{
    return mp_options;
}

QString
jveOptionsParserPrivate::projectFilePath(void) const
{
    return mp_projectFilePath;
}


