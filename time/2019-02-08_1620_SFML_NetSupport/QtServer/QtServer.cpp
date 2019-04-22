#include "QtServer.h"

QtServer::QtServer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QObject::connect(ui.listenButton, SIGNAL(clicked()), this, SLOT(start()));

}

void QtServer::start()
{
	ui.chatTextEdit->appendPlainText(__FUNCSIG__);
}