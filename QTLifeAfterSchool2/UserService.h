#pragma once
#include "EventRepository.h"
#include "UserRepository.h"
#include <vector>
#include <algorithm>

class UserService {
private:
	EventRepository& eventRepository;
	UserRepository userRepository;
	size_t currentEventIndex;

public:
	explicit UserService(EventRepository& eventRepository);

	void startBrowsing(int month = 0);
	Event getCurrentEvent() const;
	void nextEvent();
	void addEventToInterested();
	void removeEventFromInterested(const Event& event);
	std::vector<Event> getInterestedEvents() const;

	std::string getExportType() const {
		return userRepository.getExportType();
	}

	void setExportType(const std::string& type) {
		userRepository.setExportType(type);
	}

	void exportInterestedEvents(const std::string& filename) {
		userRepository.exportToFile(filename);
	}

	void displayExportedFile(const std::string& filename) {
		userRepository.displayExportedFile(filename);
	}

private:
	std::vector<Event> filteredEvents;
	void filterEventsByMonth(int month);
};