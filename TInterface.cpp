#include "TInterface.h"

TInterface::TInterface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setupDropdown();
    output = new QLabel(this);
    output->setGeometry(10, 190, 280, 25);
    ui.tableWidget->setColumnCount(2);
    ui.tableWidget->setRowCount(2);

}

TInterface::~TInterface()
{}

void TInterface::setupDropdown() {
    ui.sizeDropdown->addItem("2", two);
    ui.sizeDropdown->addItem("3", three);
    ui.sizeDropdown->addItem("4", four);
    two.setValue(2);
    three.setValue(3);
    four.setValue(4);
    
}

void TInterface::resizeInput() {
    int size = ui.sizeDropdown->currentText().toInt();//debugger says it returns 3, but to have 2x2 matrix i need to decrease 2 to 1???
    ui.tableWidget->setColumnCount(size-1);
    ui.tableWidget->setRowCount(size-1);//size when 2 is actually 3???
}

//int TInterface::getInput() {
    //int cc = ui.tableWidget->columnCount(), rc = ui.tableWidget->rowCount(),tabPtr=0;
    //int size = cc * rc;//why not just ask sizeDropdown? i can't predict results when click multiple times on same option
    //QString tmp;
    //QStringList res;
    //int buf[2]{};
    //Data.clear();
    //for (int i = 0; i < cc; i++) {
    //    for (int j = 0; j < rc; j++) {
    //        tmp = ui.tableWidget->item(i, j)->text();
    //        res = tmp.split('/');
    //        buf[0] = res.first().toInt();
    //        buf[1] = res.last().toInt();
    //        Data.push_back(buf);
    //    }
    //}
    //return cc;
//}

void TInterface::detRequest() {
    QString msg;//SIZE MODE DATA
    int cc = ui.tableWidget->columnCount(), rc = ui.tableWidget->rowCount();
    int size = cc * rc;//why not just ask sizeDropdown? i can't predict results when click multiple times on same option
    QString tmp;
    QStringList res;
    msg << QString().setNum(cc);//SIZE
    msg << QString().setNum(1);//MODE
    for (int i = 0; i < cc; i++) {
        for (int j = 0; j < rc; j++) {
            tmp = ui.tableWidget->item(i, j)->text();
            res = tmp.split('/');
            msg << res.first();
            msg << res.last();
            
        }
    }
    
    //int size = getInput();
   // msg << QString().setNum(size);//SIZE
   // msg << QString().setNum(1);//MODE
    //for (auto &var : Data)
   // {
   //     msg << QString().setNum(var[0]);//DATA
   //     msg << QString().setNum(var[1]);
   // }
    emit request(msg);
}

void TInterface::rankRequest() {
    QString msg;//SIZE MODE DATA
    int cc = ui.tableWidget->columnCount(), rc = ui.tableWidget->rowCount();
    int size = cc * rc;//why not just ask sizeDropdown? i can't predict results when click multiple times on same option
    QString tmp;
    QStringList res;
    msg << QString().setNum(cc);//SIZE
    msg << QString().setNum(2);//MODE
    for (int i = 0; i < cc; i++) {
        for (int j = 0; j < rc; j++) {
            tmp = ui.tableWidget->item(i, j)->text();
            res = tmp.split('/');
            msg << res.first();
            msg << res.last();

        }
    }
    emit request(msg);
}

void TInterface::transRequest() {
    QString msg;//SIZE MODE DATA
    int cc = ui.tableWidget->columnCount(), rc = ui.tableWidget->rowCount();
    int size = cc * rc;//why not just ask sizeDropdown? i can't predict results when click multiple times on same option
    QString tmp;
    QStringList res;
    msg << QString().setNum(cc);//SIZE
    msg << QString().setNum(3);//MODE
    for (int i = 0; i < cc; i++) {
        for (int j = 0; j < rc; j++) {
            tmp = ui.tableWidget->item(i, j)->text();
            res = tmp.split('/');
            msg << res.first();
            msg << res.last();

        }
    }
    emit request(msg);
}

void TInterface::answer(QString msg) {
    output->setText(msg);

}