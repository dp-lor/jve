

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
    private:
        void attachSourceItem(JveSourcesItemModel *item);
    private slots:
        void slotAddItems(const QStringList &itemsList);
        void slotAddImagesSequenceItem(const QStringList &imagesList);
    private:
        // members
        JveProject                            *mp_project;
        QHash<QString, JveSourcesItemModel *>  mp_items;
};


#endif // JVESOURCESMODEL_H


