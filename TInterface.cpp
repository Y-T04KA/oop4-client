#include "TInterface.h"

TInterface::TInterface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setupDropdown();
    ui.sizeDropdown->addItem("2", two);
    ui.sizeDropdown->addItem("3", three);
    ui.sizeDropdown->addItem("4", four);
    ui.tableWidget->setColumnCount(2);
    ui.tableWidget->setRowCount(2);

}

TInterface::~TInterface()
{}

void TInterface::setupDropdown() {
    two.setValue(2);
    three.setValue(3);
    four.setValue(4);
    
}

void TInterface::resizeInput() {
    int size = ui.sizeDropdown->currentText().toInt();
    ui.tableWidget->setColumnCount(size-1);
    ui.tableWidget->setRowCount(size-1);
}

