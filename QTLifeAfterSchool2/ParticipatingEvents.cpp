// ParticipatingEvents.cpp
#include "ParticipatingEvents.h"
#include <QHeaderView>
#include <QMessageBox>

ParticipatingEvents::ParticipatingEvents(UserService& userService, bool removeMode, QWidget* parent)
    : QWidget(parent), userService(userService), removeMode(removeMode), model(nullptr)
{
    setWindowTitle(removeMode ? "Remove Event" : "Participating Events");
    resize(800, 400);

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Use QTableView instead of QTableWidget
    eventsTable = new QTableView(this);
    eventsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    eventsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    layout->addWidget(eventsTable);

    actionButton = new QPushButton(removeMode ? "Remove Event" : "View Details", this);
    closeButton = new QPushButton("Close", this);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(actionButton);
    buttonLayout->addWidget(closeButton);
    layout->addLayout(buttonLayout);

    connect(actionButton, &QPushButton::clicked, this, &ParticipatingEvents::performAction);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    setUpTable();
}

ParticipatingEvents::~ParticipatingEvents()
{
    delete model; // Clean up the model
}

void ParticipatingEvents::setUpTable()
{
    // Create or update the model
    if (!model) {
        model = new EventTableModel(userService.getInterestedEvents(), this);
        eventsTable->setModel(model);

        // Set column widths
        eventsTable->setColumnWidth(0, 150); // Title
        eventsTable->setColumnWidth(1, 250); // Description
        eventsTable->setColumnWidth(2, 150); // Date
        eventsTable->setColumnWidth(3, 80);  // Attendees
        eventsTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch); // Link
    }
    else {
        refreshData();
    }
}

void ParticipatingEvents::refreshData()
{
    if (model) {
        model->updateData(userService.getInterestedEvents());
    }
}

void ParticipatingEvents::performAction()
{
    QModelIndexList selected = eventsTable->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an event.");
        return;
    }

    int row = selected.first().row();
    auto events = userService.getInterestedEvents();
    if (row < 0 || row >= events.size()) {
        return;
    }

    const Event& selectedEvent = events[row];

    if (removeMode) {
        try {
            userService.removeEventFromInterested(selectedEvent);
            QMessageBox::information(this, "Success", "Event removed successfully.");
            refreshData(); // Refresh the model instead of rebuilding
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }
    else {
        QString details = QString("Title: %1\n\nDescription: %2\n\nDate: %3\n\nAttendees: %4\n\nLink: %5")
            .arg(QString::fromStdString(selectedEvent.getTitle()))
            .arg(QString::fromStdString(selectedEvent.getDescription()))
            .arg(QString::fromStdString(selectedEvent.getDateTimeAsString()))
            .arg(selectedEvent.getAttendees())
            .arg(QString::fromStdString(selectedEvent.getLink()));
        QMessageBox::information(this, "Event Details", details);
    }
}