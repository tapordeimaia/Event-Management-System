#include "UserUI.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdio>
#endif


void UserUI::displayMenu()
{
	std::cout << "\nUser Menu\n";
	std::cout << "1. Browse events\n";
	std::cout << "2. Show interested events.\n";
	std::cout << "3. Remove from interested\n";
	std::cout << "0. Exit\n";
	std::cout << "Enter choice: ";
}

void UserUI::handleBrowseEvents()
{
	std::cout << "Enter month (1-12, 0 for all): ";
	int month;
	std::cin >> month;
	std::cin.ignore();

	service.startBrowsing(month);

	while (true) {
		try {
			const Event& current = service.getCurrentEvent();
			std::cout << "\n" << current.toString() << "\n";

			const std::string& url = current.getLink();
			#ifdef _WIN32
				ShellExecuteA(nullptr, nullptr, url.c_str(), nullptr, nullptr, SW_SHOW);
			#else
				const std::string command = "xdg-open \" + url + "\ ";
				system(command.c_str());
			#endif	

			std::cout << "\nOptions:\n";
			std::cout << "1. Add to interested\n";
			std::cout << "2. Next event\n";
			std::cout << "0. Back to menu\n";
			std::cout << "Choice: ";

			int choice;
			std::cin >> choice;
			std::cin.ignore();

			if (choice == 0) break;

			switch (choice) {
			case 1:
				service.addEventToInterested();
				std::cout << "Added to your list!\n";
				break;
			case 2:
				service.nextEvent();
				break;
			default:
				std::cout << "Invalid choice\n";
			}
		} catch (const std::exception e) {
			std::cout << "Error: " << e.what() << "\n";
		}
	}
}

void UserUI::handleShowInterested()
{
	const auto& events = service.getInterestedEvents();
	if (events.empty()) {
		std::cout << "No interested events.\n";
		return;
	}

	int i = 1;
	for (const auto& event : events) {
		std::cout << i++ << ". " << event.toString() << "\n";
	}
}

void UserUI::handleRemoveInterested()
{
	try {
		const auto& events = service.getInterestedEvents();
		if (events.empty()) {
			std::cout << "No interested events.\n";
			return;
		}

		std::cout << "Your interested events:\n";
		int i = 1;
		for (const auto& event : events) {
			std::cout << i++ << ". " << event.toString() << "\n";
		}

		std::cout << "Enter event number to remove: ";
		int choice;
		std::cin >> choice;
		std::cin.ignore();

		if (choice < 1 || choice > events.size()) {
			std::cout << "Invalid choice\n";
			return;
		}

		service.removeEventFromInterested(events[choice-1]);
		std::cout << "Event removed from your list\n";
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << "\n";
	}
}

std::tm UserUI::getDateTimeInput()
{
	std::tm time = {};
	std::cout << "Enter event date (YYY MM DD): ";
	std::cin >> time.tm_year >> time.tm_mon >> time.tm_mday;
	time.tm_year -= 1900;
	time.tm_mon -= 1;
	std::cin.ignore();
	return time;
}

UserUI::UserUI(UserService& service)
	:service(service) {}

void UserUI::run()
{
	while (true) {
		displayMenu();
		int choice;
		std::cin >> choice;
		std::cin.ignore();

		try {
			switch (choice) {
			case 1:
				handleBrowseEvents();
				break;
			case 2:
				handleShowInterested();
				break;
			case 3:
				handleRemoveInterested();
				break;
			case 0:
				return;
			default:
				std::cout << "Invaild choice";
			}
		}
		catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << "\n";
		}
	}
}




