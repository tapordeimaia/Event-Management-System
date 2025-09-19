#include "UserRepository.h"

/**
 * @brief Adds an event to the list of interested events.
 *
 * @param event The event to add.
 */
void UserRepository::addEvent(const Event& event)
{
	if (!isEventInList(event)) {
		interestedEvents.push_back(event);
	}
}

/**
 * @brief Removes an event from the list of interested events.
 *
 * @param event The event to remove.
 * @throws std::runtime_error If the event is not found in the list.
 */
void UserRepository::removeEvent(const Event& event)
{
	auto it = std::find(interestedEvents.begin(), interestedEvents.end(), event);
	if (it != interestedEvents.end()) {
		interestedEvents.erase(it);
	}
	else {
		throw std::runtime_error("Event not found");
	}
}

/**
 * @brief Gets the list of interested events.
 *
 * @return DynamicVector<Event> The list of interested events.
 */
const std::vector<Event>& UserRepository::getInterestedEvents() const
{
	return interestedEvents;
}

/**
 * @brief Checks if an event is in the list of interested events.
 *
 * @param event The event to check.
 * @return true If the event is in the list.
 * @return false If the event is not in the list.
 */
bool UserRepository::isEventInList(const Event& event) const
{
	return std::find(interestedEvents.begin(), interestedEvents.end(), event) != interestedEvents.end();
}

