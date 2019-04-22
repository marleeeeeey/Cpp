#include "QtServer.h"
#include <SFML/Network.hpp>
#include "ServerInterface.h"

QtServer::QtServer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);	
	QObject::connect(ui.listenButton, SIGNAL(clicked()), this, SLOT(start()));
}

void QtServer::start()
{
	appendText(__FUNCSIG__);
	sf::TcpListener listener;

	if (listener.listen(MagicNumbers::port()) != sf::Socket::Done)
	{
		appendText("listen error");
	}

	appendText("listen OK");
	appendText("accept a new connection");
	sf::TcpSocket client;
	if (listener.accept(client) != sf::Socket::Done)
	{
		appendText("accept error");
	}

	appendText("accepted OK");
}

void QtServer::appendText(const char* msg)
{
	ui.chatTextEdit->appendPlainText(msg);
}
