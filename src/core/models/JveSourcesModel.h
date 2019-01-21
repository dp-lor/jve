

#ifndef JVESOURCESMODEL_H
#define JVESOURCESMODEL_H


#include "JveBaseModel.h"


#include <QHash>
#include <QStringList>
#include <QString>


class JveProject;
class JveSourcesItemModel;


class JveSourcesModel : public JveBaseModel
{
    Q_OBJECT
    public:
        explicit  JveSourcesModel(JveProject *project, QDomElement domElement);
        virtual  ~JveSourcesModel(void);
    public:
        void setUp(void);
        void upSet(void);
    public:
        void addItems(const QStringList &resourcesList);
    private:
        void attachSourceItem(JveSourcesItemModel *item);
    private:
        QDomElement createSingleResourceItemDom(
            const QString &resourceTagName,
            const QString &resourcePath
        );
    private slots:
        void slotAddImagesSequenceItem(const QStringList &imagesList);
    private:
        // members
        JveProject                            *mp_project;
        QHash<QString, JveSourcesItemModel *>  mp_items;
};


#endif // JVESOURCESMODEL_H


