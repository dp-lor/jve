

#ifndef JVESOURCESMODEL_H
#define JVESOURCESMODEL_H


#include "JveBaseModel.h"


#include <QHash>
#include <QStringList>
#include <QString>


class JveSourcesItemModel;


class JveSourcesModel : public JveBaseModel
{
    Q_OBJECT
    public:
        explicit  JveSourcesModel(QDomElement domElement);
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
        // sources items
        QHash<QString, JveSourcesItemModel *>  mp_items;
};


#endif // JVESOURCESMODEL_H


