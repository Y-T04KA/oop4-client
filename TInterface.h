#pragma once

#include <QtWidgets/QMainWindow>
#include <qlabel.h>
#include "ui_TInterface.h"
#include <common.h>

class TInterface : public QMainWindow
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();
    void setupDropdown();
    QLabel* output;
    

private:
    Ui::TInterfaceClass ui;
    QVariant two,three,four;
    //std::vector<int[2]> Data;
public slots:
    void answer(QString);

private slots:
    void resizeInput();
    //int getInput();
    void detRequest();
    void rankRequest();
    void transRequest();
signals:
    void request(QString);
};


