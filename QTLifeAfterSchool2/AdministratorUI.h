#pragma once
#include "EventService.h"
#include <iostream>

class AdministratorUI {
private:
	EventService& service;

	void displayMenu();
	void handleAddEvent();
	void handleRemoveEvent();
	void handleUpdateEvent();
	void handleDisplayEvents();

	std::tm getDateTimeInput();

public:
	AdministratorUI(EventService& service);
	void run();
};