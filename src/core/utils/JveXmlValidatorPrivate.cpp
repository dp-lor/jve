

#include "JveXmlValidatorPrivate.h"


#include <QXmlSchema>
#include <QXmlSchemaValidator>


#include "../definitions/JveXmlDefines.h"
#include "../definitions/JveProjectVersion.h"


#include "JveMessageHandler.h"
#include "../application/JveReport.h"


JveXmlValidatorPrivate JveXmlValidator;


JveXmlValidatorPrivate::JveXmlValidatorPrivate(void)
{
    // project validation schemas
    mp_xsdProjectSchemas
        << JVE_XSD_SCHEMA_PROJECT_V1_0; // JveProjectVersion::v1_0
}

JveXmlValidatorPrivate::~JveXmlValidatorPrivate(void)
{
}

void
JveXmlValidatorPrivate::init(void)
{
    // project resources
    validateXsdResources(&mp_xsdProjectSchemas);
}

int
JveXmlValidatorPrivate::validateProjectFile(QFile *projectFile) const
{
    QFile               schemaFile;
    QXmlSchema          schema;
    JveMessageHandler   messageHandler;
    QXmlSchemaValidator validator;

    validator.setMessageHandler(&messageHandler);
    for (int i = 0, t = 1; i < JveProjectVersion::Reserved; i++, t++) {
        schemaFile.close();
        schemaFile.setFileName(mp_xsdProjectSchemas.at(i));
        schemaFile.open(QFile::ReadOnly);
        schema.load(schemaFile.readAll());
        validator.setSchema(schema);
        projectFile->seek(0);
        if (validator.validate(projectFile)) {
            return i; // version number
        }
    }

    return JveProjectVersion::Unsupported;
}

void
JveXmlValidatorPrivate::validateXsdResources(const QStringList *resources)
{
    QFile             schemaFile;
    QXmlSchema        schema;
    JveMessageHandler messageHandler;

    schema.setMessageHandler(&messageHandler);
    for (int i = 0; i < resources->size(); i++) {
        schemaFile.close();
        schemaFile.setFileName(resources->at(i));
        schemaFile.open(QFile::ReadOnly);
        schema.load(schemaFile.readAll());
        if (!schema.isValid()) {
            throw JveReport(
                JveReport::Error,
                JveReport::ApplicationResourceInvalid,
                resources->at(i),
                QString("(%1, %2) %3")
                    .arg(messageHandler.line())
                    .arg(messageHandler.column())
                    .arg(messageHandler.statusMessageText())
            );
        }
    }
}


