#include "EventService.h"
#include <ctime>
#include <stdexcept>

/**
 * @brief Constructs an EventService object.
 *
 * @param repo Reference to an EventRepository object.
 */
EventService::EventService(EventRepository& repo) : repository(repo) {
}

/**
 * @brief Adds a new event to the repository.
 *
 * @param title The title of the event.
 * @param description The description of the event.
 * @param dateTime The date and time of the event.
 * @param attendees The number of attendees for the event.
 * @param link The link to the event.
 *
 * @throws std::invalid_argument if the event data is invalid.
 */
void EventService::addEvent(const std::string& title, const std::string& description, const std::tm& dateTime, int attendees, const std::string& link) {
	validateEventData(title, dateTime);
	Event event(title, description, dateTime, attendees, link);
	//repository.addEvent(event);
	undoManager.execute(std::make_unique<AddCommand>(repository, event));
}

/**
 * @brief Removes an event from the repository.
 *
 * @param title The title of the event to be removed.
 * @param dateTime The date and time of the event to be removed.
 *
 * @throws std::invalid_argument if the event does not exist.
 */
void EventService::removeEvent(const std::string& title, const std::tm& dateTime) {
	Event event(title, "", dateTime, 0, "");
	//repository.removeEvent(event);
	undoManager.execute(std::make_unique<RemoveCommand>(repository, event));
}

/**
 * @brief Updates an existing event in the repository.
 *
 * @param oldTitle The title of the event to be updated.
 * @param oldDateTime The date and time of the event to be updated.
 * @param newTitle The new title of the event.
 * @param newDescription The new description of the event.
 * @param newDateTime The new date and time of the event.
 * @param newAttendees The new number of attendees for the event.
 * @param newLink The new link to the event.
 *
 * @throws std::invalid_argument if the new event data is invalid.
 */
void EventService::updateEvent(const std::string& oldTitle, const std::tm& oldDateTime, const std::string& newTitle, const std::string& newDescription, const std::tm& newDateTime, int newAttendees, const std::string& newLink) {
	validateEventData(newTitle, newDateTime);
	Event oldEvent(oldTitle, "", oldDateTime, 0, "");
	Event newEvent(newTitle, newDescription, newDateTime, newAttendees, newLink);
	//repository.updateEvent(oldEvent, newEvent);
	undoManager.execute(std::make_unique<UpdateCommand>(repository, oldEvent, newEvent));
}

/**
 * @brief Retrieves all events from the repository.
 *
 * @return DynamicVector<Event> A vector containing all events.
 */
std::vector<Event> EventService::getAllEvents() const {
	return repository.getAllEvents();
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
std::vector<Event> EventService::getEventsForMonth(int month) const {
	if (month < 1 || month > 12) {
		throw std::invalid_argument("Invalid month, must be between 1 and 12");
	}
	return repository.getEventsForMonth(month);
}

/**
 * @brief Validates the event data.
 *
 * @param title The title of the event.
 * @param dateTime The date and time of the event.
 *
 * @throws std::invalid_argument if the title is empty or the event date is in the past.
 */
void EventService::validateEventData(const std::string& title, const std::tm& dateTime) const {
	if (title.empty()) {
		throw std::invalid_argument("Title cannot be empty");
	}
	
	time_t now = time(nullptr);
	tm currentTime;
	localtime_s(&currentTime, &now);
	tm eventTime = dateTime;

	if (eventTime.tm_year < currentTime.tm_year || (eventTime.tm_year == currentTime.tm_year && eventTime.tm_mon < currentTime.tm_mon) ||
		(eventTime.tm_year == currentTime.tm_year && eventTime.tm_mon == currentTime.tm_mon && eventTime.tm_mday < currentTime.tm_mday)) {
		throw std::invalid_argument("Event date must be in the future");
	}
}