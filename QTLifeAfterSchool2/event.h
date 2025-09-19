#pragma once
#include <string>
#include <ctime>
#include <iostream>

class Event
{
private:
	std::string title;
	std::string description;
	std::tm dateTime;
	int attendees;
	std::string link;

public:
	Event() : title(""), description(""), dateTime(), attendees(0), link("") {};

	Event(const std::string& title, const std::string& description, const std::tm& dateTime, int attendees, const std::string& link);

	// Copy constructor
	Event(const Event& other) = default;

	// Copy assignment
	Event& operator=(const Event& other) = default;

	// Move constructor
	Event(Event&& other) noexcept = default;

	// Move assignment
	Event& operator=(Event&& other) noexcept = default;

	// Destructor
	~Event() = default;

	std::string getTitle() const;
	std::string getDescription() const;
	std::tm& getDateTime();
	const std::tm& getDateTime() const;
	std::string getDateTimeAsString() const;
	int getAttendees() const;
	std::string getLink() const;

	void setTitle(const std::string& title);
	void setDescription(const std::string& description);
	void setDateTime(const std::tm& dateTime);
	void setAttendees(int attendees);
	void setLink(const std::string& link);

	bool operator==(const Event& other) const;
	bool operator!=(const Event& other) const;

	std::string toString() const;

	int getMonth() const { return dateTime.tm_mon + 1; }

	// I/O operators
	friend std::ostream& operator<<(std::ostream& os, const Event& event);
	friend std::istream& operator>>(std::istream& is, Event& event);
};