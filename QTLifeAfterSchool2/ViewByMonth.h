#pragma once
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include "UserService.h"

class ViewByMonth : public QWidget
{
	Q_OBJECT

private:
	UserService& userService;
	QComboBox* monthComboBox;
	QPushButton* browseButton;
	QTextEdit* eventsDisplay;
	QPushButton* closeButton;

private slots:
	void browseSelectedMonth();

public:
	explicit ViewByMonth(UserService& userService, QWidget* parent = nullptr);
};

