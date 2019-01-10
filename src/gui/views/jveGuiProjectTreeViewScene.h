

#ifndef JVEGUIPROJECTTREEVIEWSCENE_H
#define JVEGUIPROJECTTREEVIEWSCENE_H


#include <QGraphicsScene>


class jveGuiProjectTreeViewScene : public QGraphicsScene
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectTreeViewScene(QObject *parent);
        virtual  ~jveGuiProjectTreeViewScene(void);
    private:
        inline void restoreSettings(void);
        inline void saveSettings(void);
    private slots:
        void slotToggleRuler(const bool status);
        void slotSetRulerType(const int type);
    private:
        // members
        bool mp_rulerEnabled;
        int  mp_rulerType;
};


#endif // JVEGUIPROJECTTREEVIEWSCENE_H


