#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class CalcWidget; }
QT_END_NAMESPACE

class CalcWidget : public QWidget
{
    Q_OBJECT

public:
    CalcWidget(QWidget *parent = nullptr);
    ~CalcWidget();

private:
    Ui::CalcWidget *ui;
    QString calctText;
    QStack<QString> m_stk;
    bool should_clear;

public slots:
    void digitButtonClicked();
    void actionButtonClicked();
    void calculate();
    void checkRerset();
    void reset();

};
#endif // CALCWIDGET_H
