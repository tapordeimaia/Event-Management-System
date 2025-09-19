#pragma once
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QSpinBox>
#include "EventService.h"

class EventForm : public QDialog
{
	Q_OBJECT

public:
	EventForm(EventService& service, bool isUpdate, const Event* existingEvent, QWidget* parent = nullptr);

signals:
	void eventSaved();

private slots:
	void saveEvent();

private:
	EventService& service;
	bool isUpdateMode;
	QLineEdit* titleEdit;
	QLineEdit* descriptionEdit;
	QLineEdit* linkEdit;
	QDateTimeEdit* dateTimeEdit;
	QSpinBox* attendeesEdit;
	QPushButton* saveButton;
	QPushButton* cancelButton;
};

