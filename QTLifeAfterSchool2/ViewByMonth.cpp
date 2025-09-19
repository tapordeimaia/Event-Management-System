#include "ViewByMonth.h"
#include <QMessageBox>
#include <QDate>
#include <QLocale>
#include <iomanip>
#include <sstream>

ViewByMonth::ViewByMonth(UserService& userService, QWidget* parent)
	: QWidget(parent), userService(userService)
{
	setWindowTitle("View Events by Month");
	resize(600, 400);

	QVBoxLayout* layout = new QVBoxLayout(this);

	monthComboBox = new QComboBox(this);
	QLocale locale;
	for (int i = 1; i <= 12; ++i) {
		monthComboBox->addItem(locale.monthName(i));
	}
	layout->addWidget(monthComboBox);

	browseButton = new QPushButton("Browse", this);
	layout->addWidget(browseButton);

	eventsDisplay = new QTextEdit(this);
	eventsDisplay->setReadOnly(true);
	layout->addWidget(eventsDisplay);

	closeButton = new QPushButton("Close", this);
	layout->addWidget(closeButton);

	connect(browseButton, &QPushButton::clicked, this, &ViewByMonth::browseSelectedMonth);
	connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
}

void ViewByMonth::browseSelectedMonth()
{
	int month = monthComboBox->currentIndex() + 1;
	userService.startBrowsing(month);
	try {
		Event current = userService.getCurrentEvent();
		QString details = QString("Title: %1\n\nDescription: %2\n\nDate: %3\n\nAttendees: %4\n\nLink: %5")
			.arg(QString::fromStdString(current.getTitle()))
			.arg(QString::fromStdString(current.getDescription()))
			.arg(QString::fromStdString(current.getDateTimeAsString()))
			.arg(current.getAttendees())
			.arg(QString::fromStdString(current.getLink()));
		eventsDisplay->setText(details);
	}
	catch (const std::exception& e) {
		eventsDisplay->setText(QString("No events found for %1").arg(monthComboBox->currentText()));
	}
}