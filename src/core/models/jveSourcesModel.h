

#ifndef JVESOURCESMODEL_H
#define JVESOURCESMODEL_H


#include "jveBaseModel.h"


#include <QHash>
#include <QString>
#include <QStringList>


class jveProject;
class jveSourcesItemModel;


class jveSourcesModel : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit  jveSourcesModel(jveProject *project, QDomElement domElement);
        virtual  ~jveSourcesModel(void);
    public:
        void setUp(void);
        void upSet(void);
    private:
        void attachSourceItem(jveSourcesItemModel *item);
    private slots:
        void slotAddItems(const QStringList &itemsList);
        void slotAddImagesSequenceItem(const QStringList &imagesList);
    private:
        // members
        jveProject                            *mp_project;
        QHash<QString, jveSourcesItemModel *>  mp_items;
};


#endif // JVESOURCESMODEL_H


