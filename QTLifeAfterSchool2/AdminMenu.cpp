#include "AdminMenu.h"
#include "ListAdminEvents.h"
#include "EventForm.h"
#include <QMessageBox>
#include <QShortCut>

AdminMenu::AdminMenu(EventService& service, QWidget* parent) : QWidget(parent), service(service)
{
	setWindowTitle("Administrator");
	this->resize(800, 600);
	setAdmin();
}

void AdminMenu::setAdmin()
{
	this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #667eea, stop:1 #764ba2);");

	auto* layoutAdmin = new QVBoxLayout(this);

	label = new QLabel("Administrator Menu", this);
	QFont font = label->font();
	font.setPointSize(22);
	font.setBold(true);
	font.setFamily("Verdana");
	label->setFont(font);
	label->setAlignment(Qt::AlignCenter);
	layoutAdmin->addSpacing(60);
	layoutAdmin->addWidget(label);
	layoutAdmin->addSpacing(80);
	addButton = new QPushButton("Add Event", this);
	removeButton = new QPushButton("Remove Event", this);
	updateButton = new QPushButton("Update Event", this);
	listButton = new QPushButton("List Events", this);
	closeButton = new QPushButton("Close", this);

	QSize buttonSize(200, 50);
	addButton->setFixedSize(buttonSize);
	removeButton->setFixedSize(buttonSize);
	updateButton->setFixedSize(buttonSize);
	listButton->setFixedSize(buttonSize);

	QFont buttonFont = addButton->font();
	buttonFont.setBold(true);
	buttonFont.setPointSize(14);
	addButton->setFont(buttonFont);
	removeButton->setFont(buttonFont);
	updateButton->setFont(buttonFont);
	listButton->setFont(buttonFont);
	closeButton->setFont(buttonFont);

	QString buttonStyle = "QPushButton { color: black; }";


	auto* buttonLayout = new QVBoxLayout();
	buttonLayout->addWidget(addButton, 0, Qt::AlignHCenter);
	buttonLayout->addSpacing(10);
	buttonLayout->addWidget(removeButton, 0, Qt::AlignHCenter);
	buttonLayout->addSpacing(10);
	buttonLayout->addWidget(updateButton, 0, Qt::AlignHCenter);
	buttonLayout->addSpacing(10);
	buttonLayout->addWidget(listButton, 0, Qt::AlignHCenter);
	buttonLayout->setAlignment(Qt::AlignCenter);
	layoutAdmin->addLayout(buttonLayout);
	layoutAdmin->addSpacing(50);
	layoutAdmin->addStretch();

	closeButton->setFixedSize(100, 30);
	layoutAdmin->addWidget(closeButton, 0, Qt::AlignHCenter);

	connect(addButton, &QPushButton::clicked, this, &AdminMenu::handleAdd);
	connect(removeButton, &QPushButton::clicked, this, &AdminMenu::handleRemove);
	connect(updateButton, &QPushButton::clicked, this, &AdminMenu::handleUpdate);
	connect(listButton, &QPushButton::clicked, this, &AdminMenu::openWindows);
	connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
	
	setLayout(layoutAdmin);

	// Add undo/redo buttons
	undoButton = new QPushButton("Undo (Ctrl+Z)", this);
	redoButton = new QPushButton("Redo (Ctrl+Y)", this);

	// Make them match other buttons
	undoButton->setFixedSize(buttonSize);
	redoButton->setFixedSize(buttonSize);
	undoButton->setFont(buttonFont);
	redoButton->setFont(buttonFont);
	undoButton->setStyleSheet(buttonStyle);
	redoButton->setStyleSheet(buttonStyle);

	// Add to layout with proper spacing
	buttonLayout->addSpacing(20);
	buttonLayout->addWidget(undoButton, 0, Qt::AlignHCenter);
	buttonLayout->addSpacing(10);
	buttonLayout->addWidget(redoButton, 0, Qt::AlignHCenter);

	// Connect signals with proper state checking
	connect(undoButton, &QPushButton::clicked, this, [this]() {
		if (service.canUndo()) {
			service.undo();
			updateUndoRedoButtons();
			// Force UI update if needed
			if (auto listWindow = findChild<ListAdminEvents*>()) {
				listWindow->completeTable();
			}
		}
		});

	connect(redoButton, &QPushButton::clicked, this, [this]() {
		if (service.canRedo()) {
			service.redo();
			updateUndoRedoButtons();
			// Force UI update if needed
			if (auto listWindow = findChild<ListAdminEvents*>()) {
				listWindow->completeTable();
			}
		}
		});

	// Keyboard shortcuts
	auto* undoShortcut = new QShortcut(QKeySequence::Undo, this);
	auto* redoShortcut = new QShortcut(QKeySequence::Redo, this);
	connect(undoShortcut, &QShortcut::activated, this, [this]() {
		if (undoButton->isEnabled()) undoButton->click();
		});
	connect(redoShortcut, &QShortcut::activated, this, [this]() {
		if (redoButton->isEnabled()) redoButton->click();
		});

	// Initial state
	updateUndoRedoButtons();
}

void AdminMenu::openWindows()
{
	auto* viewAdminEvents = new ListAdminEvents(service);
	viewAdminEvents->show();
}

void AdminMenu::handleAdd()
{
	showEventForm(false);
}

void AdminMenu::handleRemove()
{
	auto* listWindow = new ListAdminEvents(service, true);
	connect(listWindow, &ListAdminEvents::eventSelected, this, [this](const Event& event) {
		try {
			service.removeEvent(event.getTitle(), event.getDateTime());
			QMessageBox::information(this, "Success", "Event removed successfully.");
		}
		catch (const std::exception& e) {
			QMessageBox::warning(this, "Error", e.what());
		}
		});
	listWindow->show();
}

void AdminMenu::handleUpdate()
{
	auto* listWindow = new ListAdminEvents(service, true);
	connect(listWindow, &ListAdminEvents::eventSelected, this, [this](const Event& event) {
		this->originalEventForUpdate = event;
		showEventForm(true, &event);
		});
	listWindow->show();
}

void AdminMenu::handleList() {
	auto* listWindow = new ListAdminEvents(service);
	listWindow->show();
}

void AdminMenu::showEventForm(bool isUpdate, const Event* existingEvent)
{
	auto* eventForm = new EventForm(service, isUpdate, existingEvent, this);
	connect(eventForm, &EventForm::eventSaved, [this]() {
		QMessageBox::information(this, "Success", "Event saved successfully.");
		});
	eventForm->show();
}