#include "QtClient.h"
#include <SFML/Network.hpp>
#include "ServerInterface.h"

QtClient::QtClient(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);	
	QObject::connect(ui.listenButton, SIGNAL(clicked()), this, SLOT(start()));
}

void QtClient::start()
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

void QtClient::appendText(const char* msg)
{
	ui.chatTextEdit->appendPlainText(msg);
}
