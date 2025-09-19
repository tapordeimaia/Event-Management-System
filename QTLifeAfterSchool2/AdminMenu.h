#pragma once
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include "EventService.h"
#include "ui_QtLifeAfterSchool.h"

class AdminMenu : public QWidget
{
	Q_OBJECT

private:
	EventService& service;
	QTableWidget* eventsTable;
	QPushButton* closeButton;
	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* updateButton;
	QPushButton* listButton;
	QPushButton* undoButton;
	QPushButton* redoButton;
	QLabel* label;

	void setAdmin();
	void showEventForm(bool isUpdate = false, const Event* existingEvent = nullptr);

private slots:
	void openWindows();
	void handleAdd();
	void handleRemove();
	void handleUpdate();
	void handleList();

public:
	explicit AdminMenu(EventService& service, QWidget* parent = nullptr);
	~AdminMenu() override = default;
private:  
	Event originalEventForUpdate;
	
	void updateUndoRedoButtons() {
		qDebug() << "canUndo:" << service.canUndo() << "canRedo:" << service.canRedo();
		//undoButton->setEnabled(service.canUndo());
		//redoButton->setEnabled(service.canRedo());
	}
};

