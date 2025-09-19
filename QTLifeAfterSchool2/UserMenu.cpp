#include "UserMenu.h"
#include "BrowseEvents.h"
#include "ViewByMonth.h"
#include "ParticipatingEvents.h"
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>

UserMenu::UserMenu(UserService& userService, QWidget* parent)
	: QWidget(parent), userService(userService)
{
	setWindowTitle("User Menu");
	this->resize(800, 600);
	setUserMenu();
}

void UserMenu::setUserMenu() {
	this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);");

	auto* layoutUser = new QVBoxLayout(this);

	label = new QLabel("User Menu", this);
	QFont font = label->font();
	font.setPointSize(24);
	font.setBold(true);
	font.setFamily("Courier New");
	label->setFont(font);
	label->setAlignment(Qt::AlignCenter);
	layoutUser->addSpacing(40);
	layoutUser->addWidget(label);
	layoutUser->addSpacing(50);

	auto* formatLayout = new QHBoxLayout();
	QLabel* formatLabel = new QLabel("Export Format:", this);
	formatComboBox = new QComboBox(this);
	formatComboBox->addItem("CSV");
	formatComboBox->addItem("HTML");
	formatComboBox->setCurrentIndex(0); // Default to CSV
	userService.setExportType("csv"); // Set default export type

	formatLayout->addWidget(formatLabel);
	formatLayout->addWidget(formatComboBox);
	formatLayout->addStretch();
	layoutUser->addLayout(formatLayout);
	layoutUser->addSpacing(10);

	connect(formatComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, &UserMenu::updateExportType);


	browseEventsButton = new QPushButton("Browse Events", this);
	viewByMonthButton = new QPushButton("View Events by Month", this);
	removeEventButton = new QPushButton("Remove Event", this);
	viewParticipatingEventsButton = new QPushButton("View Participating Events", this);
	saveEventsButton = new QPushButton("Save Events to File", this);
	displayFileEventsButton = new QPushButton("Display Events from File", this);
	closeButton = new QPushButton("Close", this);
	exportButton = new QPushButton("Export to File", this);

	QFont buttonFont = browseEventsButton->font();
	buttonFont.setBold(true);
	buttonFont.setPointSize(14);
	browseEventsButton->setFont(buttonFont);
	viewByMonthButton->setFont(buttonFont);
	removeEventButton->setFont(buttonFont);
	viewParticipatingEventsButton->setFont(buttonFont);
	saveEventsButton->setFont(buttonFont);
	displayFileEventsButton->setFont(buttonFont);
	closeButton->setFont(buttonFont);
	exportButton->setFont(buttonFont);

	QSize buttonSize(235, 50);
	browseEventsButton->setFixedSize(buttonSize);
	viewByMonthButton->setFixedSize(buttonSize);
	removeEventButton->setFixedSize(buttonSize);
	viewParticipatingEventsButton->setFixedSize(buttonSize);
	saveEventsButton->setFixedSize(buttonSize);
	displayFileEventsButton->setFixedSize(buttonSize);
	closeButton->setFixedSize(buttonSize);
	exportButton->setFixedSize(buttonSize);


	auto* buttonLayout = new QVBoxLayout();
	buttonLayout->addWidget(browseEventsButton, 0, Qt::AlignHCenter);
	buttonLayout->addSpacing(10);
	buttonLayout->addWidget(viewByMonthButton, 0, Qt::AlignHCenter);
	buttonLayout->addSpacing(10);
	buttonLayout->addWidget(removeEventButton, 0, Qt::AlignHCenter);
	buttonLayout->addSpacing(10);
	buttonLayout->addWidget(viewParticipatingEventsButton, 0, Qt::AlignHCenter);
	buttonLayout->addSpacing(10);
	buttonLayout->addWidget(saveEventsButton, 0, Qt::AlignHCenter);
	buttonLayout->addSpacing(10);
	buttonLayout->addWidget(exportButton, 0, Qt::AlignHCenter);
	buttonLayout->addSpacing(10);
	buttonLayout->addWidget(displayFileEventsButton, 0, Qt::AlignHCenter);
	buttonLayout->setAlignment(Qt::AlignCenter);
	layoutUser->addLayout(buttonLayout);
	layoutUser->addSpacing(30);
	layoutUser->addStretch();

	closeButton->setFixedSize(100, 30);
	layoutUser->addWidget(closeButton, 0, Qt::AlignHCenter);

	connect(browseEventsButton, &QPushButton::clicked, this, &UserMenu::browseEvents);
	connect(viewByMonthButton, &QPushButton::clicked, this, &UserMenu::viewByMonth);
	connect(removeEventButton, &QPushButton::clicked, this, &UserMenu::removeEvent);
	connect(viewParticipatingEventsButton, &QPushButton::clicked, this, &UserMenu::viewParticipatingEvents);
	connect(saveEventsButton, &QPushButton::clicked, this, &UserMenu::saveEvents);
	connect(exportButton, &QPushButton::clicked, this, &UserMenu::handleExport);
	connect(displayFileEventsButton, &QPushButton::clicked, this, &UserMenu::displayFileEvents);
	connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
	setLayout(layoutUser);
}

void UserMenu::browseEvents() {
	BrowseEvents* browseEvents = new BrowseEvents(userService);
	browseEvents->show();
}

void UserMenu::viewByMonth() {
	ViewByMonth* viewByMonthWindow = new ViewByMonth(userService);
	viewByMonthWindow->show();
}

void UserMenu::removeEvent() {
	ParticipatingEvents* participatingEvents = new ParticipatingEvents(userService, this);
	participatingEvents->show();
}

void UserMenu::viewParticipatingEvents() {
	ParticipatingEvents* participatingEvents = new ParticipatingEvents(userService);
	participatingEvents->show();
}

void UserMenu::saveEvents() {
	QString fileName = QFileDialog::getSaveFileName(this, "Save Events to File", "", "Text Files (*.txt);;All Files (*)");
	if (fileName.isEmpty()) {
		return;
	}
	std::ofstream file(fileName.toStdString());
	if (!file) {
		QMessageBox::warning(this, "Error", "Could not open file for writing.");
		return;
	}
	auto events = userService.getInterestedEvents();
	for (const auto& event : events) {
		file << event.getTitle() << "\n";
		file << event.getDescription() << "\n";
		file << event.getDateTimeAsString() << "\n";
		file << event.getAttendees() << "\n";
		file << event.getLink() << "\n\n";
	}
	QMessageBox::information(this, "Success", "Events saved successfully.");
}

void UserMenu::displayFileEvents() {
	QString filter = formatComboBox->currentText() == "CSV"
		? "CSV Files (*.csv);;All Files (*)"
		: "HTML Files (*.html);;All Files (*)";

	QString fileName = QFileDialog::getOpenFileName(
		this,
		"Open Exported File",
		"",
		filter
	);

	if (fileName.isEmpty()) {
		return;
	}

	try {
		userService.displayExportedFile(fileName.toStdString());
	}
	catch (const std::exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
}

void UserMenu::handleExport()
{
	QString fileName = QFileDialog::getSaveFileName(
		this,
		"Export Events",
		"",
		formatComboBox->currentText() == "CSV" ? "CSV Files (*.csv);;All Files (*)"
		: "HTML Files (*.html);;All Files (*)"
	);

	if (fileName.isEmpty()) {
		return;
	}

	try {
		userService.exportInterestedEvents(fileName.toStdString());
		QMessageBox::information(this, "Success", "Events exported successfully");
	}
	catch (const std::exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
}

void UserMenu::updateExportType(int index)
{
	try {
		QString type = formatComboBox->itemText(index).toLower();
		userService.setExportType(type.toStdString());
	}
	catch (const std::exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
}





