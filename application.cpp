#include "application.h"
#include "qmessagebox.h"

TClientApp::TClientApp(int argc, char* argv[]) :QApplication(argc, argv) {
	TCommParams pars = { QHostAddress("127.0.0.1"),10001,QHostAddress("127.0.0.1"),10000 };
	comm = new TComms(pars, this);
	interface = new TClientInterface();
	interface->show();
	connect(comm, SIGNAL(received(QByteArray)), this, SLOT(fromComms(QByteArray)));
	connect(interface, SIGNAL(request(QString)), this, SLOT(toComms(QString)));
}

void TClientApp::fromComms(QByteArray msg) {
	interface->answer(QString(msg));
}

void TClientApp::toComms(QString msg) {
	comm->send(QByteArray().append(QByteArray().fromStdString(msg.toStdString())));
}