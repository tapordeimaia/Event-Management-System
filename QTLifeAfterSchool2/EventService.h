#pragma once
#include "EventRepository.h"
#include "event.h"
#include <ctime>
#include <string>
#include "UndoRedoManager.h"

class EventService {
private:
	EventRepository& repository;
	UndoRedoManager undoManager;

public:
	EventService(EventRepository& repo);

	void undo() { undoManager.undo(); }
	void redo() { undoManager.redo(); }
	bool canUndo() const { return undoManager.canUndo(); }
	bool canRedo() const { return undoManager.canRedo(); }

	void addEvent(const std::string& title, const std::string& description,
		const std::tm& dateTime, int attendees, const std::string& link);
	void removeEvent(const std::string& title, const std::tm& dateTime);
	void updateEvent(const std::string& oldTitle, const std::tm& oldDateTime, const std::string& newTitle , const std::string& newDescription, const std::tm& newDateTime, int newAttendees, const std::string& newLink);
	std::vector<Event> getAllEvents() const;
	std::vector<Event> getEventsForMonth(int month) const;

	void validateEventData(const std::string& title, const std::tm& dateTime) const;
};