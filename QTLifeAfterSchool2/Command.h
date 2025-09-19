#pragma once
#include "Event.h"
#include "EventRepository.h"
#include <memory>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AddCommand : public Command {
    EventRepository& repository;
    Event event;
public:
    AddCommand(EventRepository& repository, const Event& event)
        : repository(repository), event(event) {
    }
    void execute() override { repository.addEvent(event); }
    void undo() override { repository.removeEvent(event); }
};

class RemoveCommand : public Command {
    EventRepository& repository;
    Event event;
public:
    RemoveCommand(EventRepository& repository, const Event& event)
        : repository(repository), event(event) {
    }
    void execute() override { repository.removeEvent(event); }
    void undo() override { repository.addEvent(event); }
};

class UpdateCommand : public Command {
    EventRepository& repository;
    Event oldEvent;
    Event newEvent;
public:
    UpdateCommand(EventRepository& repository, const Event& oldEvent, const Event& newEvent)
        : repository(repository), oldEvent(oldEvent), newEvent(newEvent) {
    }
    void execute() override { repository.updateEvent(oldEvent, newEvent); }
    void undo() override { repository.updateEvent(newEvent, oldEvent); }
};