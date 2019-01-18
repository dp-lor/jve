

#ifndef JVEGUIFORM_H
#define JVEGUIFORM_H


#include <QWidget>
#include <QShowEvent>
#include <QLabel>
#include <QGridLayout>


class JveGuiForm : public QWidget
{
    Q_OBJECT
    private:
        enum UpdateTypes {
            UpdateAfterSetLabelsAlignment,
            UpdateAfterSetFieldsAlignment,
            UpdateAfterAddRow
        };
    public:
        explicit  JveGuiForm(QWidget *parent);
        virtual  ~JveGuiForm(void);
    protected:
        void showEvent(QShowEvent *event);
    public:
        void addSpace(void);
        void addSectionLabel(QLabel *sectionLabel);
        void addRow(QWidget *label, QWidget *field);
        void setLayoutAlignment(Qt::Alignment alignment);
        void setLabelsAlignment(Qt::Alignment alignment);
        void setFieldsAlignment(Qt::Alignment alignment);
    private:
        void updateRows(const int updateType);
    private:
        // members
        Qt::Alignment mp_labelsAlignment;
        Qt::Alignment mp_fieldsAlignment;
        QGridLayout   mp_layout;
};


#endif // JVEGUIFORM_H


