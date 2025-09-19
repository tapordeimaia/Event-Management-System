#pragma once
#include "event.h"
#include "exceptions.h"

class EventValidator {
public:
	static void validate(const Event& event) {
		if (event.getTitle().empty()) {
			throw ValidationException("Title cannot be empty");
		}
		if (event.getDescription().empty()) {
			throw ValidationException("Description cannot be empty");
		}
		if (event.getAttendees() < 0) {
			throw ValidationException("Number of attendees cannot be negative");
		}
		if (event.getLink().empty()) {
			throw ValidationException("Link cannot be empty");
		}

		time_t now = time(nullptr);
		tm currentTime;
		localtime_s(&currentTime, &now);
		tm eventTime = event.getDateTime();

		if (eventTime.tm_year < currentTime.tm_year ||
			(eventTime.tm_year == currentTime.tm_year && eventTime.tm_mon < currentTime.tm_mon) ||
			(eventTime.tm_year == currentTime.tm_year && eventTime.tm_mon == currentTime.tm_mon && eventTime.tm_mday < currentTime.tm_mday)) {
			throw ValidationException("Event date cannot be in the past");
		}
	}
};