#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include "EventService.h"
#include "ui_QtLifeAfterSchool.h"

class ListAdminEvents : public QWidget
{
	Q_OBJECT

protected:
	EventService& service;
	QTableWidget* eventsTable;
	QPushButton* closeButton;
	QComboBox* viewComboBox;
	bool selectionMode;
	
	void displayShortView();
	void displayDetailedView();

private slots:
	void onViewChanged();

public:
	explicit ListAdminEvents(EventService& service, bool selectionMode = false, QWidget* parent = nullptr);
	~ListAdminEvents() override = default;
	void completeTable();
signals:
	void eventSelected(const Event& event);
};

