#include <QSignalMapper>
#include <QDebug>

#include "calcwidget.h"
#include "keysenum.h"
#include "ui_calcwidget.h"

CalcWidget::CalcWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CalcWidget)
{

    ui->setupUi(this);
    calctText = "";
    should_clear = false;

    connect(ui->pushButton_0, SIGNAL(clicked()), SLOT(digitButtonClicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), SLOT(digitButtonClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(digitButtonClicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(digitButtonClicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(digitButtonClicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), SLOT(digitButtonClicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), SLOT(digitButtonClicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), SLOT(digitButtonClicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), SLOT(digitButtonClicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), SLOT(digitButtonClicked()));
    connect(ui->pushButton_comma, SIGNAL(clicked()), SLOT(digitButtonClicked()));

    connect(ui->pushButton_clear, SIGNAL(clicked()), SLOT(actionButtonClicked()));
    connect(ui->pushButton_eq, SIGNAL(clicked()), SLOT(actionButtonClicked()));
    connect(ui->pushButton_del, SIGNAL(clicked()), SLOT(actionButtonClicked()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), SLOT(actionButtonClicked()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), SLOT(actionButtonClicked()));
    connect(ui->pushButton_div, SIGNAL(clicked()), SLOT(actionButtonClicked()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), SLOT(actionButtonClicked()));
    connect(ui->pushButton_sign, SIGNAL(clicked()), SLOT(actionButtonClicked()));


}

void CalcWidget::digitButtonClicked(){
    QString str = ((QPushButton*)sender())->text();
    checkRerset();

    if (str.contains(QRegExp("[0-9]"))) {
        calctText += str;
        ui->lineEdit->setText(QString::number(calctText.toDouble(), 'G', 15));
    } else if (str == "." && !ui->lineEdit->text().contains('.')) {
        calctText += str;
        ui->lineEdit->setText(QString::number(calctText.toDouble(), 'f', 1));
    }
}

void CalcWidget::actionButtonClicked(){
    QString str = ((QPushButton*)sender())->text();
    if (str == "CE") {
        reset();
        return;
    }
    if (str == "DEL") {
        checkRerset();
        if (calctText.size() <= 1) {
            calctText = "0";
            ui->lineEdit->setText("0");
        } else {
            calctText.chop(1);
            if (calctText.at(calctText.size() - 1) == '.') {
                calctText.chop(1);
            }
            ui->lineEdit->setText(QString::number(calctText.toDouble(), 'G', 15));
        }
    } else if (str == "+/-") {
        if (calctText.contains('.')) {
            double changedDouble = calctText.toDouble() * -1;
            calctText = QString::number(changedDouble);
        } else {
            int changedInt = calctText.toInt() * -1;
            calctText = QString::number(changedInt);
        }
        ui->lineEdit->setText(calctText);
    } else {
        if (m_stk.count() >= 2) {
            m_stk.push(calctText);
            calculate();
            m_stk.clear();
            m_stk.push(calctText);
            if (str != "=") {
                m_stk.push(str);
            } else {
                should_clear = true;
            }
        } else {
            m_stk.push(calctText);
            m_stk.push(str);
            calctText = "0";
            ui->lineEdit->setText("0");
        }
    }
}

void CalcWidget::calculate(){

    qreal calcOperand2 = m_stk.pop().toDouble();
    QString strOperation = m_stk.pop();
    qreal calcOperand1 = m_stk.pop().toDouble();
    qreal calcResult = 0;

    if (strOperation == "+") {
        calcResult = calcOperand1 + calcOperand2;
    }
    if (strOperation == "−") {
        calcResult = calcOperand1 - calcOperand2;
    }
    if (strOperation == "÷") {
        calcResult = calcOperand1 / calcOperand2;
    }
    if (strOperation == "×") {
        calcResult = calcOperand1 * calcOperand2;
    }
    calctText = QString::number(calcResult);
    ui->lineEdit->setText(calctText);
}

void CalcWidget::checkRerset() {
    if (should_clear) {
        should_clear = false;
        calctText = "";
        ui->lineEdit->clear();
    }
}

void CalcWidget::reset() {
    m_stk.clear();
    calctText = "0";
    ui->lineEdit->setText("0");
}


CalcWidget::~CalcWidget()
{
    delete ui;
}

