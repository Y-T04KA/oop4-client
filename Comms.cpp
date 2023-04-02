#include "Comms.h"
#include <qmessagebox.h>

TComms::TComms(TCommParams& pars, QObject* parent) :QUdpSocket(parent) {
	params = pars;
	ready = bind(params.rHost, params.rPort, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
	if (ready) connect(this, SIGNAL(readyRead()), this, SLOT(receive()));
}

bool TComms::isReady(){
	return ready;
}

void TComms::send(QByteArray msg) {
	if (ready) {
		QMessageBox msgBox;
		msgBox.setText("reached writeDatagram()");
		msgBox.exec();
		writeDatagram(msg, params.sHost, params.sPort);
	}
}

void TComms::receive() {
	if (hasPendingDatagrams()) {
		quint64 size = pendingDatagramSize();
		QByteArray msg(size, '\0');
		readDatagram(msg.data(), size);
		QMessageBox msgBox;
		msgBox.setText(QString().setNum(size));
		msgBox.exec();
		emit received(msg);
	}
}