#include "EventForm.h"
#include <QLabel>
#include <QMessageBox>

EventForm::EventForm(EventService& service, bool isUpdate, const Event* existingEvent, QWidget* parent)
	: QDialog(parent), service(service), isUpdateMode(isUpdate)
{
	setWindowTitle(isUpdate ? "Update Event" : "Add Event");
	setModal(true);
	resize(400, 300);

	QFormLayout* layout = new QFormLayout(this);

	titleEdit = new QLineEdit(this);
	descriptionEdit = new QLineEdit(this);
	dateTimeEdit = new QDateTimeEdit(this);
	attendeesEdit = new QSpinBox(this);
	attendeesEdit->setMinimum(0);
	linkEdit = new QLineEdit(this);

	if (isUpdate && existingEvent) {
		titleEdit->setText(QString::fromStdString(existingEvent->getTitle()));
		descriptionEdit->setText(QString::fromStdString(existingEvent->getDescription()));
		QDateTime dt;
		dt.setDate(QDate(existingEvent->getDateTime().tm_year + 1900, existingEvent->getDateTime().tm_mon + 1, existingEvent->getDateTime().tm_mday));
		dt.setTime(QTime(existingEvent->getDateTime().tm_hour, existingEvent->getDateTime().tm_min));
		dateTimeEdit->setDateTime(dt);
		attendeesEdit->setValue(existingEvent->getAttendees());
		linkEdit->setText(QString::fromStdString(existingEvent->getLink()));
	}

	layout->addRow("Title: ", titleEdit);
	layout->addRow("Description: ", descriptionEdit);
	layout->addRow("Date and Time: ", dateTimeEdit);
	layout->addRow("Attendees: ", attendeesEdit);
	layout->addRow("Link: ", linkEdit);

	auto* buttonLayout = new QHBoxLayout();
	saveButton = new QPushButton(isUpdate ? "Update" : "Add", this);
	cancelButton = new QPushButton("Cancel", this);

	buttonLayout->addWidget(saveButton);
	buttonLayout->addWidget(cancelButton);
	layout->addRow(buttonLayout);

	connect(saveButton, &QPushButton::clicked, this, &EventForm::saveEvent);
	connect(cancelButton, &QPushButton::clicked, this, &QWidget::close);

}

void EventForm::saveEvent() {
	try {
		std::tm tm = { 0 };
		QDateTime dt = dateTimeEdit->dateTime();
		tm.tm_year = dt.date().year() - 1900;
		tm.tm_mon = dt.date().month() - 1;
		tm.tm_mday = dt.date().day();
		tm.tm_hour = dt.time().hour();
		tm.tm_min = dt.time().minute();

		if (isUpdateMode) {
			auto events = service.getAllEvents();
			Event originalEvent;
			bool found = false;

			for (const auto& event : events) {
				if (event.getTitle() == titleEdit->text().toStdString() &&
					event.getDateTime().tm_year == tm.tm_year &&
					event.getDateTime().tm_mon == tm.tm_mon &&
					event.getDateTime().tm_mday == tm.tm_mday) {
					originalEvent = event;
					found = true;
					break;
				}
			}

			if (!found) {
				throw std::runtime_error("Original event not found");
			}

			// Create the updated event
			Event updatedEvent(
				titleEdit->text().toStdString(),
				descriptionEdit->text().toStdString(),
				tm,
				attendeesEdit->value(),
				linkEdit->text().toStdString()
			);

			// Perform the update
			service.updateEvent(originalEvent.getTitle(), originalEvent.getDateTime(), updatedEvent.getTitle(), updatedEvent.getDescription(), updatedEvent.getDateTime(), updatedEvent.getAttendees(), updatedEvent.getLink());
		}
		else {
			service.addEvent(titleEdit->text().toStdString(), descriptionEdit->text().toStdString(), tm, attendeesEdit->value(), linkEdit->text().toStdString());
		}

		emit eventSaved();
		accept();
	}
	catch (const std::exception& e) {
		QMessageBox::warning(this, "Error", e.what());
	}
}