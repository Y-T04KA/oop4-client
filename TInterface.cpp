#include "TInterface.h"
#include "qmessagebox.h"

TClientInterface::TClientInterface(QWidget *parent)
    : QMainWindow(parent)
{  
    ui.setupUi(this);
    setupDropdown();
    output = new QLabel(this);
    output->setGeometry(10, 200, 280, 50);
    ui.tableWidget->setColumnCount(2);
    ui.tableWidget->setRowCount(2);
    detButton = new QPushButton("Определитель",this);
    detButton->setGeometry(484, 50, 91, 24);
    rankButton = new QPushButton("Ранг", this);
    rankButton->setGeometry(484, 100, 91, 24);
    transButton = new QPushButton("Транспон.", this);
    transButton->setGeometry(484, 150, 91, 24);

    connect(detButton, SIGNAL(pressed()), this, SLOT(detRequest()));
    connect(rankButton, SIGNAL(pressed()), this, SLOT(rankRequest()));
    connect(transButton, SIGNAL(pressed()), this, SLOT(transRequest()));
}

TClientInterface::~TClientInterface()
{}

void TClientInterface::setupDropdown() {
    ui.sizeDropdown->addItem("2", two);
    ui.sizeDropdown->addItem("3", three);
    ui.sizeDropdown->addItem("4", four);
    two.setValue(2);
    three.setValue(3);
    four.setValue(4);
    
}

void TClientInterface::resizeInput() {
    int size = ui.sizeDropdown->currentText().toInt();//debugger says it returns 3, but to have 2x2 matrix i need to decrease 2 to 1???
    ui.tableWidget->setColumnCount(size-1);
    ui.tableWidget->setRowCount(size-1);//size when 2 is actually 3???
}


void TClientInterface::detRequest() {
    int cc = ui.tableWidget->columnCount(), rc = ui.tableWidget->rowCount();
    if (!cellsFilled(cc, rc)) return; //cancel if there are empty cells
    QString msg;//SIZE MODE DATA
    int size = cc * rc;//why not just ask sizeDropdown? i can't predict results when click multiple times on same option
    msg << QString().setNum(cc);//SIZE
    int ourType = typeDetector(ui.tableWidget->item(0, 0)->text());
    msg << QString().setNum(1+ourType);//IMPORTANT:MODE
    for (int i = 0; i < cc; i++) {
        for (int j = 0; j < rc; j++) {
            if (ourType == typeDetector(ui.tableWidget->item(i, j)->text())) {
                //tmp = ui.tableWidget->item(i, j)->text();
                //res = tmp.split('/');
                //msg << res.first();
                //msg << res.last();
                msg << cellDataHandler(ui.tableWidget->item(i, j)->text(), ourType);
            }
            else {
                QMessageBox q;
                q.setText("type mismatch");
                q.exec();
                return;
            }
        }
    }
    emit request(msg);
}

void TClientInterface::rankRequest() {
    int cc = ui.tableWidget->columnCount(), rc = ui.tableWidget->rowCount();
    if (!cellsFilled(cc, rc)) return; //cancel if there are empty cells
    QString msg;//SIZE MODE DATA
    int size = cc * rc;//why not just ask sizeDropdown? i can't predict results when click multiple times on same option
    msg << QString().setNum(cc);//SIZE
    int ourType = typeDetector(ui.tableWidget->item(0, 0)->text());
    msg << QString().setNum(4 + ourType);//IMPORTANT:MODE
    for (int i = 0; i < cc; i++) {
        for (int j = 0; j < rc; j++) {
            if (ourType == typeDetector(ui.tableWidget->item(i, j)->text())) {
                msg << cellDataHandler(ui.tableWidget->item(i, j)->text(), ourType);
            }
            else {
                QMessageBox q;
                q.setText("type mismatch");
                q.exec();
                return;
            }
        }
    }
    emit request(msg);
}

void TClientInterface::transRequest() {
    int cc = ui.tableWidget->columnCount(), rc = ui.tableWidget->rowCount();
    if (!cellsFilled(cc, rc)) return; //cancel if there are empty cells
    QString msg;//SIZE MODE DATA
    int size = cc * rc;//why not just ask sizeDropdown? i can't predict results when click multiple times on same option
    msg << QString().setNum(cc);//SIZE
    int ourType = typeDetector(ui.tableWidget->item(0, 0)->text());
    msg << QString().setNum(7 + ourType);//IMPORTANT:MODE
    for (int i = 0; i < cc; i++) {
        for (int j = 0; j < rc; j++) {
            if (ourType == typeDetector(ui.tableWidget->item(i, j)->text())) {
                msg << cellDataHandler(ui.tableWidget->item(i, j)->text(), ourType);
            }
            else {
                QMessageBox q;
                q.setText("type mismatch");
                q.exec();
                return;
            }
        }
    }
    emit request(msg);
}

void TClientInterface::answer(QString msg) {
    output->setText(msg);
}

int TClientInterface::typeDetector(QString i) {
    if (i.contains("/"))return 2;
    else if (i.contains("i")) return 1;
    else return 0;
}

bool TClientInterface::cellsFilled(int cc, int rc) {
    QMessageBox fail;
    for (int i = 0; i < cc; i++) {
        for (int j = 0; j < rc; j++) {
            if (!ui.tableWidget->item(i, j)) { 
                fail.setText("uninitialized cells");
                fail.exec();
                return false; 
            }
            else if(ui.tableWidget->item(i, j)->text().isEmpty()) {
                fail.setText("empty cells");
                fail.exec();
                return false;
            }
        }
    }
    return true;
}

QString TClientInterface::cellDataHandler(QString data, int type) {
    QString retval;
    QStringList res;
    switch (type)
    {
    case 1://rational
        res = data.split('+');
        retval = res.first();
        retval += separator;
        res.last().chop(1);//remove 'i' symbol
        retval += res.last();
        break;
    case 2://complex
        res = data.split('/');
        retval = res.first();
        retval += separator;//so it needs separated values with ;, and last ; will be appended by caller
        retval += res.last();
        break;
    default://double
        retval = data;
        break;
    }
    return retval;
}