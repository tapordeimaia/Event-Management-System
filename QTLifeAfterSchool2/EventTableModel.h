#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Event.h"

class EventTableModel : public QAbstractTableModel
{
    Q_OBJECT
        std::vector<Event> events;

public:
    explicit EventTableModel(const std::vector<Event>& events, QObject* parent = nullptr)
        : QAbstractTableModel(parent), events(events) {
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return events.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5; 
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= events.size() || role != Qt::DisplayRole)
            return QVariant();

        const Event& event = events[index.row()];
        switch (index.column()) {
        case 0: return QString::fromStdString(event.getTitle());
        case 1: return QString::fromStdString(event.getDescription());
        case 2: return QString::fromStdString(event.getDateTimeAsString());
        case 3: return event.getAttendees();
        case 4: return QString::fromStdString(event.getLink());
        default: return QVariant();
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
            return QVariant();

        switch (section) {
        case 0: return "Title";
        case 1: return "Description";
        case 2: return "Date";
        case 3: return "Attendees";
        case 4: return "Link";
        default: return QVariant();
        }
    }

    void updateData(const std::vector<Event>& newEvents) {
        beginResetModel();
        events = newEvents;
        endResetModel();
    }
};