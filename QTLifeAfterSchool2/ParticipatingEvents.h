// ParticipatingEvents.h
#pragma once
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include "UserService.h"
#include "EventTableModel.h"

class ParticipatingEvents : public QWidget
{
    Q_OBJECT

private:
    UserService& userService;
    bool removeMode;
    QTableView* eventsTable;  // Changed from QTableWidget to QTableView
    EventTableModel* model;   // Add model pointer
    QPushButton* actionButton;
    QPushButton* closeButton;

    void setUpTable();
    void refreshData();

private slots:
    void performAction();

public:
    explicit ParticipatingEvents(UserService& userService, bool removeMode = false, QWidget* parent = nullptr);
    ~ParticipatingEvents();
};

