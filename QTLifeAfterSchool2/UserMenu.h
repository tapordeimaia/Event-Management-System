#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "UserService.h"
#include "ui_QtLifeAfterSchool.h"

class UserMenu : public QWidget
{
	Q_OBJECT

private:
	UserService& userService;
	QPushButton* browseEventsButton;
	QPushButton* viewByMonthButton;
	QPushButton* removeEventButton;
	QPushButton* viewParticipatingEventsButton;
	QPushButton* saveEventsButton;
	QPushButton* displayFileEventsButton;
	QPushButton* closeButton;
	QLabel* label;
	QPushButton* exportButton;
	QComboBox* formatComboBox;

	void setUserMenu();

private slots:
	void browseEvents();
	void viewByMonth();
	void removeEvent();
	void viewParticipatingEvents();
	void saveEvents();
	void displayFileEvents();
	void handleExport();
	void updateExportType(int index);

public:
	explicit UserMenu(UserService& userService, QWidget* parent = nullptr);
	~UserMenu() override = default;
};