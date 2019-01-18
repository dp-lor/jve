

#ifndef JVEGUIHISTORYVIEW_H
#define JVEGUIHISTORYVIEW_H


#include <QListView>


#include "JveGuiHistoryViewModel.h"


class QEvent;


class JveGuiHistoryView : public QListView
{
    Q_OBJECT
    public:
        explicit  JveGuiHistoryView(QWidget *parent);
        virtual  ~JveGuiHistoryView(void);
    protected:
        void changeEvent(QEvent *event);
    private slots:
        void slotSetState(const int state);
        void slotSetGuiState(const int state);
    private:
        // members
        int                    mp_state;
        int                    mp_guiState;
        JveGuiHistoryViewModel mp_viewModel;
};


#endif // JVEGUIHISTORYVIEW_H


