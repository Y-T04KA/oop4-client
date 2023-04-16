#pragma once
#include <qobject.h>
#include <qapplication.h>
#include <TInterface.h>
#include <Comms.h>

class TClientApp : public QApplication {
	Q_OBJECT
	TComms* comm;
	TClientInterface* interface;
public:
	TClientApp(int, char**);
public slots:
	void fromComms(QByteArray);
	void toComms(QString);
};

