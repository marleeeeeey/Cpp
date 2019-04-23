#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtClient.h"


class QtClient : public QMainWindow
{
	Q_OBJECT

public:
	QtClient(QWidget *parent = Q_NULLPTR);

public slots:
	void start();

private:
	void appendText(const char* msg);

	Ui::QtClientClass ui;
};
