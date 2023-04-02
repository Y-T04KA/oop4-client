#pragma once
#include <qobject.h>
#include <qapplication.h>
#include <TInterface.h>
#include <Comms.h>

class TApplication : public QApplication {
	Q_OBJECT
	TComms* comm;
	TInterface* interface;
public:
	TApplication(int, char**);
public slots:
	void fromComms(QByteArray);
	void toComms(QString);
};

