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
    
    bool fix = false;
    int size = cc * rc;//why not just ask sizeDropdown? i can't predict results when click multiple times on same option
    QString tmp;
    QStringList res;
    msg << QString().setNum(cc);//SIZE

    int ourType = typeDetector(ui.tableWidget->item(0, 0)->text());
    msg << QString().setNum(1+ourType);//IMPORTANT:MODE
    
    for (int i = 0; i < cc; i++) {
        for (int j = 0; j < rc; j++) {
            if (ui.tableWidget->item(i, j)) {
                tmp = ui.tableWidget->item(i, j)->text();
                //tmp.contains('/');
                res = tmp.split('/');
                msg << res.first();
                msg << res.last();
            }
        }
    }
    if (fix) { return; }
    
    //emit request(msg);
}

void TClientInterface::rankRequest() {
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

void TClientInterface::transRequest() {
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

void TClientInterface::answer(QString msg) {
    
    output->setText(msg);

}

int TClientInterface::typeDetector(QString i) {
    //QMessageBox type;
    //tmp = ui.tableWidget->item(0, 0)->text();
    if (i.contains("/")) {
        //type.setText("it's rational");
        return 2;
    }
    else
        if (i.contains("i")) {
            //type.setText("it's complex");
            return 1;
        }
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