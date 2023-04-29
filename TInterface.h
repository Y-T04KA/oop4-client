#pragma once

#include <QtWidgets/QMainWindow>
#include <qlabel.h>
#include <qpushbutton.h>
#include "ui_TInterface.h"
#include <common.h>

class TClientInterface : public QMainWindow
{
    Q_OBJECT

public:
    TClientInterface(QWidget *parent = nullptr);
    ~TClientInterface();
    void setupDropdown();
    QLabel* output;
    QPushButton* detButton,*rankButton,*transButton;
    

private:
    Ui::TInterfaceClass ui;
    QVariant two,three,four;
    int typeDetector(QString);
    bool cellsFilled(int, int);
    QString cellDataHandler(QString, int);
public slots:
    void answer(QString);

private slots:
    void resizeInput();
    void detRequest();
    void rankRequest();
    void transRequest();
signals:
    void request(QString);
};


