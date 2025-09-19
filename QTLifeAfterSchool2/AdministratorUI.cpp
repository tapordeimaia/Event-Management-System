#include "AdministratorUI.h"
#include <iomanip>
#include <sstream>
#include <limits>

AdministratorUI::AdministratorUI(EventService& service) : service(service) {
}

void AdministratorUI::run() {
	while (true) {
		displayMenu();
		int choice;
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		try {
			switch (choice) {
			case 1:
				handleAddEvent();
				break;
			case 2:
				handleRemoveEvent();
				break;
			case 3:
				handleUpdateEvent();
				break;
			case 4:
				handleDisplayEvents();
				break;
			case 0:
				return;
			default:
				std::cout << "Invalid choice\n";
			}
		}
		catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << "\n";
		}
	}
}

void AdministratorUI::displayMenu() {
	std::cout << "\nAdministrator Menu\n";
	std::cout << "1. Add event\n";
	std::cout << "2. Remove event\n";
	std::cout << "3. Update event\n";
	std::cout << "4. Display events\n";
	std::cout << "0. Exit\n";
	std::cout << "Enter choice: ";
}

void AdministratorUI::handleAddEvent() {
	std::string title, description, link;
	std::tm dateTime = getDateTimeInput();
	int attendees;
	std::cout << "Title: ";
	std::getline(std::cin, title);
	std::cout << "Description: ";
	std::getline(std::cin, description);
	std::cout << "Attendees: ";
	std::cin >> attendees;
	std::cin.ignore();
	std::cout << "Link: ";
	std::getline(std::cin, link);
	service.addEvent(title, description, dateTime, attendees, link);
	std::cout << "Event added successfully\n";
}

void AdministratorUI::handleRemoveEvent() {
	std::string title;
	std::tm dateTime = getDateTimeInput();
	std::cout << "Title: ";
	std::getline(std::cin, title);
	service.removeEvent(title, dateTime);
	std::cout << "Event removed successfully\n";
}

void AdministratorUI::handleUpdateEvent() {
	std::string oldTitle, newTitle, newDescription, newLink;
	std::tm oldDateTime = getDateTimeInput();
	std::tm newDateTime = getDateTimeInput();
	int newAttendees;
	std::cout << "Old title: ";
	std::getline(std::cin, oldTitle);
	std::cout << "New title: ";
	std::getline(std::cin, newTitle);
	std::cout << "New description: ";
	std::getline(std::cin, newDescription);
	std::cout << "New attendees: ";
	std::cin >> newAttendees;
	std::cin.ignore();
	std::cout << "New link: ";
	std::getline(std::cin, newLink);
	service.updateEvent(oldTitle, oldDateTime, newTitle, newDescription, newDateTime, newAttendees, newLink);
	std::cout << "Event updated successfully\n";
}

void AdministratorUI::handleDisplayEvents() {
	const auto& events = service.getAllEvents();
	if (events.empty()) {
		std::cout << "No events available\n";
		return;
	}

	std::for_each(events.begin(), events.end(), [i=1](const Event& event) mutable {
		std::cout << i++ << ". " << event.toString() << "\n";
		});
}

std::tm AdministratorUI::getDateTimeInput() {
	std::tm time = {};
	int year, month, day, hour, minute;

	std::cout << "Year: ";
	std::cin >> year;
	time.tm_year = year - 1900;

	std::cout << "Month: ";
	std::cin >> month;
	time.tm_mon = month - 1;

	std::cout << "Day: ";
	std::cin >> day;
	time.tm_mday = day;

	std::cout << "Hour: ";
	std::cin >> hour;
	time.tm_hour = hour;

	std::cout << "Minute: ";
	std::cin >> minute;
	time.tm_min = minute;

	std::cin.ignore();
	return time;
}