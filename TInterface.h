#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TInterface.h"

class TInterface : public QMainWindow
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();
    void setupDropdown();

    

private:
    Ui::TInterfaceClass ui;
    QVariant two,three,four;

private slots:
    void resizeInput();
    void getInput();
};


