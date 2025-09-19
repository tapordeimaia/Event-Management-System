#include "UserService.h"
#include <algorithm>
#include <QDesktopServices>
#include <QUrl>

/**
 * @brief Constructs a new UserService object.
 *
 * @param eventRepository Reference to the EventRepository object.
 */
UserService::UserService(EventRepository& eventRepository)
	: eventRepository(eventRepository), currentEventIndex(0) {}

/**
 * @brief Starts browsing events, optionally filtered by month.
 *
 * @param month The month to filter events by. If 0, all events are included.
 */
void UserService::startBrowsing(int month)
{
	if (month == 0) {
		filteredEvents = eventRepository.getAllEvents();
		std::sort(filteredEvents.begin(), filteredEvents.end(), [](const Event& a, const Event& b) {
			return std::mktime(const_cast<std::tm*>(&a.getDateTime())) < std::mktime(const_cast<std::tm*>(&b.getDateTime()));
			});
	}
	else {
		filterEventsByMonth(month);
	}
	currentEventIndex = 0;
}

/**
 * @brief Gets the current event being browsed.
 *
 * @return Event The current event.
 * @throws std::runtime_error If there are no events to display.
 */
Event UserService::getCurrentEvent() const
{
	if (filteredEvents.empty()) {
		throw std::runtime_error("No events to display");
	}
	return filteredEvents[currentEventIndex];
}

/**
 * @brief Moves to the next event in the browsing list.
 */
void UserService::nextEvent()
{
	if (filteredEvents.empty()) return;
	currentEventIndex = (currentEventIndex + 1) % filteredEvents.size();
}

/**
 * @brief Adds the current event to the list of interested events.
 */
void UserService::addEventToInterested()
{
	try {
		Event current = getCurrentEvent();
		userRepository.addEvent(current);

		// Open the event link automatically
		QDesktopServices::openUrl(QUrl(QString::fromStdString(current.getLink())));

		// Update attendees count
		Event updated = current;
		updated.setAttendees(current.getAttendees() + 1);
		eventRepository.updateEvent(current, updated);
	}
	catch (const std::exception& e) {
		throw;
	}
	/*
	if (!filteredEvents.empty()) {
		const Event& current = getCurrentEvent();
		userRepository.addEvent(current);

		Event updated = current;
		updated.setAttendees(current.getAttendees() + 1);
		eventRepository.updateEvent(current, updated);
	}
	*/
}

/**
 * @brief Removes an event from the list of interested events.
 *
 * @param title The title of the event to remove.
 * @param dateTime The date and time of the event to remove.
 * @throws std::runtime_error If the event is not found in the interested events.
 */
void UserService::removeEventFromInterested(const Event& event)
{
	const auto& interestedEvents = userRepository.getInterestedEvents();

	auto it = std::find(interestedEvents.begin(), interestedEvents.end(), event);
	if (it != interestedEvents.end()) {
		try {
			Event original = *it;
			userRepository.removeEvent(*it);
			Event updated = original;
			updated.setAttendees(original.getAttendees() - 1);
			eventRepository.updateEvent(original, updated);
		}
		catch (const std::exception& e) {
		}
	}
	else {
		throw std::runtime_error("Event not found in interested events");
	}
}

/**
 * @brief Gets the list of interested events.
 *
 * @return DynamicVector<Event> The list of interested events.
 */
std::vector<Event> UserService::getInterestedEvents() const
{
	return userRepository.getInterestedEvents();
}

/**
 * @brief Filters events by the specified month.
 *
 * @param month The month to filter events by.
 */
void UserService::filterEventsByMonth(int month)
{
	filteredEvents = eventRepository.getEventsForMonth(month);
}









