#include "ListAdminEvents.h"
#include <QHeaderView>

ListAdminEvents::ListAdminEvents(EventService& service, bool selectionMode, QWidget* parent)
	: QWidget(parent), service(service), selectionMode(selectionMode) 
{
	this->resize(1400, 500);
	setWindowTitle("All events");
	this->setStyleSheet("background-color: #f8f9fa;");

	auto* layout = new QVBoxLayout(this);

	viewComboBox = new QComboBox(this);
	viewComboBox->addItem("Detailed View");
	viewComboBox->addItem("Short view");
	connect(viewComboBox, &QComboBox::currentTextChanged, this, &ListAdminEvents::onViewChanged);
	layout->addWidget(viewComboBox, 0, Qt::AlignRight);

	eventsTable = new QTableWidget(this);
	eventsTable->setColumnCount(5);
	eventsTable->setHorizontalHeaderLabels({ "Title", "Description", "Link", "Date", "Number of people" });
	layout->addWidget(eventsTable);

	closeButton = new QPushButton("Close", this);
	closeButton->setFixedSize(100, 30);
	layout->addWidget(closeButton, 0, Qt::AlignHCenter);

	connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
	completeTable();
}

void ListAdminEvents::completeTable() {
	eventsTable->setColumnWidth(4, 300);
	eventsTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
	
	if (viewComboBox->currentText() == "Detailed View") {
		displayDetailedView();
	}
	else {
		displayShortView();
	}

	if (selectionMode) {
		connect(eventsTable, &QTableWidget::cellDoubleClicked, [this](int row) {
			auto events = service.getAllEvents();
			if (row >= 0 && row < events.size()) {
				emit eventSelected(events[row]);
				close();
			}
			});
	}
}

void ListAdminEvents::displayDetailedView() {
	eventsTable->setColumnCount(5);
	eventsTable->setHorizontalHeaderLabels({ "Title", "Description", "Link", "Date", "Number of people" });
	eventsTable->clearContents();
	auto events = service.getAllEvents();
	eventsTable->setRowCount(events.size());
	for (int i = 0; i < events.size(); ++i) {
		const Event& event = events[i];
		eventsTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(event.getTitle())));
		eventsTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(event.getDescription())));
		eventsTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(event.getLink())));
		eventsTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(event.getDateTimeAsString())));
		eventsTable->setItem(i, 4, new QTableWidgetItem(QString::number(event.getAttendees())));
	}
}

void ListAdminEvents::displayShortView() {
	eventsTable->setColumnCount(2);
	eventsTable->setHorizontalHeaderLabels({ "Title", "Date"});
	eventsTable->clearContents();
	auto events = service.getAllEvents();
	eventsTable->setRowCount(events.size());
	for (int i = 0; i < events.size(); ++i) {
		const Event& event = events[i];
		eventsTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(event.getTitle())));
		eventsTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(event.getDateTimeAsString())));
	}
}

void ListAdminEvents::onViewChanged() {
	completeTable();
}
