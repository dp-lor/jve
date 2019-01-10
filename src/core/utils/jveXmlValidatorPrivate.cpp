

#include "jveXmlValidatorPrivate.h"


#include <QXmlSchema>
#include <QXmlSchemaValidator>


#include "../definitions/jveXmlDefines.h"
#include "../definitions/jveProjectVersion.h"


#include "jveMessageHandler.h"
#include "../application/jveReport.h"


jveXmlValidatorPrivate jveXmlValidator;


jveXmlValidatorPrivate::jveXmlValidatorPrivate(void)
{
    // project validation schemas
    mp_xsdProjectSchemas
        << JVE_XSD_SCHEMA_PROJECT_V1_0; // jveProjectVersion::v1_0
}

jveXmlValidatorPrivate::~jveXmlValidatorPrivate(void)
{
}

void
jveXmlValidatorPrivate::init(void)
{
    // project resources
    validateXsdResources(&mp_xsdProjectSchemas);
}

int
jveXmlValidatorPrivate::validateProjectFile(QFile *projectFile) const
{
    QFile               schemaFile;
    QXmlSchema          schema;
    jveMessageHandler   messageHandler;
    QXmlSchemaValidator validator;

    validator.setMessageHandler(&messageHandler);
    for (int i = 0, t = 1; i < jveProjectVersion::Reserved; i += 1, t += 1) {
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

    return jveProjectVersion::Unsupported;
}

void
jveXmlValidatorPrivate::validateXsdResources(const QStringList *resources)
{
    QFile             schemaFile;
    QXmlSchema        schema;
    jveMessageHandler messageHandler;

    schema.setMessageHandler(&messageHandler);
    for (int i = 0; i < resources->size(); i += 1) {
        schemaFile.close();
        schemaFile.setFileName(resources->at(i));
        schemaFile.open(QFile::ReadOnly);
        schema.load(schemaFile.readAll());
        if (!schema.isValid()) {
            throw jveReport(
                jveReport::Error,
                jveReport::ApplicationResourceInvalid,
                resources->at(i),
                QString("(%1, %2) %3")
                    .arg(messageHandler.line())
                    .arg(messageHandler.column())
                    .arg(messageHandler.statusMessageText())
            );
        }
    }
}


