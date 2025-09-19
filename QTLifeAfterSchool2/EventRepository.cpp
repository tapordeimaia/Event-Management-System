#include "EventRepository.h"
#include <algorithm>
#include <iostream>



/**
 * @brief Adds a new event to the repository.
 *
 * @param event The event to be added.
 *
 * @throws std::runtime_error if the event already exists.
 */
void EventRepository::addEvent(const Event& event) {
	if (std::find(events.begin(), events.end(), event) == events.end()) {
		events.push_back(event);
	}
	else {
		throw std::runtime_error("Event already exists");
	}
}

/**
 * @brief Removes an event from the repository.
 *
 * @param event The event to be removed.
 *
 * @throws std::runtime_error if the event does not exist.
 */
void EventRepository::removeEvent(const Event& event) {
    auto it = std::find(events.begin(), events.end(), event);
    if (it == events.end()) {
        throw std::runtime_error("Event not found");
    }
    events.erase(it);
    std::cout << "Event removed successfully\n";
}

/**
 * @brief Updates an existing event in the repository.
 *
 * @param oldEvent The event to be updated.
 * @param newEvent The new event data.
 *
 * @throws std::runtime_error if the old event does not exist.
 */
void EventRepository::updateEvent(const Event& oldEvent, const Event& newEvent) {
	auto it = std::find(events.begin(), events.end(), oldEvent);
	if (it != events.end()) {
		*it = newEvent;
	}
	else {
		throw std::runtime_error("Event does not exist");
	}
}


/**
 * @brief Retrieves all events from the repository.
 *
 * @return DynamicVector<Event> A vector containing all events.
 */
std::vector<Event> EventRepository::getAllEvents() const {
	return events;
}

/**
 * @brief Retrieves events for a specific month from the repository.
 *
 * @param month The month for which to retrieve events (1-12).
 *
 * @return std::vector<Event> A vector containing events for the specified month.
 *
 * @throws std::invalid_argument if the month is not between 1 and 12.
 */
std::vector<Event> EventRepository::getEventsForMonth(int month) const {
	std::vector<Event> result;
	std::copy_if(events.begin(), events.end(), std::back_inserter(result),
		[month](const Event& event) { return event.getMonth() == month; });
	return result;
}

/**
 * @brief Checks if an event exists in the repository.
 *
 * @param event The event to check.
 *
 * @return bool True if the event exists, false otherwise.
 */
bool EventRepository::eventExists(const Event& event) const {
	return findEventIndex(event) != -1;
}

/**
 * @brief Finds the index of an event in the repository.
 *
 * @param event The event to find.
 *
 * @return int The index of the event if found, -1 otherwise.
 */
int EventRepository::findEventIndex(const Event& event) const {
	auto it = std::find(events.begin(), events.end(), event);
	return it != events.end() ? std::distance(events.begin(), it) : -1;
}