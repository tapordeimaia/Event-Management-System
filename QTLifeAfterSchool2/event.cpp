#include "event.h"
#include <sstream>
#include <iomanip>
#include <iostream>

/**
 * @brief Constructs an Event object with the given parameters.
 *
 * @param title The title of the event.
 * @param description The description of the event.
 * @param dateTime The date and time of the event.
 * @param attendees The number of attendees for the event.
 * @param link The link to the event.
 */
Event::Event(const std::string& title, const std::string& description, const std::tm& dateTime, int attendees, const std::string& link)
	: title(title), description(description), dateTime(dateTime), attendees(attendees), link(link) {
	if (link.find("http://") != 0 && link.find("https://") != 0) {
		this->link = "http://" + link;
	}
	else {
		this->link = link;
	}
}


/**
 * @brief Gets the title of the event.
 *
 * @return std::string The title of the event.
 */
std::string Event::getTitle() const {
	return title;
}
/**
 * @brief Gets the description of the event.
 *
 * @return std::string The description of the event.
 */
std::string Event::getDescription() const {
	return description;
}
/**
 * @brief Gets the date and time of the event.
 *
 * @return std::tm The date and time of the event.
 */
std::tm& Event::getDateTime() {
	return dateTime;
}	

const std::tm& Event::getDateTime() const {
	return dateTime;
}

std::string Event::getDateTimeAsString() const
{
	std::ostringstream oss;
	oss << std::put_time(&dateTime, "%Y-%m-%d %H:%M");
	return oss.str();
}

/**
 * @brief Gets the number of attendees for the event.
 *
 * @return int The number of attendees.
 */
int Event::getAttendees() const {
	return attendees;
}
/**
 * @brief Gets the link to the event.
 *
 * @return std::string The link to the event.
 */
std::string Event::getLink() const {
	return link;
}

/**
 * @brief Sets the title of the event.
 *
 * @param title The new title of the event.
 */
void Event::setTitle(const std::string& title) {
	this->title = title;
}
/**
 * @brief Sets the description of the event.
 *
 * @param description The new description of the event.
 */
void Event::setDescription(const std::string& description) {
	this->description = description;
}
/**
 * @brief Sets the date and time of the event.
 *
 * @param dateTime The new date and time of the event.
 */
void Event::setDateTime(const std::tm& dateTime) {
	this->dateTime = dateTime;
}	
/**
 * @brief Sets the number of attendees for the event.
 *
 * @param attendees The new number of attendees.
 */
void Event::setAttendees(int attendees) {
	this->attendees = attendees;
}
/**
 * @brief Sets the link to the event.
 *
 * @param link The new link to the event.
 */
void Event::setLink(const std::string& link) {
	this->link = link;
}

/**
 * @brief Compares two Event objects for equality.
 *
 * @param other The other Event object to compare with.
 *
 * @return bool True if the events are equal, false otherwise.
 */
bool Event::operator==(const Event& other) const {
	return title == other.title &&
		dateTime.tm_year == other.dateTime.tm_year &&
		dateTime.tm_mon == other.dateTime.tm_mon &&
		dateTime.tm_mday == other.dateTime.tm_mday &&
		dateTime.tm_hour == other.dateTime.tm_hour &&
		dateTime.tm_min == other.dateTime.tm_min;
}

/**
 * @brief Compares two Event objects for inequality.
 *
 * @param other The other Event object to compare with.
 *
 * @return bool True if the events are not equal, false otherwise.
 */
bool Event::operator!=(const Event& other) const {
	return !(*this == other);
}

/**
 * @brief Converts the Event object to a string representation.
 *
 * @return std::string The string representation of the event.
 */
std::string Event::toString() const {
	std::ostringstream oss;
	oss << "Event: " << title << "\n"
		<< "Description: " << description << "\n"
		<< "Date: " << std::put_time(&dateTime, "%Y-%m-%d %H:%M") << "\n"
		<< "Attendees: " << attendees << "\n"
		<< "Link: " << link << "\n";
	return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Event& event)
{
	auto time = std::mktime(const_cast<std::tm*>(&event.dateTime));
	std::tm localTime;
	localtime_s(&localTime, &time); // Use localtime_s for thread safety and to avoid deprecation warnings
	os << event.title << "\n"
		<< event.description << "\n"
		<< std::put_time(&localTime, "%Y-%m-%d %H:%M") << "\n"
		<< event.attendees << "\n"
		<< event.link << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, Event& event)
{
	std::getline(is, event.title);
	std::getline(is, event.description);

	std::string timeStr;
	std::getline(is, timeStr);
	std::istringstream timeIss(timeStr);
	timeIss >> std::get_time(&event.dateTime, "%Y-%m-%d %H:%M");

	is >> event.attendees;
	is.ignore(); // Ignore the newline character after the number of attendees
	std::getline(is, event.link);
	return is;
}
