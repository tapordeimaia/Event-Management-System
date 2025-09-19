#pragma once
#include "event.h"
#include <vector>
#include <fstream>
#include <algorithm>

class EventRepository {
private:
	std::vector<Event> events;
	const std::string filename = "events.txt";

	void loadFromFile() {
		std::ifstream file(filename);
		if (file) {
			Event event;
			while (file >> event) {
				events.push_back(event);
			}
		}
	}

	void saveToFile() const {
		std::ofstream file(filename);
		for (const auto& event : events) {
			file << event;
		}
	}

public:
	EventRepository() {
		loadFromFile();
	}
	~EventRepository() {
		saveToFile();
	}

	void addEvent(const Event& event);
	void removeEvent(const Event& event);
	void updateEvent(const Event& oldEvent, const Event& newEvent);

	std::vector<Event> getAllEvents() const;
	std::vector<Event> getEventsForMonth(int month) const;

	int findEventIndex(const Event& event) const;
	bool eventExists(const Event& event) const;
};
