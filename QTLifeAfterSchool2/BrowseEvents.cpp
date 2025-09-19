#include "BrowseEvents.h"
#include <QMessageBox>

BrowseEvents::BrowseEvents(UserService& userService, QWidget* parent)
	: QWidget(parent), userService(userService) {
	setWindowTitle("Browse Events");
	resize(600, 400);

	userService.startBrowsing();

	QVBoxLayout* layout = new QVBoxLayout(this);

	eventLabel = new QLabel("Current Event", this);
	eventLabel->setAlignment(Qt::AlignCenter);
	QFont font = eventLabel->font();
	font.setPointSize(16);
	font.setBold(true);
	eventLabel->setFont(font);
	layout->addWidget(eventLabel);

	eventDetails = new QTextEdit(this);
	eventDetails->setReadOnly(true);
	layout->addWidget(eventDetails);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	nextButton = new QPushButton("Next Event", this);
	addButton = new QPushButton("Add to Interested", this);
	closeButton = new QPushButton("Close", this);

	buttonLayout->addWidget(nextButton);
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(closeButton);
	layout->addLayout(buttonLayout);

	connect(nextButton, &QPushButton::clicked, this, &BrowseEvents::nextEvent);
	connect(addButton, &QPushButton::clicked, this, &BrowseEvents::addCurrentEvent);
	connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

	displayCurrentEvent();
}

void BrowseEvents::displayCurrentEvent() {
	try {
		Event current = userService.getCurrentEvent();
		QString details = QString("Title: %1\n\nDescription: %2\n\nDate: %3\n\nAttendees: %4\n\nLink: %5")
			.arg(QString::fromStdString(current.getTitle()))
			.arg(QString::fromStdString(current.getDescription()))
			.arg(QString::fromStdString(current.getDateTimeAsString()))
			.arg(current.getAttendees())
			.arg(QString::fromStdString(current.getLink()));
		eventDetails->setText(details);
	}
	catch (const std::exception& e) {
		eventDetails->setText("No events to display");
		nextButton->setEnabled(false);
		addButton->setEnabled(false);
	}
}

void BrowseEvents::nextEvent() {
	userService.nextEvent();
	displayCurrentEvent();
}

void BrowseEvents::addCurrentEvent() {
	try {
		userService.addEventToInterested();

		// This is now handled in UserService
		QMessageBox::information(this, "Success",
			"Event added to your list and link opened!");
	}
	catch (const std::exception& e) {
		QMessageBox::warning(this, "Error", e.what());
	}
}