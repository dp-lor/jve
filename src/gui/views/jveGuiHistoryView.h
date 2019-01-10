

#ifndef JVEGUIHISTORYVIEW_H
#define JVEGUIHISTORYVIEW_H


#include <QListView>


#include "jveGuiHistoryViewModel.h"


class QEvent;


class jveGuiHistoryView : public QListView
{
    Q_OBJECT
    public:
        explicit  jveGuiHistoryView(QWidget *parent);
        virtual  ~jveGuiHistoryView(void);
    protected:
        void changeEvent(QEvent *event);
    private slots:
        void slotSetState(const int state);
        void slotSetGuiState(const int state);
    private:
        // members
        int                    mp_state;
        int                    mp_guiState;
        jveGuiHistoryViewModel mp_viewModel;
};


#endif // JVEGUIHISTORYVIEW_H


