#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include "UserService.h"

class BrowseEvents : public QWidget
{
	Q_OBJECT

private:
	UserService& userService;
	QLabel* eventLabel;
	QTextEdit* eventDetails;
	QPushButton* nextButton;
	QPushButton* addButton;
	QPushButton* closeButton;

	void displayCurrentEvent();

private slots:
	void nextEvent();
	void addCurrentEvent();

public:
	explicit BrowseEvents(UserService& userService, QWidget* parent = nullptr);
};

