#include "application.h"
#include "qmessagebox.h"

TApplication::TApplication(int argc, char* argv[]) :QApplication(argc, argv) {
	TCommParams pars = { QHostAddress("127.0.0.1"),10001,QHostAddress("127.0.0.1"),10000 };
	comm = new TComms(pars, this);
	interface = new TInterface();
	interface->show();
	connect(comm, SIGNAL(received(QByteArray)), this, SLOT(fromComms(QByteArray)));
	connect(interface, SIGNAL(request(QString)), this, SLOT(toComms(QString)));
}

void TApplication::fromComms(QByteArray msg) {
	QMessageBox msgBox;
	msgBox.setText("reached fromComms");
	msgBox.exec();
	interface->answer(QString(msg));
}

void TApplication::toComms(QString msg) {
	QMessageBox msgBox;
	msgBox.setText("reached toComms()");
	msgBox.exec();
	comm->send(QByteArray().append(QByteArray().fromStdString(msg.toStdString())));
}