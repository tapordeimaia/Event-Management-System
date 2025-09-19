#pragma once
#include "ui_QtLifeAfterSchool.h"
#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "EventService.h"
#include "UserService.h"

class GUI : public QWidget
{
	Q_OBJECT

private:
	EventService& service;
	UserService userService;
	QTableWidget* eventsTable;
	QPushButton* closeButton;
	QPushButton* adminButton;
	QPushButton* userButton;
	QSpacerItem* spacer;

	void setupUI();

private slots:
	void adminMenu();
	void userMenu();

public:
	explicit GUI(EventService& service, EventRepository& repo, QWidget* parent = nullptr);
	~GUI();
};

